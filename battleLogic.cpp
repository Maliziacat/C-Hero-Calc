#include "battleLogic.h"

int totalFightsSimulated = 0;

// Function determining if a monster is strictly better than another
bool isBetter(Monster * a, Monster * b, bool considerAbilities) {
	if (a->element == b->element) {
		return (a->damage >= b->damage) && (a->hp >= b->hp);
	} else { // a needs to be better than b even when b has elemental advantage, or a is at disadvantage
		return !considerAbilities && (a->damage >= b->damage * elementalBoost) && (a->hp >= b->hp * elementalBoost);
	}
}

FightData::FightData(Army &army) {
	lost = 0;
	armySize = army.monsterAmount;
	lineup = army.monsters;

	frontDamageTaken = 0;
	healing = 0;
	cumAoeDamageTaken = 0;
	berserkProcs = 0;

	damage = 0;
	damageBuff = 0;
	protection = 0;
	aoeDamage = 0;
	paoeDamage = 0;
	revengeDamage = 0;
	healingSkill = 0;
	pureMonsters = 0;
}

void FightData::LoadSkills() {
	HeroSkill * skill;

	for (int8_t i = lost; i < armySize; i++) {
		skill = &monsterReference[lineup[i]].skill;
		skillType[i] = skill->type;
		skillTarget[i] = skill->target;
		skillAmount[i] = skill->amount;
	}
}

void FightData::LoadHeroInfluences() {
	damageBuff = 0;
	protection = 0;
	aoeDamage = 0;
	paoeDamage = 0;
	revengeDamage = 0;
	healingSkill = 0;
	pureMonsters = 0;
	elements = 0;

	if (HasLost())
		return;

	Monster *currentMonster = &monsterReference[lineup[lost]];

	for (int i = lost; i < armySize; i++) {
		if (cumAoeDamageTaken >= currentMonster->hp) { // Check for Backline Deaths
			if (lost == i) {
				if (skillType[lost] == revenge) {
					aoeDamage += (int)(currentMonster->damage * skillAmount[lost] + 0.5);
				}
				OnCurrentMonsterDeath();
				currentMonster = &monsterReference[lineup[lost]];
			}
		} else {
			// track elements of monsters before current monster
			if (i != lost)
				elements |= 1 << currentMonster->element;

			if (skillType[i] == nothing) {
				pureMonsters++; // count for friends ability
			} else if (skillType[i] == protect && (skillTarget[i] == all || skillTarget[i] == currentMonster->element)) {
				protection += (int)(skillAmount[i]);
			} else if (skillType[i] == buff && (skillTarget[i] == all || skillTarget[i] == currentMonster->element)) {
				damageBuff += (int)(skillAmount[i]);
			} else if (skillType[i] == champion && (skillTarget[i] == all || skillTarget[i] == currentMonster->element)) {
				damageBuff += (int)(skillAmount[i]);
				protection += (int)(skillAmount[i]);
			} else if (skillType[i] == heal) {
				healingSkill += (int)(skillAmount[i]);
			} else if (skillType[i] == aoe) {
				aoeDamage += (int)(skillAmount[i]);
			} else if (skillType[i] == pAoe && i == lost) {
				paoeDamage += currentMonster->damage;
			} else if (skillType[i] == ricochet && i == lost) {
				paoeDamage += (int)(currentMonster->damage * skillAmount[i]);
			}
		}
	}
}

void FightData::Heal() {
	// these values are from the last iteration
	frontDamageTaken -= healing;
	cumAoeDamageTaken -= healing;

	if (frontDamageTaken < 0) {
		frontDamageTaken = 0;
	}
	if (cumAoeDamageTaken < 0) {
		cumAoeDamageTaken = 0;
	}
}

bool FightData::HasLost() {
	return lost >= armySize;
}

void FightData::SetCurrentMonster() {
	currentMonster = &monsterReference[lineup[lost]];
}

