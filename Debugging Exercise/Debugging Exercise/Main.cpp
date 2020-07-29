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

#define random

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

#pragma region Set-up


	vector<Marine> squad;
	vector<Zergling> swarm;
	typedef vector<Zergling>::iterator ZergIter;
	int damageTaken = 0;
	int deadMarine = 0;
	int deadZerg = 0;

	// Set up the Squad and the Swarm at their initial sizes listed above

#if random true

	srand((unsigned int)time(nullptr));
	const int squadSize = rand() % 16 + 30;				//30 - 45
		const int swarmSize = rand() % 261 + 260;		//260 - 520
	squad.reserve(squadSize);
	int legends = 0;
	int deadLegends = 0;
	int zergRush = 0;
	int chipDamage = 0;

	for (size_t i = 0; i < squadSize; i++)
	{
		squad.push_back(Marine(rand() % 1101 + 900));
	}
	
	for (size_t i = 0; i < squadSize; i++)
	{
		if (squad[i].maxHealth > 1850)
		{
			squad[i].isLegend();
			legends++;
		}
		if (!squad[i].legendary)
		{
			if (rand() % 6 == 0)
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

#if random true
	cout << "A squad of " << squadSize << " marines with " << legends << " legends approaches a swarm of " << swarmSize << " Zerglings and opens fire! The Zerglings charge!\n";
#else
	cout << "A squad of " << squadSize << " marines approaches a swarm of " << swarmSize << " Zerglings and opens fire! The Zerglings charge!\n";
#endif
#pragma endregion

	// Attack each other until only one team is left alive
	while (marineAlive(squad) && zerglingAlive(swarm)) // If anyone is left alive to fight . . .
	{
#pragma region Marine Attacks

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
#if random true
					if (squad[i].legendary)
					{
						cout << "\x1b[96mA legendary marine fires for " << damage << " exquisite damage.\x1b[0m\n";
						chipDamage = damage - swarm[0].getHealth();
					}
					else
					{
						cout << "A marine fires for " << damage << " damage.\n";
					}
#endif
					//Attack the first zergling
					swarm[0].takeDamage(damage);
					if (!swarm[0].isAlive()) // if the zergling dies, it is removed from the swarm
					{
#if random true
						if (squad[i].legendary)
						{
							int chipStored = 0;
							int nowDead = 1;
							
							for (nowDead; nowDead > 0; nowDead--)
							{

								if (zerglingAlive(swarm))
								{
									chipStored = chipDamage - swarm[0].getHealth();
									swarm[0].takeDamage(chipDamage);
									chipDamage = chipStored;
								}
								
								if (!zerglingAlive(swarm))
								{
									nowDead = 0;
								}
								else if (!swarm[0].isAlive())
								{
									nowDead++;
									swarm.erase(swarm.begin());
									deadZerg++;
									cout << "\x1b[96mA legendary has vanquised a foe\x1b[0m\n";
								}
							}
							cout << endl;
						}
						else
						{
							cout << "The zergling target dies\n\n";
							swarm.erase(swarm.begin());
							deadZerg++;
						}
#endif
					}
				}
			}
			cout << endl << deadZerg << " Zerglings have been purged. " << swarmSize - deadZerg << " remain.\n";
		}
#pragma endregion

#pragma region Zergling Attack

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
#if random true
					zergRush++;
#else
					cout << "A zergling attacks for " << damage << " damage.\n";
#endif
#if random true
					if (squad[0].legendary)
					{
						squad[0].takeDamage(damage / 3);
					}
					else
					{
						squad[0].takeDamage(damage);
					}
#endif
					damageTaken += damage;
					if (!squad[0].isAlive())
					{
#if random true
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
#if random true
			cout << "\n\x1b[92m" << deadMarine << " Marines have fallen, " << deadLegends << " of whom were legendary. " << squadSize - deadMarine << " Marines fight on.\x1b[0m\n";
#else
			cout << "\n\x1b[92m" << deadMarine << " Marines have fallen. " << squadSize - deadMarine << " fight on.\x1b[0m\n";
#endif
		}
	}
#pragma endregion

	// Once one team is completely eliminated, the fight ends and one team wins
	cout << "The fight is over. ";
	if (marineAlive(squad))
	{
#if random true
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
