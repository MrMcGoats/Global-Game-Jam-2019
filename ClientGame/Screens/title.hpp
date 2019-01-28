#include "gameManager.hpp"

class TitleScreen: public GameScreen
{
	public:
		TitleScreen();

		virtual void Start();
		virtual void Update(float dt);

};
