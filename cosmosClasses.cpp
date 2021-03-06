#include "cosmosClasses.h"
#include "cosmosDefines.h"

vector<Monster> monsterReference {}; // Will be filled with leveled heroes if needed (determined by input)

Monster::Monster(int damage, int hp, int cost, string name, Element element, Rarity rarity, HeroSkill skill) {
	this->damage = damage;
	this->hp = hp;
	this->cost = cost;
	this->name = name;
	this->element = element;
	this->rarity = rarity;
	this->skill = skill;

	this->isHero = (skill.type != nothing);
};

Monster::Monster() {
	isHero = false;
}

// Function for sorting Monsters by cost (ascending)
bool isCheaper(const Monster & a, const Monster & b) {
	return a.cost < b.cost;
}

FightResult::FightResult() {
	this->valid = false;
}

bool FightResult::operator <=(FightResult & toCompare) { // both results are expected to not have won
	if(this->leftAoeDamage < toCompare.leftAoeDamage || this->rightAoeDamage > toCompare.rightAoeDamage) {
		return false; // left is not certainly worse thn right
	}
	if (this->monstersLost == toCompare.monstersLost) {
		return this->damage <= toCompare.damage; // less damage dealt to the enemy -> left is worse
	} else {
		return this->monstersLost < toCompare.monstersLost; // less monsters destroyed on the enemy side -> left is worse
	}
}

bool FightResult::operator >=(FightResult & toCompare) {
	return toCompare <= *this;
}

Army::Army(vector<int8_t> monsters) {
	this->followerCost = 0;
	this->monsterAmount = 0;
	this->heroLineup = 0;
	this->lastFightData = FightResult();

	for(size_t i = 0; i < monsters.size(); i++) {
		this->add(monsters[i]);
	}
}

void Army::add(int8_t m) {
	int8_t heroId = m - baseMonsterSize;
	if (heroId >= 0)
		this->heroLineup |= (uint32_t) 1 << heroId;

	this->monsters[monsterAmount] = m;
	this->followerCost += monsterReference[m].cost;
	this->monsterAmount++;
}

void Army::replace(int i, int8_t m) {
	int8_t heroId = this->monsters[i] - baseMonsterSize;
	if (heroId >= 0)
		this->heroLineup &= ~((uint32_t) 1 << heroId);

	this->followerCost -= monsterReference[this->monsters[i]].cost;

	heroId = m - baseMonsterSize;
	if (heroId >= 0)
		this->heroLineup |= (uint32_t) 1 << heroId;

	this->monsters[i] = m;
	this->followerCost += monsterReference[m].cost;
}

string Army::toString(bool reverse, bool verbose) {
	stringstream s;
	s << "(Followers: " << setw(7) << this->followerCost << " | ";
	for (int i = 0; i < this->monsterAmount; i++) {
		int j = reverse ? j = (this->monsterAmount - 1) - i : i;
		if (verbose)
			s << "(" << i+1 << ") ";
		s << monsterReference[this->monsters[j]].name << " ";
		if (verbose)
			s << "(" << monsterReference[this->monsters[j]].damage << "/" << monsterReference[this->monsters[j]].hp << ")" << endl << "                      ";
	}
	s << ")"; 
	return s.str();
}

void Army::print(bool reverse, bool verbose) {
	cout << this->toString(reverse, verbose) << endl;
}

int32_t Army::avgFollowerCost() {
	int8_t monsterCount = 0;

	for (int i = 0; i < this->monsterAmount; i++) {
		if (baseMonsterSize - this->monsters[i] > 0)
			++monsterCount;
	}

	//cout << "There are " << (int)monsterCount << " nonheroes in this lineup." << endl;
	return (int32_t)(this->followerCost / monsterCount);
}

// Function for sorting FightResults by followers (ascending)
bool hasFewerFollowers(const Army & a, const Army & b) {
	return (a.followerCost < b.followerCost);
}
