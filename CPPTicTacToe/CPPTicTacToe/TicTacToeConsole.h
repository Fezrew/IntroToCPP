#pragma once
#include "ConsoleGame.h"

namespace TicTacToe
{
	class TicTacToeConsole : public ConsoleGame
	{
	public:
		TicTacToeConsole();

	protected:
		void Init() override;
		void Shutdown() override;
		
		void Update() override;
		void Draw() override;

	private:
		void askForPlayerInput();
		void drawBoard();
	};
}
