#include "Zergling.h"
#include <random>
#include <time.h>
//#define random

Zergling::Zergling(int health) : Entity(health)
{
}

Zergling::Zergling()
{

}


Zergling::~Zergling()
{
}

int Zergling::attack()
{
#if random //true
	return rand() % 50 + 1;
#else
	return 10;
#endif
}

