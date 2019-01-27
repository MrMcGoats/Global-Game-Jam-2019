
#include "stdafx.h"
//#include "gameManager.hpp"
#include "mainGame.hpp"

void MainGameScreen::genSongs()
{
	srand(time(NULL));
	for(int i=0;i<180;i++)
	{
		if(i%2==0) song1[i]=-1;
		else song1[i]=rand()%6;
	}
}

MainGameScreen::MainGameScreen()
{
}

void MainGameScreen::Start()
{
	this->genSongs();

	player1=new Actor();
	player1Arm=new Actor();
	player2=new Actor();
	player2Arm=new Actor();

	for(int i=0;i<14;i++)
	{
		buttons[i]=new Actor();
		buttons[i]->SetDrawShape(ADS_Circle);
		buttons[i]->SetColor(0,0,0);
		buttons[i]->SetSize(1.3);
	}

	buttons[0]->SetPosition(3,-2);
	for(int i=1;i<5;i++)
		buttons[i]->SetPosition((3+i*1.4),2.5);
	buttons[5]->SetPosition(10,-2);

	buttons[6]->SetPosition(6.5,-5);
	buttons[6]->SetSize(3);
	buttons[13]->SetPosition(-6.5,-5);
	buttons[13]->SetSize(3);

	buttons[7]->SetPosition(-3,-2);
	for(int i=8;i<12;i++)
		buttons[i]->SetPosition(-(1+i*1.4)+7.8,2.5);
	buttons[12]->SetPosition(-10,-2);

	buttons[13]->LoadSpriteFrames("Resources/Images/Skelly/button/skelly_button_001.png");

	for(int i=0;i<14;i++)
	{
		theWorld.Add(buttons[i],2);
		_objects.push_back(buttons[i]);
	}

	player1->SetDrawShape(ADS_Square);
	player1->SetColor(1,1,1);
	player1->SetPosition(6.5,-3);
	player1->SetSize(5,6);
	player1Arm->SetDrawShape(ADS_Square);
	player1Arm->SetColor(1,1,1);
	player1Arm->SetPosition(6.5,-1);
	player1Arm->SetSize(2,4);

	player1->LoadSpriteFrames(theGameManager.rightSprite);
	player1Arm->LoadSpriteFrames("Resources/Images/becky_arm_vertical.png");

	theWorld.Add(player1);
	theWorld.Add(player1Arm,3);

	_objects.push_back(player1);
	_objects.push_back(player1Arm);

	player2->SetDrawShape(ADS_Square);
	player2->SetColor(1,1,1);
	player2->SetPosition(-6.5,-3);
	player2->SetSize(5,6);
	player2Arm->SetDrawShape(ADS_Square);
	player2Arm->SetColor(1,1,1);
	player2Arm->SetPosition(-6.5,-1);
	player2Arm->SetSize(2,4);

	player2->LoadSpriteFrames(theGameManager.leftSprite);

	theWorld.Add(player2,1);
	theWorld.Add(player2Arm,3);

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

	static int frames=0;
	if(frames>5)
	{
		player1->SetSpriteFrame((player1->GetSpriteFrame()+1)%2);
		player2->SetSpriteFrame((player2->GetSpriteFrame()+1)%3);
		frames=0;
	}
	frames++;

	//Update position based on thumbstick
	Vec2i movementL = theController.GetLeftThumbstick(); //returns a 2d integer vector
														 // where each component ranges
														 // from -32768 to 32768
	
	Vec2i movementR = theController.GetRightThumbstick();

	Vector2 position;
	if (movementR.X)
	{
		// Scale the thumbstick down to reasonable proportions and make the range of
		//  movement 3
		position.X = 3.0f * ((float)movementR.X / 32768.0f)+7;
	}
	else
	{
		position.X = 6.5f;
	}
	if (movementR.Y)
	{
		position.Y = 3.0f * ((float)movementR.Y / 32768.0f)-1;
	}
	else
	{
		position.Y = -1.0f;
	}

	
	Vector2 position2;
	if (movementL.X)
	{
		// Scale the thumbstick down to reasonable proportions and make the range of
		//  movement 3
		position2.X = 3.0f * ((float)movementL.X / 32768.0f)-7;
	}
	else
	{
		position2.X = -6.5f;
	}
	if (movementL.Y)
	{
		position2.Y = 3.0f * ((float)movementL.Y / 32768.0f)-1;
	}
	else
	{
		position2.Y = -1.0f;
	}

	player2Arm->SetPosition(position2);
	player1Arm->SetPosition(position);
}
