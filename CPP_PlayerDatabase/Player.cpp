#include "Player.h"
#include <string.h>
#include <iostream>

using namespace std;

Player::Player(const char* _name, unsigned int highscore)
{
	strcpy_s(name, MaxNameLength, _name);
	this->highScore = highscore;
}

void Player::Draw()
{
	cout << name << ", " << highScore << endl;
}
