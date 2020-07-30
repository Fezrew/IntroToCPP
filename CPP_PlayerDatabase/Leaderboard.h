#pragma once
#include <vector>
#include "player.h"
#include <string>

using std::vector;
using namespace std;

class Leaderboard
{
#pragma region public
public:
	const unsigned int MaxLeaderboardSize = 1000;

	Leaderboard(unsigned int maxPlayers = 10);
	~Leaderboard();

	bool IsEmpty() const { return playersInUse == 0; }
	bool IsFull() const { return playersInUse >= maxPlayers; }

	unsigned int PlayersInUse() const { return playersInUse; }
	unsigned int MaxPlayers() const { return maxPlayers; }

	void Clear();
	void Draw();
	void SortByPoints();
	void SortByName();
	void AddPlayer(const string& name, unsigned int score);
	void AddPlayer(const Player& player);

	//Binary search the collection and updates pos when true(When it finds the position)
	bool Search(const string& name, unsigned int& posFound);
	bool Load(const char* filename);
	bool Save(const char* filename);
	
	Player& operator [](unsigned int pos);

	const Player* begin() const { return playerList; }
	const Player* end() const { return playerList + playersInUse; }
#pragma endregion

#pragma region private
private:
	Player* playerList = nullptr;

	unsigned int maxPlayers = 0;
	unsigned int playersInUse = 0;
#pragma endregion
};

