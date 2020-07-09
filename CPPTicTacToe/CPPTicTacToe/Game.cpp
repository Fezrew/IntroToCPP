#include "Game.h"

namespace TicTacToe
{
	Game::Game()
	{
	}
	void Game::Run()
	{
		Init();

		while (IsGameRunning())
		{
			Update();
			Draw();
		}

		Shutdown();
	}
}