#ifndef COSMOS_CLASSES_HEADER
#define COSMOS_CLASSES_HEADER

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <sstream>

using namespace std;

// Define types of HeroSkills and Elements
enum SkillType {
	nothing,
	buff,
	protect,
	aoe,
	pAoe,
	heal,
	berserk,
	friends,
	champion,
	adapt,
	training,
	rainbow,
	wither,
	revenge,
	buff_l,
	prot_l,
	champ_l,
	ricochet
};

enum Element {
	earth   = 0,
	air     = 1,
	water   = 2,
	fire    = 3,
	all,
	self
}; // also used for hero skill targets

enum Rarity {
	follower  = 0,
	common    = 0,
	rare      = 1,
	legendary = 2
};

// Defines Skills of Heros
struct HeroSkill {
	SkillType type;
	Element target;
	float amount;
};
static HeroSkill none = HeroSkill({nothing, air, 1}); // base skill used for normal monsters

// Defines a Monster or Hero
class Monster {
	public :
		int damage;
		int hp;
		int cost;
		bool isHero;
		string name;
		Element element;
		Rarity rarity;
		HeroSkill skill;

		Monster(int damage, int hp, int cost, string name, Element element, Rarity rarity = follower, HeroSkill skill = none);
		Monster();
};

// Function for sorting Monsters by cost (ascending)
bool isCheaper(const Monster & a, const Monster & b);

// Defines the results of a fight between two armies; monstersLost and damage describe the condition of the winning side
class FightResult {
	public :
		unsigned int leftAoeDamage  : 16; // how much aoe damage left took
		unsigned int rightAoeDamage : 16; // how much aoe damage right took

		unsigned int berserk        :  8; // berserk multiplier, if there is a berserker in the front
		unsigned int turncounter    :  8; // how many turns have passed since the battle started

		unsigned int damage         : 10; // how much damage dealt to the current leading mob of the winning side
		unsigned int monstersLost   :  3; // how many mobs lost on the winning side (the other side lost all)
		unsigned int valid          :  1; // If the result is valid
		unsigned int rightWon       :  1; // false -> left win, true -> right win.
		unsigned int dominated      :  1; // If the result is worse than another

		FightResult();

	bool operator <= (FightResult & toCompare);
	bool operator >= (FightResult & toCompare);
};

// Defines a single lineup of monsters
class Army {
	public:
		FightResult lastFightData; // 8 bytes
		int32_t followerCost;      // 4
		int8_t monsters[6];        // 6
		int8_t monsterAmount;      // 1
		uint32_t heroLineup;       // 4

		void add(int8_t m);
		void replace(int i, int8_t m);
		string toString(bool reverse, bool verbose = false);
		void print(bool reverse, bool verbose = false);
		int32_t avgFollowerCost();
		Army(vector<int8_t> monsters = {});
};

// Function for sorting Armies by followers (ascending)
bool hasFewerFollowers(const Army & a, const Army & b);

extern vector<Monster> monsterReference; // Will be filled with leveled heroes if needed (determined by input)

#endif