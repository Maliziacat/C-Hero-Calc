#include "inputProcessing.h"

bool useConfigFile;
ifstream configFile;

// Initialize a config file provided by filename
void initConfigFile(string configFileName) {
	configFile.open(configFileName);
}

// Wait for user input before continuing. Used to stop program from closing outside of a command line.
void haltExecution() {
	cout << "Press enter to continue...";
	cin.get();
}

// Method for handling ALL input. Gives access to help, error resistance and config file for input.
string getResistantInput(string query, string help, QueryType queryType) {
	string inputString;
	while (true) {
		cout << query;
		if (useConfigFile) {
			useConfigFile = (bool) getline(configFile, inputString);
		} 
		if (!useConfigFile) {
			getline(cin, inputString);
		}
		inputString = split(inputString, " ")[0];
		if (useConfigFile) {
			cout << inputString << endl;
		}
		if (inputString == "help") {
			cout << help;
		} else {
			if (queryType == question && (inputString == "y" || inputString == "n")) {
				return inputString;
			}
			if (queryType == integer) {
				try {
					stoi(inputString);
					return inputString;
				} catch (...) {}
			}
			if (queryType == raw) {
				return inputString;
			}
		}
	}
}

// Ask the user a question that they can answer via command line
bool askYesNoQuestion(string questionMessage, string help) {
	string inputString = getResistantInput(questionMessage + " (y/n): ", help, question);
	if (inputString == "n") {
		return false;
	}
	if (inputString == "y") {
		return true;
	}
	return false;
}

// Output things on the command line. Using shouldOutput this can be easily controlled globally
void debugOutput(time_t timeStamp, string message, bool shouldOutput, bool finishLastOutput, bool finishLine) {
	if (shouldOutput) { 
		if (finishLastOutput) {
			cout << "Done! (" << right << setw(3) << (int)(time(NULL) - timeStamp) << " seconds)" << endl; // Exactly 20 bytes long
		}
		if (message != "") {
			cout << left << setw(60) << message; // With 60 there is exactly enough space to fit the finish message in on a windows cmd
			if (finishLine) {
				cout << endl;
			}
		}
	}
}


// Promt the User via command line to input his hero levels and return them as a vector<int>
vector<int> takeHerolevelInput() {
	vector<string> stringLevels;
	vector<int> levels {};
	string input;
	fstream heroFile;
	heroFile.exceptions(fstream::failbit);
	bool fileInput = true;

	if (fileInput) {
		try {
			heroFile.open(heroLevelFileName, fstream::in);
			heroFile >> input;
			stringLevels = split(input, ",");
			for (size_t i = 0; i < baseHeroes.size(); i++) {
				int level = 0;

				for (size_t j = 0; j < stringLevels.size(); j++) {
					pair<size_t, int> heroData = parseHeroString(stringLevels[j]);
					if (heroData.first == i) {
						level = heroData.second;
						break;
					}
				}

				levels.push_back(level);
			}
			heroFile.close();
		} catch (...) {
			cout << heroFileNotFoundErrorMessage;
			fileInput = false;
		}
	}
	if (!fileInput) {
		cout << "Enter the level of the hero whose name is shown." << endl;
		for (size_t i = 0; i < baseHeroes.size(); i++) {
			input = getResistantInput(baseHeroes[i].name + ": ", heroInputHelp, integer);
			levels.push_back(stoi(input));
		}

		// Write nonzero Hero Levels to file to use next time
		heroFile.open(heroLevelFileName, fstream::out);
		bool fNeedComma = false;
		for (size_t i = 0; i < levels.size(); i++) {
			if (levels[i] == 0)
				continue;

			if (fNeedComma)
				heroFile << ",";

			heroFile << baseHeroes[i].name << ":" << levels[i];
			fNeedComma = true;
		}
		heroFile.close();
		cout << "Hero Levels have been saved in a file. Next time you use this program you can load them from file." << endl;
	}
	return levels;
}

// Promt the user via command Line to input a monster lineup and return them as a vector of pointers to those monster
vector<int8_t> takeLineupInput(string prompt, int &questNumber) {
	vector<int8_t> lineup {};
	string questString = "quest";

	string input;

	while (true) {
		input = getResistantInput(prompt, lineupInputHelp, raw);
		try {
			if (input.compare(0, questString.length(), questString) == 0) {
				questNumber = stoi(input.substr(questString.length(), 2));
				lineup = makeMonstersFromStrings(quests[questNumber]);
				return lineup;
			} else {
				vector<string> stringLineup = split(input, ",");
				lineup = makeMonstersFromStrings(stringLineup);
				return lineup;
			}
		} catch (...) {}
	}
}

// Parse string linup input into actual monsters if there are heroes in the input, a leveled hero is added to the database
vector<int8_t> makeMonstersFromStrings(vector<string> stringLineup) {
	vector<int8_t> lineup {};
	pair<size_t, int> heroData;

	for(size_t i = 0; i < stringLineup.size(); i++) {
		if(stringLineup[i].find(":") != stringLineup[i].npos) {
			heroData = parseHeroString(stringLineup[i]);
			lineup.push_back(addLeveledHero(baseHeroes[heroData.first], heroData.second));
		} else {
			lineup.push_back(monsterMap.at(stringLineup[i]));
		}
	}
	return lineup;
}

// Parse hero input from a string into its baseHeroes index and level
pair<size_t, int> parseHeroString(string heroString) {
	string name = heroString.substr(0, heroString.find(':'));
	size_t i = 0;

	for (i = 0; i < baseHeroes.size(); i++) {
		if (baseHeroes[i].name == name) {
			break;
		}
	}

	int level = stoi(heroString.substr(heroString.find(':')+1));
	return pair<size_t, int>(i, level);
}

// Splits strings into a vector of strings. No need to optimize, only used for input.
vector<string> split(string s, string to_split) {
	vector<string> output;
	size_t x = 0;
	size_t limit = 0;
	while(limit != s.npos){
		limit = s.find(to_split, x);
		output.push_back(s.substr(x, limit-x));
		x = limit + to_split.length();
	}
	return output;
}