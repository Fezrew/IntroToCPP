#include "PlayerDatabase.h"
#include "iostreamUtils.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void PlayerDatabase::Init()
{
	//Load leaderboard from file
	try
	{
		leaderboard.AddPlayer("Me", 100);
		leaderboard.AddPlayer("You", 50);

		//Sort players by highscore
		leaderboard.SortByHighscore();
	}
	catch(exception & err)
	{
		cout << "Error: " << err.what() << endl;
		getchar();
	}
}

void PlayerDatabase::Shutdown()
{
	//Save the leaderboard to file
}

bool PlayerDatabase::IsGameRunning()
{
	return isGameRunning;
}

void PlayerDatabase::Update()
{
	displayMenu();
	string menuOption = getMenuOption();

	if (menuOption == "a")
	{
		addNewPlayer();
	}
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
	else if (menuOption == "h")
	{
		leaderboard.SortByHighscore();
	}
	else if (menuOption == "n")
	{
		leaderboard.SortByName();
	}
	else if (menuOption == "c")
	{
		leaderboard.Clear();
	}
	else if (menuOption == "q")
	{
		isGameRunning = false;
	}
}

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
	cout << "H)ighscore\n";
	cout << "N)ame\n\n";

	cout << "Q)uit\n";
	cout << "------------------\n";
	cout << ">";
}

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
		getchar();
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
		leaderboard[pos -1].LoadFromConsole();
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

string PlayerDatabase::getMenuOption()
{
	string userInput;
	cinClear(); //Clear pending input
	cin >> userInput;

	transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
	return userInput;
}

