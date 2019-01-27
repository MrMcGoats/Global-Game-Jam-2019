#pragma once

#include "gameManager.hpp"


class MenuScreen : public GameScreen
{
public:
	MenuScreen();

	virtual void Start();
	virtual void Update(float dt);

	void toggleReadyLeft();
	void toggleReadyRight();
private:
	Actor *becky1;
	Actor *becky2;
	Actor *skelly1;
	Actor *skelly2;

	TextActor *leftReady;
	TextActor *rightReady;

	int leftSelect;
	int rightSelect;
	
};
