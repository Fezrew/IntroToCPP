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

	void TicTacToeConsole::InitialiseGame()
	{
		currentPlayer = 1;
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
		cout << "Player " << (int)currentPlayer << "'s turn\n";
		cout << "Enter command\n";
		cout << "(Numpad 1-9) Enter Tile\n";
		cout << "(R)estart\n";
		cout << "(Q)uit\n";

		char userInput;
		cin.ignore(cin.rdbuf()->in_avail());
		cin.get(userInput);

		if (userInput == 'Q' || userInput == 'q')
		{
			isGameRunning = false;
		}
		else if (userInput == 'R' || userInput == 'r')
		{
			InitialiseGame();
		}
		else
		{
			try
			{
				
				int position = userInput - '0'; // converting a char (0-9) to an int

				if ((position >= 1) && (position <= 9))
				{
					int row = getRow(position);
					int col = getCol(position);

					//Update the board to have the current player's piece
					BoardData[row][col] = currentPlayer;

					//Update the current player
					if (currentPlayer == 1)
					{
						currentPlayer = 2;
					}
					else if(currentPlayer == 2)
					{
						currentPlayer = 1;
					}
				}
			}
			catch (...)
			{
				cout << "Invalid input, try again...\n";
			}
		}
	}

	void TicTacToeConsole::DrawBoard()
	{
		system("cls");

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
	int TicTacToeConsole::getRow(int position)
	{
		return (BoardSize - 1) - ((position-1) / BoardSize);
	}
	int TicTacToeConsole::getCol(int position)
	{
		return (position -1 ) % BoardSize;
	}
}