namespace TicTacToe
{
	class Game
	{

	public:
		Game();

		void Run();

	protected:
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual bool IsGameRunning() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}