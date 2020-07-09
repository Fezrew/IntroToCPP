#include <iostream>
#include "TicTacToeConsole.h"

using namespace std;

namespace TicTacToe
{
	TicTacToeConsole::TicTacToeConsole() : ConsoleGame("Tic Tac Toe")
	{
	}

	void TicTacToeConsole::Init()
	{
		ConsoleGame::Init();

		cout << "Loading board please wait...\n";

		drawBoard();
		isGameRunning = true;
	}

	void TicTacToeConsole::Shutdown()
	{
		cout << "Closing rescources... Please wait....\n";
		ConsoleGame::Shutdown();
	}

	void TicTacToeConsole::Update()
	{
		askForPlayerInput();
	}

	void TicTacToeConsole::Draw()
	{
		drawBoard();
	}

	void TicTacToeConsole::askForPlayerInput()
	{
		string userInput;
		cout << "Enter command (Q)uit >";
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> userInput;

		if (userInput == "Q" || userInput == "q")
		{
			isGameRunning = false;
		}
	}

	void TicTacToeConsole::drawBoard()
	{
		cout << "Draw board" << endl;
	}
}