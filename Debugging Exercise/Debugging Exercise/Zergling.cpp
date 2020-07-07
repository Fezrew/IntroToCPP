#include "Zergling.h"



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
	return 10;
}

