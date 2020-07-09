#include <iostream>
#include "ConsoleGame.h"


using namespace std;

namespace TicTacToe
{
#pragma warning (push)
#pragma warning (disable: 6031)


	ConsoleGame::ConsoleGame(const char* gameName)
	{
		this->gameName = gameName;
	}

	void ConsoleGame::Init()
	{
		cout << "====================\n";
		cout << "Welcome to " << gameName << endl;
		cout << "====================\n";
		cout << "Press any key to start...\n\n";
		getchar();
	}

	void ConsoleGame::Shutdown()
	{
		cout << endl;
		cout << "====================\n";
		cout << "Thanks for playing " << gameName << endl;
		cout << "====================\n";
		getchar();
	}

	bool ConsoleGame::IsGameRunning()
	{
		return isGameRunning;
	}

	void ConsoleGame::Update()
	{

	}

	void ConsoleGame::Draw()
	{

	}

#pragma warning (pop)
}