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

int Marine::attack()
{
#if random //true
	return rand() % 50 +1;
#else
	return 10;
#endif
}

