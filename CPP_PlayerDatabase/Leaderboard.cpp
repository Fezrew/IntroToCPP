#include "Leaderboard.h"
#include <iostream>

using namespace std;


Leaderboard::Leaderboard(unsigned int _maxPlayers) : maxPlayers(_maxPlayers), playersInUse(0)
{
	if (maxPlayers == 0)
	{
		maxPlayers = 10;
	}

	if (maxPlayers > 100)
	{
		maxPlayers = 100;
	}

	playerList = new Player[maxPlayers];
}

Leaderboard::~Leaderboard()
{
	delete[] playerList;
}

void Leaderboard::Draw()
{
	cout << "===================================\n";
	cout << "==          Leaderboard          ==\n";
	cout << "===================================\n";

	if (!IsEmpty())
	{
		for (unsigned int i = 0; i < playersInUse; i++)
		{
			cout << i + 1 << "] ";
			playerList[i].Draw();
		}
	}
	else
	{
		cout << "... Empty ...\n";
	}
}

void Leaderboard::AddPlayer(const string& name, unsigned int score)
{
	AddPlayer(Player(name.c_str(), score));
}

void Leaderboard::AddPlayer(const Player& player)
{
	if (playersInUse < maxPlayers)
	{
		playerList[playersInUse] = player;
		playersInUse++;
	}
	else
	{
		throw exception("Out of bounds...Leaderboard full");
	}
}

void Leaderboard::Clear()
{
	playersInUse = 0;
}

Player& Leaderboard::operator[](unsigned int pos)
{
	if (pos > playersInUse)
	{
		throw out_of_range("Out of bounds");
	}
	else
	{
		return playerList[pos];
	}

}
