# Malizia's Cosmos Quest PvE Instance Solver

## Summary
This is a slightly modified version of [Diceycle's PvE Calculator](https://github.com/Diceycle/C-Hero-Calc).
The goal is to tweak that calculator to improve result quality, calculation speed, and memory usage.
This calculator, on the other hand, has significantly fewer features.

Game forum [here](http://www.kongregate.com/forums/910715-cosmos-quest/).
You can message me [here](http://www.kongregate.com/accounts/Malizia).

### What to do if something is wrong:
If the calculator does something you don't think it should, send [me a private message!](http://www.kongregate.com/accounts/Malizia)
Be sure to include your hero levels, the lineup you're fighting against, and a brief description of a) what the calculator did and b) what you expected the calculator to do.

### Features
* C++ based Calculator for solving PvE instances
* Hero Levels will be saved between executions
* All quests predefined
* Don't know how to input heroes, monster or just generally confused how to use this calculator? Type `help` when asked for input
* Precompiled exe included for x64 Windows 10

### What's Different from Diceycle's calc?
* Calculator will attempt to replace single hero in an "optimal" lineup to try to improve the solution.  Mostly useful for the "greedy" solutions.
* Calculator should run faster than Diceycle's calc, except if you're good at estimating minimum follower cost.
* Hero input files are different.
* No JSON battle lineup you can paste into the game.
* No option to specify minimum follower cost, or maximum follower amount.
* No option to calculate multiple lineups at once.

## Usage
For most people, only downloading the exe and running it will be enough. For those who are not on Windows they will need to download all files and compile for themselves.
Saved hero files will look like "heroLevels.txt".  Creating / editing the file should be simple: heroes should be comma separated, with no spaces or returns.  Heroes are listed with the format "<heroname>:<level>", as you would input for an enemy lineup, like "jackolantern:15".  The hero ordering does not matter.

### Compiling
I compile using Visual C++, available with Visual Studio 2017.  There is a free edition available for Windows [here](https://www.visualstudio.com/downloads/).
If you are not on Windows consider looking at Dicecycle's calculator's makefile for instructions for compiling with gcc.

### Input via command line
If you use the exe then the program will take you through the steps you need to take to start calculating. Access the quests by typing `questX` (X being the quest number) when asked for a lineup. All other questions can be answered by typing `help` at any point.

## Bugs, Warnings and other problems

### Regarding non-optimal solutions
There are many situations where this calculator does not give the optimal solution.  This is a core fault of the calculator design.  You're welcome to report it to me as a bug, but be aware I probably cannot fix it.

### Regarding RAM usage
RAM usage as well as computation time heavily scales with available Heroes and Monsters. 
I recommend using a maximum of 16 heroes.  The calculator has a hard limit of 32 heroes, and will probably not work if more heroes are used.