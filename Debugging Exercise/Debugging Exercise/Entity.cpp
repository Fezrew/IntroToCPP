#include "Entity.h"



Entity::Entity()
{
	health = 100;
	maxHealth = 100;
}


Entity::~Entity()
{

}

bool Entity::isAlive()
{
	return health == 0;
}
