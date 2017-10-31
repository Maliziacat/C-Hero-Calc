#include "cosmosDefines.h"

vector<int8_t> monsterList {}; // Contains pointers to raw Monster Data from a1 to f10, will be sorted by follower cost
map<string, int8_t> monsterMap {}; // Maps monster Names to their pointers (includes heroes)

vector<int8_t> availableHeroes {};
int8_t baseMonsterSize;

// Make sure all the values are set
void initMonsterData() {
	// Sort MonsterList by followers
	sort(monsterBaseList.begin(), monsterBaseList.end(), isCheaper);
	baseMonsterSize = (int8_t)(monsterBaseList.size());

	// Initialize Monster Data
	monsterReference.clear();
	monsterMap.clear();
	monsterList.clear();
	for (int8_t i = 0; i < baseMonsterSize; i++) {
		monsterReference.push_back(monsterBaseList[i]);
		monsterList.push_back(i);
		monsterMap.insert(pair<string, int8_t>(monsterBaseList[i].name, i));
	}

	availableHeroes.clear();
}

// Filter MonsterList by cost. User can specify if he wants to exclude cheap monsters
void filterMonsterData(int minimumMonsterCost) {
	while (monsterList.size() > 0 && monsterReference[monsterList[0]].cost <= minimumMonsterCost) {
		monsterList.erase(monsterList.begin());
	}
	if (minimumMonsterCost == -1) {
		monsterList = {};
	}
}

// Initialize Hero Data
void initializeUserHeroes(vector<int> levels) {
	for (size_t i = 0; i < baseHeroes.size(); i++) {
		if (levels[i] > 0) {
			availableHeroes.push_back(addLeveledHero(baseHeroes[i], levels[i]));
		}
	}
}

// Create a new hero with leveled stats and return it
Monster getLeveledHero(const Monster & m, int rarity, int level) {
	HeroSkill hallowSkill;
	int points = level-1;

	if (rarity == 1) {
		points = 2 * points;
	} else if (rarity == 2) {
		points = 6 * points;
	}

	// replace hallow skill with actual skill
	if (m.skill.type == hallow) {
		hallowSkill.target = all;

		if (rarity == 0) {
			hallowSkill.type = protect;
		} else if (rarity == 1) {
			hallowSkill.type = buff;
		} else if (rarity == 2) {
			hallowSkill.type = champion;
		}

		hallowSkill.amount = (float)floor(level / 9);
	}

	int value = m.hp + m.damage;
	return Monster(
		(int)round(m.hp + points * ((double)m.hp) / value),
		m.damage + (int)round(points * ((double)m.damage) / value),
		m.cost,
		m.name + ":" + to_string(level),
		m.element,
		m.skill.type == hallow ? hallowSkill : m.skill
	);
}

// Add a leveled hero to the databse 
int8_t addLeveledHero(Monster hero, int level) {
	Monster m = getLeveledHero(hero, rarities.at(hero.name), level);
	monsterReference.emplace_back(m);

	return (int8_t)(monsterReference.size()) - 1;
}