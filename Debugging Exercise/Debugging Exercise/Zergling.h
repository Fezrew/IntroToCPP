#pragma once
#include "Entity.h"

class Zergling : public Entity
{
public:
	Zergling();
	Zergling(int health);
	~Zergling();

	int attack() override;
};

