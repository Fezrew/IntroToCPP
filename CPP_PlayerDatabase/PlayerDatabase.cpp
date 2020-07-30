#include "PlayerDatabase.h"
#include "iostreamUtils.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

#pragma region Game Management

void PlayerDatabase::Init()
{
	//Load leaderboard from file
	try
	{
		leaderboard.Load(LeaderboardFilename);

		//Sort players by highscore
		leaderboard.SortByPoints();
	}
	catch (exception & err)
	{
		cout << "Error: " << err.what() << endl;
		int ch = getchar();
	}
}

void PlayerDatabase::Shutdown()
{
	//Save the leaderboard to file
	
	string quitOption;

	while (quitOption != "y" && quitOption != "n")
	{
		cout << "Save? Y/N\n> ";
		quitOption = getMenuOption();
		                        
		if (quitOption == "y")
		{
			leaderboard.Save(LeaderboardFilename);
		}
	}
}

bool PlayerDatabase::IsGameRunning()
{
	return isGameRunning;
}

void PlayerDatabase::Update()
{
	displayMenu();
	string menuOption = getMenuOption();

	//If Adding player
	if (menuOption == "a")
	{
		addNewPlayer();
	}

	//If Modifying player
	else if (menuOption == "m")
	{
		cout << "Search by player (I)ndex or (N)ame?\n> ";
		string modifyOption = getMenuOption();

		if (modifyOption == "i")
		{
			modifyPlayerByIndex();
		}
		else if (modifyOption == "n")
		{
			modifyPlayerByName();
		}
	}

	//If sorting players
	else if (menuOption == "p")
	{
		leaderboard.SortByPoints();
	}
	else if (menuOption == "n")
	{
		leaderboard.SortByName();
	}

	//Clear the leaderboard
	else if (menuOption == "c")
	{
		leaderboard.Clear();
	}

	//Save the leaderboard
	else if (menuOption == "s")
	{
		if (!leaderboard.Save(LeaderboardFilename))
		{
			cerr << "Error saving file: " << LeaderboardFilename << endl;
			int ch = getchar();
		}
	}

	//Load the leaderboard
	else if (menuOption == "l")
	{
		if (!leaderboard.Load(LeaderboardFilename))
		{
			cerr << "Error loading file: " << LeaderboardFilename << endl;
			int ch = getchar();
		}
		else
		{
			leaderboard.SortByPoints();
		}
	}

	//What does hack do???
	else if (menuOption == "h")
	{
		hackLeaderboard();
	}

	//Close the application
	else if (menuOption == "q")
	{
		isGameRunning = false;
	}
}
#pragma endregion

#pragma region Text Management

void PlayerDatabase::Draw()
{
	system("cls");
	leaderboard.Draw();

}

void PlayerDatabase::displayMenu()
{
	cout << "\n=== Menu ===\n";
	cout << "A)dd Player\n";
	cout << "M)odify Player\n";
	cout << "C)lear Leaderboard\n\n";

	cout << "Sort Leaderboard by:\n";
	cout << "P)oints\n";
	cout << "N)ame\n\n";

	cout << "S)ave\n";
	cout << "L)oad\n";
	cout << "H)ack\n";
	cout << "Q)uit\n";
	cout << "------------------\n";
	cout << "> ";
}
#pragma endregion

#pragma region Database Management

void PlayerDatabase::addNewPlayer()
{
	if (!leaderboard.IsFull())
	{
		Player p;
		if (p.LoadFromConsole())
		{
			//Add a player to the leaderboard
			leaderboard.AddPlayer(p);
		}
	}
	else
	{
		cout << "Leaderboard is full\n";
		int ch = getchar();
	}
}

void PlayerDatabase::modifyPlayerByIndex()
{
	cinClear();
	cout << "Select player index to modify\n> ";
	unsigned int pos;
	cin >> pos;

	if (pos <= leaderboard.PlayersInUse())
	{
		leaderboard[pos - 1].LoadFromConsole();
	}
}

void PlayerDatabase::modifyPlayerByName()
{
	cinClear();
	cout << "Select name of player to modify\n> ";
	string name;
	cin >> name;

	//Perform a binary search for the player and return it's postition to the array
	unsigned int pos = 0;

	if (leaderboard.Search(name, pos))
	{
		leaderboard[pos].LoadFromConsole();
	}
}

void PlayerDatabase::hackLeaderboard()
{
	cinClear();

	cout << "Select name of player to modify\n> ";
	string name;
	cin >> name;

	fstream f(LeaderboardFilename, ios_base::in | ios_base::out | ios_base::binary);
	if (f.good())
	{
		//Read past header info (maxplayers/playersInUse)
		unsigned int maxPlayers, playersInUse;
		
		f.read((char*)&maxPlayers, sizeof(maxPlayers));
		f.read((char*)&playersInUse, sizeof(playersInUse));

		//Read Players one at a time and test their names
		Player p;
		while (!f.eof())
		{
			f.read((char*)& p, sizeof(Player));

			if (name == p.GetName())
			{
				cout << "Found player: " << name << endl;
				p.Draw();
				f.close();
				return;
			}
		}

		f.close();
	}
	else
	{
		cerr << "Failed to find player: " << name << endl;
	}

	cinClear();
	int ch = getchar();
}

string PlayerDatabase::getMenuOption()
{
	string userInput;
	cinClear(); //Clear pending input
	cin >> userInput;


	transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
	return userInput;
}
#pragma endregion



