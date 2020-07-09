#include "Entity.h"



Entity::Entity()
{
	maxHealth = 100;
	health = maxHealth;
}

Entity::~Entity()
{

}

Entity::Entity(int h)
{
	this->maxHealth = h;
	health = maxHealth;
}

void Entity::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}

int Entity::getHealth()
{
	return health;
}

bool Entity::isAlive()
{
	return health > 0;
}
