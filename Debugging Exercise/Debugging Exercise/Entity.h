#pragma once

class Entity
{
public:
	Entity();
	~Entity();
	Entity(int h);

	virtual int attack() = 0;
	virtual void takeDamage(int damage);
	bool isAlive();
	int getHealth();
	int maxHealth;
	
private:
	int health;
};

