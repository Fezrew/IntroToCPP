#pragma once
#include <string>
#include "../CPPTicTacToe/Game.h"

using std::string;

namespace TicTacToe
{
	class ConsoleGame : public Game
	{
	protected:
		bool isGameRunning = false;
		string gameName;

	public:
		ConsoleGame(const char* gameName = "Game");

	protected:
		void Init() override;
		virtual void Shutdown() override;
		virtual bool IsGameRunning() override;
		virtual void Update() override;
		virtual void Draw() override;
	};
}