Element FightData::GetCurrentElement() {
	return currentMonster->element;
}

int FightData::GetProtection() {
	return protection;
}

void FightData::CalcDamage(Element enemyElement, int enemyProtection, int turncounter) {
	int elementalDifference;

	// Get Base Damage for this Turn
	damage = currentMonster->damage;

	// Handle Monsters with skills berserk or friends
	if (skillType[lost] == friends) {
		damage = (int)(damage * pow(skillAmount[lost], pureMonsters));
	} else if (skillType[lost] == adapt && currentMonster->element == enemyElement) {
		damage = (int)(damage * skillAmount[lost]);
	} else if (skillType[lost] == berserk) {
		damage = (int)(damage * pow(skillAmount[lost], berserkProcs));
		berserkProcs++;
	} else if (skillType[lost] == training) {
		damage += (int)(skillAmount[lost] * turncounter);
	} else if (skillType[lost] == rainbow && elements == 15) { // 15 is 1111 in binary, so all four elements are included
		damage += (int)(skillAmount[lost]);
	}

	// Add Buff Damage
	damage += damageBuff;

	// Handle Elemental advantage
	elementalDifference = (currentMonster->element - enemyElement);
	if (elementalDifference == -1 || elementalDifference == 3) {
		damage = (int)(damage * elementalBoost);
	}

	// Handle Protection
	if (damage > enemyProtection) {
		damage -= enemyProtection;
	} else {
		damage = 0;
	}
}

int FightData::GetDamageGiven() {
	return damage + aoeDamage;
}

int FightData::GetAoeDamageGiven() {
	return aoeDamage + paoeDamage;
}

void FightData::ApplyDamage(int enemyDamageGiven, int enemyAoeDamageGiven) {
	// Write values into permanent Variables for the next iteration
	frontDamageTaken += enemyDamageGiven;
	cumAoeDamageTaken += enemyAoeDamageGiven;
	healing = healingSkill;

	// Check if the first Monster died (otherwise it will be revived next turn)
	if (currentMonster->hp <= frontDamageTaken) {
		if (skillType[lost] == revenge)
			revengeDamage = (int)(currentMonster->damage * skillAmount[lost] + 0.5);
		OnCurrentMonsterDeath();
		frontDamageTaken = cumAoeDamageTaken;
	}
}

void FightData::ApplyRevengeDamage(int revengeDamage) {
	frontDamageTaken += revengeDamage;
	cumAoeDamageTaken += revengeDamage;

	if (currentMonster->hp <= frontDamageTaken) {
		OnCurrentMonsterDeath();
		frontDamageTaken = cumAoeDamageTaken;
	} else if (skillType[lost] == wither && frontDamageTaken != cumAoeDamageTaken) {
		// wither damage happens after AoE damage,
		// so probably happens after revenge damage
		int remainingHealth = currentMonster->hp - frontDamageTaken;
		remainingHealth = (int)(remainingHealth * skillAmount[lost] + 0.5); // round up
		frontDamageTaken = currentMonster->hp - remainingHealth;
	}
}

void FightData::OnCurrentMonsterDeath() {
	lost++;
	berserkProcs = 0;
}

