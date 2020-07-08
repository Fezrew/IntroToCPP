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

//If you want random health & damage, uncomment this define & all "#if random true" expressions in Main, Marine.cpp, and Zergling.cpp
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
	vector<Marine> squad;
	vector<Zergling> swarm;
	typedef vector<Zergling>::iterator ZergIter;

	const int squadSize = 10;
	const int swarmSize = 20;

	squad.reserve(squadSize);

	// Set up the Squad and the Swarm at their initial sizes listed above

#if random true

	srand(time(nullptr));

	for (size_t i = 0; i < squadSize; i++)
	{
		squad.push_back(Marine(rand() % 100 + 1));
	}

	for (size_t i = 0; i < swarmSize; i++)
	{
		swarm.push_back(Zergling(rand() % 50 + 1));
	}
#else
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

	cout << "A squad of marines approaches a swarm of Zerglings and opens fire! The Zerglings charge!\n";
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
					cout << "A marine fires for " << damage << " damage.\n";
					
					//Attack the first zergling
					swarm[0].takeDamage(damage);
					if (!swarm[0].isAlive()) // if the zergling dies, it is removed from the swarm
					{
						cout << "The zergling target dies\n\n";
						swarm.erase(swarm.begin());
					}
				}
			}
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
					cout << "A zergling attacks for " << damage << " damage.\n";
					squad[0].takeDamage(damage);
					if (!squad[0].isAlive())
					{
						cout << "The marine succumbs to his wounds.\n\n";
						squad.erase(squad.begin());
					}
				}
			}
		}
	}

	// Once one team is completely eliminated, the fight ends and one team wins
	cout << "The fight is over. ";
	if (marineAlive(squad))
	{
		cout << "The Marines win.\n";
	} else 
	{
		cout << "The Zerg win.\n";
	}
}
