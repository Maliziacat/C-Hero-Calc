#ifndef COSMOS_DATA_HEADER
#define COSMOS_DATA_HEADER

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

#include "cosmosClasses.h"

using namespace std;

extern vector<int8_t> availableHeroes; // Contains all User Heroes, readily Leveled

extern vector<int8_t> monsterList; // Contains pointers to raw Monster Data from a1 to f15, will be sorted by follower cost
extern map<string, int8_t> monsterMap; // Maps monster Names to their pointers (includes heroes)

extern int8_t baseMonsterSize;

static vector<Monster> monsterBaseList { // Raw Monster Data, holds the actual Objects
	Monster(  8,  20,    1000,  "a1", air),
	Monster(  6,  48,    3900,  "a2", air),
	Monster( 12,  36,    8000,  "a3", air),
	Monster( 26,  24,   15000,  "a4", air),
	Monster( 20,  60,   41000,  "a5", air),
	Monster( 34,  62,   96000,  "a6", air),
	Monster( 26, 106,  144000,  "a7", air),
	Monster( 52,  78,  257000,  "a8", air),
	Monster( 54, 116,  495000,  "a9", air),
	Monster( 60, 142,  785000, "a10", air),
	Monster(110, 114, 1403000, "a11", air),
	Monster( 88, 164, 1733000, "a12", air),
	Monster( 94, 210, 2772000, "a13", air),
	Monster(142, 200, 4785000, "a14", air),
	Monster(190, 226, 8897000, "a15", air),

	Monster(  6,  30,    1400,  "w1", water),
	Monster( 12,  24,    3900,  "w2", water),
	Monster( 24,  18,    8000,  "w3", water),
	Monster( 20,  36,   18000,  "w4", water),
	Monster( 18,  78,   52000,  "w5", water),
	Monster( 44,  44,   84000,  "w6", water),
	Monster( 32,  92,  159000,  "w7", water),
	Monster( 36, 108,  241000,  "w8", water),
	Monster( 70,  80,  418000,  "w9", water),
	Monster( 70, 110,  675000, "w10", water),
	Monster( 79, 152, 1315000, "w11", water),
	Monster( 78, 188, 1775000, "w12", water),
	Monster(128, 140, 2398000, "w13", water),
	Monster(122, 212, 4159000, "w14", water),
	Monster(142, 276, 7758000, "w15", water),

	Monster(  4,  44,    1300,  "e1", earth),
	Monster(  8,  30,    2700,  "e2", earth),
	Monster( 16,  26,    7500,  "e3", earth),
	Monster( 10,  72,   18000,  "e4", earth),
	Monster( 40,  36,   54000,  "e5", earth),
	Monster( 24,  72,   71000,  "e6", earth),
	Monster( 36,  66,  115000,  "e7", earth),
	Monster( 60,  60,  215000,  "e8", earth),
	Monster( 48, 120,  436000,  "e9", earth),
	Monster( 64, 122,  689000, "e10", earth),
	Monster( 81, 134, 1130000, "e11", earth),
	Monster(120, 128, 1903000, "e12", earth),
	Monster(132, 190, 3971000, "e13", earth),
	Monster(136, 244, 6044000, "e14", earth),
	Monster(186, 200, 7173000, "e15", earth),

	Monster( 10,  16,    1000,  "f1", fire),
	Monster( 16,  18,    3900,  "f2", fire),
	Monster(  8,  54,    8000,  "f3", fire),
	Monster( 16,  52,   23000,  "f4", fire),
	Monster( 24,  42,   31000,  "f5", fire),
	Monster( 20, 104,   94000,  "f6", fire),
	Monster( 44,  54,  115000,  "f7", fire),
	Monster( 50,  94,  321000,  "f8", fire),
	Monster( 58, 102,  454000,  "f9", fire),
	Monster( 82, 104,  787000, "f10", fire),
	Monster( 70, 164, 1229000, "f11", fire),
	Monster( 92, 156, 1718000, "f12", fire),
	Monster(130, 166, 3169000, "f13", fire),
	Monster(168, 168, 4741000, "f14", fire),
	Monster(136, 234, 5676000, "f15", fire)
};
static vector<Monster> baseHeroes { // Raw, unleveld Hero Data, holds actual Objects
	Monster( 12,  50, 0, "james",             earth, legendary, {pAoe,    all, 1}),

	Monster( 14,  22, 0, "hunter",            air,   common,    {buff,    air, 2}),
	Monster( 20,  40, 0, "shaman",            earth, rare,      {protect, earth , 2}),
	Monster( 22,  82, 0, "alpha",             fire,  legendary, {aoe,     all, 1}),

	Monster( 12,  28, 0, "carl",              water, common,    {buff,    water , 2}),
	Monster( 22,  38, 0, "nimue",             air,   rare,      {protect, air, 2}),
	Monster( 26,  70, 0, "athos",             earth, legendary, {protect, all, 2}),

	Monster( 16,  24, 0, "jet",               fire,  common,    {buff,    fire, 2}),
	Monster( 24,  36, 0, "geron",             water, rare,      {protect, water, 2}),
	Monster( 40,  46, 0, "rei",               air,   legendary, {buff,    all, 2}),

	Monster( 22,  19, 0, "ailen",             earth, common,    {buff,    earth, 2}),
	Monster( 18,  50, 0, "faefyr",            fire,  rare,      {protect, fire, 2}),
	Monster( 32,  60, 0, "auri",              water, legendary, {heal,    all, 2}),

	Monster( 16,  28, 0, "k41ry",             air,   common,    {buff,    air, 3}),
	Monster( 20,  46, 0, "t4urus",            earth, rare,      {buff,    all, 1}),
	Monster( 20, 100, 0, "tr0n1x",            fire,  legendary, {aoe,     all, 3}),

	Monster(  8,  58, 0, "aquortis",          water, common,    {buff,    water, 3}),
	Monster( 32,  30, 0, "aeris",             air,   rare,      {heal,    all, 1}),
	Monster(  2,  75, 0, "geum",              earth, legendary, {berserk, self, 2}),

	Monster( 12,  38, 0, "rudean",            fire,  common,    {buff,    fire, 3}),
	Monster( 50,  18, 0, "aural",             water, rare,      {berserk, self, (float)1.2}),
	Monster( 46,  46, 0, "geror",             air,   legendary, {friends, self, (float)1.2}),

	Monster( 16,  30, 0, "ourea",             earth, common,    {buff,    earth, 3}),
	Monster( 20,  48, 0, "erebus",            fire,  rare,      {champion,fire, 2}),
	Monster( 36,  62, 0, "pontus",            water, legendary, {adapt,   self, 2}),

	Monster( 14,  36, 0, "oymos",             air,   common,    {buff,    air, 4}),
	Monster( 32,  32, 0, "xarth",             earth, rare,      {champion,earth, 2}),
	Monster( 32,  76, 0, "atzar",             fire,  legendary, {adapt,   self, 2}),

	Monster( 18,  30, 0, "hama",              water, common,    {buff,    water, 4}),
	Monster( 34,  34, 0, "hallinskidi",       air,   rare,      {champion,air, 2}),
	Monster( 42,  60, 0, "rigr",              earth, legendary, {adapt,   self, 2}),

	Monster( 20,  45, 0, "ladyoftwilight",    air,   common,    {protect, all, 1}),
	Monster( 30,  70, 0, "tiny",              earth, rare,      {aoe,     all, 2}),
	Monster( 40,  90, 0, "nebra",             fire,  legendary, {buff,    all, 8}),

	Monster( 44,  66, 0, "veildur",           earth, legendary, {champion,all, 3}),
	Monster( 48,  72, 0, "brynhildr",         air,   legendary, {champion,all, 4}),
	Monster( 52,  78, 0, "groth",             fire,  legendary, {champion,all, 5}),

	Monster( 12,  60, 0, "sigrun",            fire,  legendary, {ricochet,all, (float)0.5}),
	Monster( 14,  70, 0, "koldis",            water, legendary, {ricochet,all, (float)0.5}),
	Monster( 16,  75, 0, "alvitr",            earth, legendary, {ricochet,all, (float)0.5}),

	Monster( 42,  70, 0, "zeth",              water, legendary, {revenge, all, (float)0.1}),
	Monster( 46,  76, 0, "koth",              earth, legendary, {revenge, all, (float)0.15}),
	Monster( 50,  82, 0, "gurth",             air,   legendary, {revenge, all, (float)0.2}),

	Monster( 45,  75, 0, "spyke",             air,   legendary, {training,self, 5}),
	Monster( 55,  70, 0, "aoyuki",            water, legendary, {rainbow, self, 50}),
	Monster(100,  50, 0, "gaiabyte",          earth, legendary, {wither,  self, (float)0.5}),

	Monster( 25,  35, 0, "werewolf",          earth, common,    {prot_l,  all, 1}),
	Monster( 35,  55, 0, "jackoknight",       air,   rare,      {buff_l,  all, 1}),
	Monster( 45,  75, 0, "dullahan",          fire,  legendary, {champ_l, all, 1}),

	Monster( 10,  20, 0, "valor",             air,   common,    {protect, air, 1}),
	Monster(  8,  30, 0, "rokka",             earth, common,    {protect, earth, 1}),
	Monster( 12,  24, 0, "pyromancer",        fire,  common,    {protect, fire, 1}),
	Monster(  6,  50, 0, "bewat",             water, common,    {protect, water, 1}),

	Monster( 32,  22, 0, "nicte",             air,   rare,      {buff,    air, 4}),
	Monster( 16,  46, 0, "forestdruid",       earth, rare,      {buff,    earth, 4}),
	Monster( 24,  32, 0, "ignitor",           fire,  rare,      {buff,    fire, 4}),
	Monster( 14,  58, 0, "undine",            water, rare,      {buff,    water, 4}),

	Monster( 20,  52, 0, "chroma",            air,   rare,      {protect, air, 4}),
	Monster( 44,  26, 0, "petry",             earth, rare,      {protect, earth, 4}),
	Monster( 22,  58, 0, "zaytus",            fire,  rare,      {protect, fire, 4}),
	Monster( 36,  36, 0, "ladyodelith",       water, rare,      {protect, water, 4}),

	Monster( 54,  34, 0, "shygu",             air,   legendary, {prot_l,  air, 1}),
	Monster( 28,  72, 0, "thert",             earth, legendary, {prot_l,  earth, 1}),
	Monster( 64,  32, 0, "lordkirk",          fire,  legendary, {prot_l,  fire, 1}),
	Monster( 70,  30, 0, "neptunius",         water, legendary, {prot_l,  water, 1}),
};

