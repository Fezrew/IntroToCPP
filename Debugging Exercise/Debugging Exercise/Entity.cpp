#include "Entity.h"



Entity::Entity()
{
	health = 100;
}

Entity::~Entity()
{

}

Entity::Entity(int h)
{
	this->health = h;
}

void Entity::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}

bool Entity::isAlive()
{
	return health > 0;
}
