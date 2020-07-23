#pragma once
#include <vector>
#include "player.h"

using std::vector;
using namespace std;

class Leaderboard
{
public:
	Leaderboard(unsigned int maxPlayers = 10);
	~Leaderboard();

	void Draw();

private:
	Player* playerList = nullptr;

	unsigned int maxPlayers = 0;
	unsigned int playersInUse = 0;
};

