#pragma once
#include "ConsoleGame.h"

namespace TicTacToe
{
	constexpr unsigned int BoardSize = 3;

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
		unsigned char BoardData [BoardSize][BoardSize];
		unsigned char currentPlayer = 1;

		void InitialiseGame();
		void AskForPlayerInput();
		void DrawBoard();

		int getRow(int position);
		int getCol(int position);
	};
}
