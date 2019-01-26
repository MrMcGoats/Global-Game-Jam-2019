
#include "stdafx.h"
//#include "gameManager.hpp"
#include "mainGame.hpp"

MainGameScreen::MainGameScreen()
{
}

void MainGameScreen::Start()
{
	player1=new Actor();
	player1Arm=new Actor();
	player2=new Actor();
	player2Arm=new Actor();

	for(int i=0;i<14;i++)
	{
		buttons[i]=new Actor();
		buttons[i]->SetDrawShape(ADS_Circle);
		buttons[i]->SetColor(i*0.1,i*0.2,i*0.3);
		buttons[i]->SetPosition(i,i);
		theWorld.Add(buttons[i]);
		_objects.push_back(buttons[i]);
	}

	player1->SetDrawShape(ADS_Square);
	player1->SetColor(1,0,1);
	player1->SetPosition(7,-3);
	player1->SetSize(2,3);
	player1Arm->SetDrawShape(ADS_Square);
	player1Arm->SetColor(1,0,1);
	player1Arm->SetPosition(7,-1);

	theWorld.Add(player1);
	theWorld.Add(player1Arm);

	_objects.push_back(player1);
	_objects.push_back(player1Arm);

	player2->SetDrawShape(ADS_Square);
	player2->SetColor(1,0,0);
	player2->SetPosition(-7,-3);
	player2->SetSize(2,3);
	player2Arm->SetDrawShape(ADS_Square);
	player2Arm->SetColor(1,0,0);
	player2Arm->SetPosition(-7,-1);

	theWorld.Add(player2);
	theWorld.Add(player2Arm);

	_objects.push_back(player2);
	_objects.push_back(player2Arm);
}

void MainGameScreen::Update(float dt)
{
	//If there's no controller connected, this is kind of irrelevant.
	//  (Note that you can still query the controller object if the hardware
	//  isn't connected, but it will return default data (no buttons down,
	//  thumbsticks both at center, triggers untouched, no vibration.)
	if (!theController.IsConnected())
		return;

	//Update position based on thumbstick
	Vec2i movementL = theController.GetLeftThumbstick(); //returns a 2d integer vector
														 // where each component ranges
														 // from -32768 to 32768
	
	Vec2i movementR = theController.GetRightThumbstick();
}
