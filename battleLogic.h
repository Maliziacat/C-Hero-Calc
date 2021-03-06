#ifndef BATTLE_LOGIC_HEADER
#define BATTLE_LOGIC_HEADER

#include <vector>
#include <cmath>

#include "cosmosClasses.h"

const float elementalBoost = 1.5;
extern int totalFightsSimulated;

// Function determining if a monster is strictly better than another
bool isBetter(Monster * a, Monster * b, bool considerAbilities = false);

// Simulates One fight between 2 Armies
void simulateFight(Army & left, Army & right, bool verbose = false);

class FightData {
public:
	FightData(Army &army);

	void LoadSkills();
	void LoadHeroInfluences();
	void Heal();
	bool HasLost();

	void SetCurrentMonster();
	Element GetCurrentElement();
	int GetProtection();
	void CalcDamage(Element enemyElement, int enemyProtection, int turncounter);

	int GetDamageGiven();
	int GetAoeDamageGiven();
	void ApplyDamage(int enemyDamageGiven, int enemyAoeDamageGiven);
	void ApplyRevengeDamage(int revengeDamage);

	void OnCurrentMonsterDeath();

	// army-wide data
	int8_t lost;
	int8_t armySize;
	int8_t *lineup;

	int frontDamageTaken;
	int healing;
	int cumAoeDamageTaken;
	int berserkProcs;

	// skill data
	int damage;
	int damageBuff;
	int protection;
	int aoeDamage;
	int paoeDamage;
	int revengeDamage;
	int healingSkill;
	int pureMonsters;
	int elements; // this should be read as a 4-bit array

	Monster *currentMonster;
	SkillType skillType[6];
	Element skillTarget[6];
	float skillAmount[6];
};

#endif