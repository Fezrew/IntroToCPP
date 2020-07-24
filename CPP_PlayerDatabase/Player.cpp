#include "Player.h"
#include "iostreamUtils.h"
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
	cout << highScore << ", " << name << endl;
}

bool Player::LoadFromConsole()
{
	cinClear(); // Clear pending input

	cout << "Enter player name\n> ";
	cin >> name;
	cout << "Enter player score\n> ";
	cin >> highScore;

	if (highScore > MaxScore)
	{
		highScore = MaxScore;
	}
	else
	{

	}
	return true;
}

bool Player::operator<(const Player& other)
{
	return (highScore < other.highScore);
}
