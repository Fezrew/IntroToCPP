#include "PlayerDatabase.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void PlayerDatabase::Init()
{
	//Load leaderboard from file
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
	string menuOption = getMenuOption();

	if (menuOption == "n")
	{
		cout << "New Player\n";
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
}

string PlayerDatabase::getMenuOption()
{
	cout << "\n=== Menu ===\n";
	cout << "Q)uit\n";
	cout << "------------------\n";
	cout << ">";

	string userInput;
	cin.ignore(cin.rdbuf()->in_avail()); // Clear pending input
	cin >> userInput;

	transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
	return userInput;
}

