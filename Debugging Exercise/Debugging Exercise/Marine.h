#pragma once
#include "Entity.h"

class Marine : public Entity
{
public:
	Marine();
	Marine(int health);
	~Marine();

	int attack() override;

};

