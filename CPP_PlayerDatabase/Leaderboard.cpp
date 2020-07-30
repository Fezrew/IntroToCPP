#include "Leaderboard.h"
#include <iostream>
#include <algorithm>
#include <fstream>

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

#pragma region AddPlayer

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
#pragma endregion

#pragma region Leaderboard Management

bool comparePlayerScores(const Player& lhs, const Player& rhs)
{
	return lhs.GetHighScore() > rhs.GetHighScore();
}

void Leaderboard::SortByPoints()
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

void Leaderboard::Clear()
{
	playersInUse = 0;
}

void Leaderboard::Hack()
{

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

#pragma endregion

#pragma region Save/Load

bool Leaderboard::Load(const char* filename)
{
	ifstream fin(filename, ios_base::in | ios_base::binary);

	if (fin.good())
	{
		//Read the max players and reallocate the playersList to meet that amount
		unsigned int maxPlayers;
		fin.read((char*)&maxPlayers, sizeof(unsigned int));

		if (maxPlayers > MaxLeaderboardSize)
		{
			cerr << "Leaderboard:: Invalid file format. Player limit is too high\n";
			fin.close();
			return false;
		}

		//Reallocate playerlist if it holds a different size than the files
		if (this->maxPlayers != maxPlayers)
		{
			this->maxPlayers;
			delete[] this->playerList;
			this->playerList = new Player[maxPlayers];
		}

		//Read players in use
		unsigned int playersInUse;
		fin.read((char*)&playersInUse, sizeof(unsigned int));

		if (playersInUse > maxPlayers)
		{
			cerr << "Leaderboard:: Invalid file format. Player count is too high\n";
			fin.close();
			return false;
		}

		this->playersInUse = playersInUse;

		//Read the array of players
		fin.read((char*)playerList, (streamsize)(sizeof(Player) * playersInUse));

		fin.close();
		return true;
	}

	return false;
}

bool Leaderboard::Save(const char* filename)
{
	ofstream fout(filename, ios_base::out | ios_base::binary);

	if (fout.good())
	{
		//Write maxPlayers to file
		fout.write((const char*)&maxPlayers, sizeof(maxPlayers));

		//Write playersInUse to file
		fout.write((const char*)&playersInUse, sizeof(playersInUse));

		//Write our playerList array
		fout.write((const char*)playerList, (streamsize)(sizeof(Player) * playersInUse));

		fout.close();
		return true;
	}

	return false;
}
#pragma endregion

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
