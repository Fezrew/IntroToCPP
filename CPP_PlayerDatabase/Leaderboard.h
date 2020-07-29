#pragma once
#include <vector>
#include "player.h"
#include <string>

using std::vector;
using namespace std;

class Leaderboard
{
public:
	Leaderboard(unsigned int maxPlayers = 10);
	~Leaderboard();

	bool IsEmpty() const { return playersInUse == 0; }
	bool IsFull() const { return playersInUse >= maxPlayers; }

	unsigned int PlayersInUse() const { return playersInUse; }
	unsigned int MaxPlayers() const { return maxPlayers; }

	void Clear();
	void Draw();
	void SortByHighscore();
	void SortByName();
	void AddPlayer(const string& name, unsigned int score);
	void AddPlayer(const Player& player);
	
	Player& operator [](unsigned int pos);

	const Player* begin() const { return playerList; }
	const Player* end() const { return playerList + playersInUse; }

private:
	Player* playerList = nullptr;

	unsigned int maxPlayers = 0;
	unsigned int playersInUse = 0;
};

