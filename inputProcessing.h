#ifndef COSMOS_INPUT_HEADER
#define COSMOS_INPUT_HEADER

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "cosmosDefines.h"

using namespace std;

const string heroVersion = "2.8.1";
const string heroLevelFileName = "heroLevels.txt";

extern bool useConfigFile;
extern ifstream configFile;

const string welcomeMessage = "Welcome to Malizia's v" + heroVersion + " PvE Instance Solver!";
const string helpMessage = "If you don't know what to do you can type help at any time to get an explanation about the current step.";

enum QueryType {question, integer, raw};

const string inputModeQuestion = "Do you want to input everything via command line?";
const string inputModeHelp =
    "  If YES is selected all necessary data will be asked of you here.\n" 
    "  Note that selecting NO only makes sense if you have edited the data in the script and compiled the program for yourself! \n";
const string heroFileNotFoundErrorMessage = 
    "  Could not find Hero File or Hero File is deprecated. (Were there any new Heroes added recently?)\n"
    "  Switching to manual input mode...\n";

const string heroInputModeQuestion = "Do you want to load hero levels from file?";
const string heroInputModeHelp =
    "  If YES is selected the hero levels will be loaded from the " + heroLevelFileName + " -file in this folder.\n"
    "  If this is your first time using this calculator then that file will be created for you when you select NO.\n";

const string heroInputHelp = 
    "  Enter the Level of the hero whose name is displayed on the left. If you don't own that hero, enter 0.\n";

const string lineupInputHelp = 
    "  Enter Monsters separated by a comma and no spaces.\n"
    "  Normal monsters are written with their element (a,e,w,f) and their tier number. So the level 5 water monster is w5.\n"
    "  Heroes are written first with their full name and a colon(:) followed by their level. For example: forestdruid:50\n"
    "  Full example: a1,geror:22,f13,w2,ladyoftwilight:1\n"
    "  The other alternative is selecting a quest from the game. For example: Typing quest23 loads the lineup for the 23rd quest.\n";

const string maxMonstersAllowedHelp =
    "  This determines the maximum size of your lineup.\n"
    "  The most common input here is 6 with the exception of doing quests where it can also be 5 or 4.\n";

const string minimumMonsterCostHelp = 
    "  This determines how expensive a monster needs to be in order for the calculator to consider it for a solution.\n"
    "  This feature is intended for users with a lot of followers or good heroes to ignore monsters like a1.\n"
    "  Example: Entering 215000 will exclude e8 and cheaper monsters in the solution.\n"
    "  Special Values are: 0 for ALL monsters considered and -1 for NO monsters considered.\n";

const string maxFollowerHelp = 
    "  This determines how expensive the entire solution is allowed to be.\n"
    "  I only reluctantly put this option in because a lot of people asked for it. "
    "Note that as soon as calculation starts an upper bound is automatically generated by a greedy approach.\n"
    "  You can enter your followers here if you think that it speeds up calculation. "
    "But then you won't be able to know how many followers you are missing to beat the lineup. Your choice.\n"
    "  Enter -1 if you don't want to set the limit yourself.\n";

// Initialize a config file provided by filename
void initConfigFile(string configFileName);

// Wait for user input before continuing. Used to stop program from colsing outside of a command line.
void haltExecution();

string getResistantInput(string query, string help, QueryType queryType = raw);

// Ask the user a question that they can answer via command line
bool askYesNoQuestion(string question, string help);

// Output things on the command line. Using shouldOutput this can be easily controlled globally
void debugOutput(time_t timeStamp, string message, bool shouldOutput, bool finishLastOutput, bool finishLine);

// Promt the User via command line to input his hero levels and return them as a vector<int>
vector<int> takeHerolevelInput();

// Promt the user via command Line to input a monster lineup and return them as a vector of pointers to those monster
vector<int8_t> takeLineupInput(string prompt, int &questNumber);

// Parse string linup input into actual monsters if there are heroes in the input, a leveled hero is added to the database
vector<int8_t> makeMonstersFromStrings(vector<string> stringLineup);

// Parse hero input from a string into its name and level
pair<size_t, int> parseHeroString(string heroString);

// Splits strings into a vector of strings. No need to optimize, only used for input.
vector<string> split(string s, string to_split);

#endif