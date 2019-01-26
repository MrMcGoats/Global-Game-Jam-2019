#pragma once

#include "gameManager.hpp"


class MainGameScreen : public GameScreen
{
public:
	MainGameScreen();

	virtual void Start();
	virtual void Update(float dt);

private:
	Actor *player1;
	Actor *player1Arm;
	Actor *player2;
	Actor *player2Arm;
	Actor *buttons[14];
};
