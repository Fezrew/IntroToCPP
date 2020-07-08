#pragma once
#include "Entity.h"
//#define random

class Marine : public Entity
{
public:
	Marine();
	Marine(int health);
	~Marine();

	int attack() override;

#if random //true
	void isLegend();
	bool legendary = false;
private:
	int legendAttack = 0;
#endif
};

