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

		DrawBoard();
		isGameRunning = true;
	}

	void TicTacToeConsole::Shutdown()
	{
		cout << "Closing rescources... Please wait....\n";
		ConsoleGame::Shutdown();
	}

	void TicTacToeConsole::Update()
	{
		AskForPlayerInput();
	}

	void TicTacToeConsole::Draw()
	{
		DrawBoard();
	}

	void TicTacToeConsole::InitialiseBoard()
	{
		for (int row = 0; row < BoardSize; row++)
		{
			for (int col = 0; col < BoardSize; col++)
			{
				BoardData[row][col] = 0;
			}
		}
	}

	void TicTacToeConsole::AskForPlayerInput()
	{
		string userInput;
		cout << "Enter command (Q)uit > ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> userInput;

		if (userInput == "Q" || userInput == "q")
		{
			isGameRunning = false;
		}
	}

	void TicTacToeConsole::DrawBoard()
	{
		system("cls");
		//cout << "Draw board" << endl;

		for (int row = 0; row < BoardSize; row++)
		{
			for (int col = 0; col < BoardSize; col++)
			{
				if (BoardData[row][col] == 1)
				{
					cout << "X";
				}
				else if (BoardData[row][col] == 2)
				{
					cout << "O";
				}
				else
				{
					cout << " ";
				}
				
				if (col < BoardSize - 1)
				{
					cout << " | ";
				}
				else
				{
					cout << endl;
				}
			}
			if (row < BoardSize - 1)
			{
				cout << "----------" << endl;
			}
			else
			{
				cout << endl;
			}
		}
	}
}