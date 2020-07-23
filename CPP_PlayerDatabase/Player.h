#pragma once
class Player
{
public:

	static const unsigned int MaxNameLength = 50;
	Player(const char* _name = "", unsigned int highscore = 0);

	void Draw();

private:
	char name[MaxNameLength] = {};
	unsigned int highScore = 0;
};

