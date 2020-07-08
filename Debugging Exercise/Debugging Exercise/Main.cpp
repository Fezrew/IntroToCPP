// A Debugging Exercise by Marc Chee (marcc@aie.edu.au)
// 18/12/2016

// Marines are trying to "de-bug" an area (haha . . . haha)
// However something's up with this code . . . figure out what's going wrong
// When you're finished, there should be no compiler errors or warnings
// The encounter should also run and finish correctly as per the rules in the comments

// In many cases there are differences between what's in otherwise identical sections
// for Marines and Zerglings. It's good to be able to tell what the differences are
// and why they might be important.

// What's efficient and inefficient? Why?
// What uses more memory and what doesn't? Why?

#include <iostream>
#include <vector>
#include "Marine.h"
#include "Zergling.h"
#include <time.h>
#include <Windows.h>

//If you want random health & damage (Despite true random always giving warnings), 
//uncomment this define & all "#if random true" expressions in Main, Marine.cpp, Marine.h and Zergling.cpp

//#define random

using std::vector;
using std::cout;
using std::endl;

// Is there a Marine Alive?
bool marineAlive(vector<Marine> squad)
{
	return !squad.empty();
}

// Is there a zergling Alive
bool zerglingAlive(vector<Zergling> swarm)
{
	return !swarm.empty();
}

int main()
{
	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	vector<Marine> squad;
	vector<Zergling> swarm;
	typedef vector<Zergling>::iterator ZergIter;

	// Set up the Squad and the Swarm at their initial sizes listed above

#if random //true

	srand(time(nullptr));
	const int squadSize = rand() % 31 + 15;
	const int swarmSize = rand() % 300 + 150;
	squad.reserve(squadSize);
	int legends = 0;

	for (size_t i = 0; i < squadSize; i++)
	{
		squad.push_back(Marine(rand() % 1101 + 700));
	}
	
	for (size_t i = 0; i < squadSize; i++)
	{
		if (squad[i].maxHealth > 1700)
		{
			squad[i].isLegend();
			legends++;
		}
		if (!squad[i].legendary)
		{
			if (rand() % 8 == 0)
			{
				squad[i].isLegend();
				legends++;
			}
		}
	}

	for (size_t i = 0; i < swarmSize; i++)
	{
		swarm.push_back(Zergling(rand() % 50 + 1));
	}

	int deadLegends = 0;
	int zergRush = 0;
#else
	const int squadSize = 10;
	const int swarmSize = 20;
	squad.reserve(squadSize);

	Marine m(50);
	for (size_t i = 0; i < squadSize; i++)
	{
		squad.push_back(m);
	}

	Zergling z(30);
	for (size_t i = 0; i < swarmSize; i++)
	{
		swarm.push_back(z);
	}
#endif
	int damageTaken = 0;
	int deadMarine = 0;
	int deadZerg = 0;

#if random //true
	cout << "A squad of " << squadSize << " marines with " << legends << " legends approaches a swarm of " << swarmSize << " Zerglings and opens fire! The Zerglings charge!\n";
#else
	cout << "A squad of " << squadSize << " marines approaches a swarm of " << swarmSize << " Zerglings and opens fire! The Zerglings charge!\n";
#endif

	// Attack each other until only one team is left alive
	while (marineAlive(squad) && zerglingAlive(swarm)) // If anyone is left alive to fight . . .
	{
		if (marineAlive(squad)) // if there's at least one marine alive
		{
			cout << "\n";

			for (size_t i = 0; i < squad.size(); i++) // go through the squad
			{
				if (!zerglingAlive(swarm))
				{
					break;
				}
				else
				{
					// each marine will attack the first zergling in the swarm
					int damage = squad[i].attack();
#if random //true
					if (squad[i].legendary)
					{
						cout << "\x1b[96mA legendary marine fires for " << damage << " exquisite damage.\x1b[0m\n";
					}
#else
					cout << "A marine fires for " << damage << " damage.\n";
#endif
					//Attack the first zergling
					swarm[0].takeDamage(damage);
					if (!swarm[0].isAlive()) // if the zergling dies, it is removed from the swarm
					{
#if random //true
						if (squad[i].legendary)
						{
							cout << "\x1b[96mA legendary has vanquised a foe\x1b[0m\n\n";
						}
#else
							cout << "The zergling target dies\n\n";
#endif
						swarm.erase(swarm.begin());
						deadZerg++;
					}
				}
			}
			cout << endl << deadZerg << " Zerglings have been purged. " << swarmSize - deadZerg << " remain.\n";
		}

		if (marineAlive(squad)) // if there's at least one marine alive
		{
			cout << "\n";
			for (size_t i = 0; i < swarm.size(); i++) // loop through zerglings+
			{
				if (!marineAlive(squad))
				{
					break;
				}
				else
				{
					int damage = swarm[i].attack();
#if random //true
					zergRush++;
#else
					cout << "A zergling attacks for " << damage << " damage.\n";
#endif
#if random //true
					if (squad[0].legendary)
					{
						squad[0].takeDamage(damage / 2);
					}
#else
						squad[0].takeDamage(damage);
#endif
					damageTaken += damage;
					if (!squad[0].isAlive())
					{
#if random //true
						cout << "\x1b[91m";
						if (squad[0].legendary)
						{
							legends--;
							deadLegends++;
							cout << "A legend has been attacked " << zergRush << " times by zerglings and sustained " << damageTaken << " damage before succumbing to his wounds.\n";
						}
						else
						{
							cout << "A marine has been attacked " << zergRush << " times by zerglings and took " << damageTaken << " damage before succumbing to his wounds.\n";
						}
						zergRush = 0;
						cout << "\x1b[0m";
#else
						cout << "\x1b[91mThe marine took " << damageTaken << " and succumbed to his wounds.\x1b[0m\n";
#endif
						squad.erase(squad.begin());
						damageTaken = 0;
						deadMarine++;
					}
				}
			}
#if random //true
			cout << "\n\x1b[92m" << deadMarine << " Marines have fallen, " << deadLegends << " of whom were legendary. " << squadSize - deadMarine << " Marines fight on.\x1b[0m\n";
#else
			cout << "\n\x1b[92m" << deadMarine << " Marines have fallen. " << squadSize - deadMarine << " fight on.\x1b[0m\n";
#endif
		}
	}

	// Once one team is completely eliminated, the fight ends and one team wins
	cout << "The fight is over. ";
	if (marineAlive(squad))
	{
#if random //true
		cout << "The " << squadSize - deadMarine - legends << " Marines and their " << legends << " surviving legends have won.\n";
#else
		cout << "The " << squadSize - deadMarine << " surviving Marines have won.\n";
#endif
	}
	else 
	{
		cout << "The " << swarmSize - deadZerg << " remaining Zerg win.\n";
	}
}