// TODO: Implement MAX AOE Damage to make sure nothing gets revived
// Simulates One fight between 2 Armies and writes results into left's LastFightData
void simulateFight(Army & left, Army & right, bool verbose) {
	// left[0] and right[0] are the first to fight
	// Damage Application Order:
	//  1. Base Damage of creature
	//  2. Multiplicators of self       (friends, berserk)
	//  3. Buffs from heroes            (Hunter, Rei, etc.)
	//  4. Elemental Advantage          (f.e. Fire vs. Earth)
	//  5. Protection of enemy Side     (Nimue, Athos, etc.)
	//  6. AOE of friendly Side         (Tiny, Alpha, etc.)
	//  7. Healing of enemy Side        (Auri, Aeris, etc.)

	totalFightsSimulated++;

	FightData leftData(left);
	FightData rightData(right);
	int turncounter = 0;

	if (verbose) {
		cout << endl << endl << "Left: " << endl;
		left.print(false /*reverse*/, true /*verbose*/);
		cout << endl << "Right: " << endl;
		right.print(false /*reverse*/, true /*verbose*/);
		cout << endl;
	}

	// If no heroes are in the army the result from the smaller army is still valid
	if (left.lastFightData.valid && !verbose) { 
		// Set pre-computed values to pick up where we left off
		leftData.lost                = leftData.armySize - 1; // All monsters of left died last fight only the new one counts
		leftData.frontDamageTaken    = left.lastFightData.leftAoeDamage;
		leftData.cumAoeDamageTaken   = left.lastFightData.leftAoeDamage;
		rightData.lost               = left.lastFightData.monstersLost;
		rightData.frontDamageTaken   = left.lastFightData.damage;
		rightData.cumAoeDamageTaken  = left.lastFightData.rightAoeDamage;
		rightData.berserkProcs       = left.lastFightData.berserk;
		turncounter                  = left.lastFightData.turncounter;
	}

	leftData.LoadSkills();
	rightData.LoadSkills();

	while (true) {
		leftData.LoadHeroInfluences();
		rightData.LoadHeroInfluences();

		// Heal everything that hasnt died
		leftData.Heal();
		rightData.Heal();

		// Add last effects of abilities and start resolving the turn
		if (leftData.HasLost() || rightData.HasLost()) {
			break; // At least One army was beaten
		}

		leftData.SetCurrentMonster();
		rightData.SetCurrentMonster();
		leftData.CalcDamage(rightData.GetCurrentElement(), rightData.GetProtection(), turncounter);
		rightData.CalcDamage(leftData.GetCurrentElement(), leftData.GetProtection(), turncounter);

		leftData.ApplyDamage(rightData.GetDamageGiven(), rightData.GetAoeDamageGiven());
		rightData.ApplyDamage(leftData.GetDamageGiven(), leftData.GetAoeDamageGiven());

		leftData.ApplyRevengeDamage(rightData.revengeDamage);
		rightData.ApplyRevengeDamage(leftData.revengeDamage);

		++turncounter;

		// Output detailed fight Data for debugging
		if (verbose) {
			Monster *leftMonster = &monsterReference[leftData.lineup[leftData.lost]];
			Monster *rightMonster = &monsterReference[rightData.lineup[rightData.lost]];
			cout << "End of Turn " << setw(2) << turncounter << ": ";
			cout << "Left monster (" << (int)leftData.lost + 1 << "): " << leftMonster->name << "  damage taken: " << setw(3) << leftData.frontDamageTaken << "  aoe taken: " << setw(3) << leftData.cumAoeDamageTaken;
			cout << "  Right monster (" << (int)rightData.lost + 1 << "): " << rightMonster->name << "  damage taken: " << setw(3) << rightData.frontDamageTaken << "  aoe taken: " << setw(3) << rightData.cumAoeDamageTaken << endl;
		}
	}

	// write all the results into a FightResult
	left.lastFightData.dominated = false;
	left.lastFightData.turncounter = turncounter;
	left.lastFightData.leftAoeDamage = leftData.cumAoeDamageTaken;
	left.lastFightData.rightAoeDamage = rightData.cumAoeDamageTaken;

	if (leftData.lost >= leftData.armySize) { //draws count as right wins. 
		left.lastFightData.rightWon = true;
		left.lastFightData.monstersLost = rightData.lost; 
		left.lastFightData.damage = rightData.frontDamageTaken;
		left.lastFightData.berserk = rightData.berserkProcs;
	} else {
		left.lastFightData.rightWon = false;
		left.lastFightData.monstersLost = leftData.lost; 
		left.lastFightData.damage = leftData.frontDamageTaken;
		left.lastFightData.berserk = leftData.berserkProcs;
	}
}