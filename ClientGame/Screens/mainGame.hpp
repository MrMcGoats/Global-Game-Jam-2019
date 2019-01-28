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

	int curr_note;

	TextActor *rightScoreText;
	TextActor *leftScoreText;

	int leftHit;
	int rightHit;

	bool leftSmash;
	bool rightSmash;

	int leftScore;
	int rightScore;

	int leftMul;
	int rightMul;

	int song1[180];

	void genSongs();
	void checkLeftHit(Vector2);
	void checkRightHit(Vector2);
};
