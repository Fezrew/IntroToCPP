#pragma once
class Entity
{
public:
	Entity();
	~Entity();

	virtual int attack() 
	{
		return 0;
	}
	virtual void takeDamage(int damage)
	{
		return;
	}
	bool isAlive();
	

protected:
	int health;
	int maxHealth;
};