static vector<vector<string>> quests { // Contains all quest lineups for easy referencing
	{""},
	{"w5"},
	{"f1", "a1", "f1", "a1", "f1", "a1"},
	{"f5", "a5"},
	{"f2", "a2", "e2", "w2", "f3", "a3"},
	{"w3", "e3", "w3", "e3", "w3", "e3"},       //5

	{"w4", "e1", "a4", "f4", "w1", "e4"},
	{"f5", "a5", "f4", "a3", "f2", "a1"},
	{"e4", "w4", "w5", "e5", "w4", "e4"},
	{"w5", "f5", "e5", "a5", "w4", "f4"},
	{"w5", "e5", "a5", "f5", "e5", "w5"},       //10

	{"f5", "f6", "e5", "e6", "a5", "a6"},
	{"e5", "w5", "f5", "e6", "f6", "w6"},
	{"a8", "a7", "a6", "a5", "a4", "a3"},
	{"f7", "f6", "f5", "e7", "e6", "e6"},
	{"w5", "e6", "w6", "e8", "w8"},             //15

	{"a9", "f8", "a8"},
	{"w5", "e6", "w7", "e8", "w8"},
	{"f7", "f6", "a6", "f5", "a7", "a8"},
	{"e7", "w9", "f9", "e9"},
	{"f2", "a4", "f5", "a7", "f8", "a10"},      //20

	{"w10", "a10", "w10"},
	{"w9", "e10", "f10"},
	{"e9", "a9", "w8", "f8", "e8"},
	{"f6", "a7", "f7", "a8", "f8", "a9"},
	{"w8", "w7", "w8", "w8", "w7", "w8"},       //25

	{"a9", "w7", "w8", "e7", "e8", "f10"},
	{"e9", "f9", "w9", "f7", "w7", "w7"},
	{"a10", "a8", "a9", "a10", "a9"},
	{"a10", "w7", "f7", "e8", "a9", "a9"},
	{"e10", "e10", "e10", "f10"},               //30

	{"e9", "f10", "f9", "f9", "a10", "a7"},
	{"w1", "a9", "f10", "e9", "a10", "w10"},
	{"e9", "a9", "a9", "f9", "a9", "f10"},
	{"f8", "e9", "w9", "a9", "a10", "a10"},
	{"w8", "w8", "w10", "a10", "a10", "f10"},   //35

	{"a8", "a10", "f10", "a10", "a10", "a10"},
	{"e8", "a10", "e10", "f10", "f10", "e10"},
	{"f10", "e10", "w10", "a10", "w10", "w10"},
	{"w9", "a10", "w10", "e10", "a10", "a10"},
	{"w10", "a10", "w10", "a10", "w10", "a10"}, //40

	{"e12", "e11", "a11", "f11", "a12"},
	{"a11", "a11", "e11", "a11", "e11", "a11"},
	{"a8", "a11", "a10", "w10", "a12", "e12"},
	{"a10", "f10", "a12", "f10", "a10", "f12"},
	{"w4", "e11", "a12", "a12", "w11", "a12"},  //45

	{"a11", "a12", "a11", "f11", "a11", "f10"},
	{"f12", "w11", "e12", "a12", "w12"},
	{"a11", "a11", "e12", "a11", "a11", "a13"},
	{"a13", "f13", "f13", "f13"},
	{"f12", "f12", "f12", "f12", "f12", "f12"}, //50

	{"a11", "e11", "a13", "a11", "e11", "a13"},
	{"f13", "w13", "a13", "f12", "f12"},
	{"a9", "f13", "f13", "f12", "a12", "a12"},
	{"a13", "a13", "a12", "a12", "f11", "f12"},
	{"a11", "f10", "a11", "e14", "f13", "a11"}, //55

	{"f13", "a13", "f13", "e13", "w12"},
	{"e10", "a13", "w12", "f13", "f13", "f13"},
	{"f7", "w11", "w13", "e14", "f13", "a14"},
	{"a8", "f15", "a14", "f14", "w14"},
	{"f12", "w13", "a14", "f13", "a13", "e10"}, //60

	{"f13", "e13", "a13", "w12", "f12", "a12"},
	{"w13", "e12", "w12", "a14", "a12", "f13"},
	{"e15", "f14", "w14", "a15"},
	{"e12", "a14", "e14", "w13", "e12", "f13"},
	{"e13", "f12", "w11", "w12", "a14", "e14"}, //65

	{"a14", "e13", "a11", "a14", "f13", "e13"},
	{"f13", "w13", "e14", "f13", "f14", "a14"},
	{"a15", "e15", "f15", "w15"},
	{"f13", "a14", "e14", "f13", "a14", "f13"},
	{"a11", "a14", "w13", "e14", "a14", "f14"}, //70

	{"e13", "a14", "f14", "w13", "f14", "e14"},
	{"w10", "a14", "a14", "a14", "a14", "w14"},
	{"w13", "w13", "f14", "a15", "a15", "e13"},
	{"a14", "e14", "e14", "e14", "e14", "e14"},
	{"w15", "w15", "e15", "w15", "f15"},        //75

	{"f14", "e15", "a15", "w14", "a14", "e15"},
	{"w14", "a15", "w14", "e15", "a15", "w14"},
	{"w15", "w15", "w15", "w15", "f15", "f15"},
	{"a15", "a15", "a15", "a15", "a15", "w14"},
	{"f15", "w15", "w15", "w15", "w15", "w15"}, //80
};

// Make sure all the values are set
void initMonsterData();

// Filter MonsterList by cost. User can specify if he wants to exclude cheap monsters
void filterMonsterData(int minimumMonsterCost);

// Initialize Hero Data
void initializeUserHeroes(vector<int> levels);

// Add a leveled hero to the databse 
int8_t addLeveledHero(Monster hero, int level);

// Create a new hero with leveled stats and return it
Monster getLeveledHero(const Monster & m, int level);

#endif
