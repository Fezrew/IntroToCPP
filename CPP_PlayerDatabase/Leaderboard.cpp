#include "Leaderboard.h"
#include <iostream>
#include <algorithm>

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

bool comparePlayerScores(const Player& lhs, const Player& rhs)
{
	return lhs.GetHighScore() > rhs.GetHighScore();
}


void Leaderboard::SortByHighscore()
{
	//sort(playerList, playerList + playersInUse);

	sort(playerList, playerList + playersInUse, comparePlayerScores);
}

bool comparePlayerNames(const Player& lhs, const Player& rhs)
{
	
	return (strcmp(lhs.GetName(), rhs.GetName()) < 0);
}

void Leaderboard::SortByName()
{
	sort(playerList, playerList + playersInUse, comparePlayerNames);
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

bool Leaderboard::Search(const string& name, unsigned int& posFound)
{
	//Sort collection before beginning binary search
	SortByName();

	unsigned int l = 0;
	unsigned int r = playersInUse - 1;
	unsigned int m;

	while (l <= r)
	{
		m = (l + r) / 2;

		if (name == playerList[m].GetName())
		{
			posFound = m;
			return true;
		}
		else if (name < playerList[m].GetName())
		{
			r = m - 1;
		}
		else if (name > playerList[m].GetName())
		{
			l = m + 1;
		}
	}

	return false;
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
