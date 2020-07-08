#include "Marine.h"
#include <random>
#include <time.h>
//#define random



Marine::Marine(int health) : Entity(health)
{
	
}

Marine::Marine()
{

}


Marine::~Marine()
{
}

#if random //true
void Marine::isLegend()
{
	legendAttack = rand() % 15 + 10;
	legendary = true;
}
#endif

int Marine::attack()
{
#if random //true
	return rand() % (26 + legendAttack) + 25 + legendAttack;
#else
	return 10;
#endif
}

