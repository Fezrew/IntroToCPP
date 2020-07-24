#include "PlayerDatabase.h"
#include "iostreamUtils.h"
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
	if (menuOption == "m")
	{
		modifyPlayer();
	}
	else if (menuOption == "s")
	{
		Sort();
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
	cout << "S)ort Leaderboard\n";
	cout << "C)lear Leaderboard\n";
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
			leaderboard.AddPlayer(p);
		}
	}
	else
	{
		cout << "Leaderboard is full\n";
		getchar();
	}
}

void PlayerDatabase::modifyPlayer()
{
	cinClear();
	cout << "Select player number to modify\n> ";
	unsigned int pos;
	cin >> pos;

	if (pos < leaderboard.PlayersInUse())
	{
		leaderboard[pos].LoadFromConsole();
	}
}

void PlayerDatabase::Sort()
{
	sort(leaderboard.begin(), leaderboard.end());
}

string PlayerDatabase::getMenuOption()
{
	string userInput;
	cinClear(); //Clear pending input
	cin >> userInput;

	transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
	return userInput;
}

