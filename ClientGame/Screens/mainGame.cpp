
#include "stdafx.h"
//#include "gameManager.hpp"
#include "mainGame.hpp"

void MainGameScreen::genSongs()
{
	srand(time(NULL));
	for(int i=0;i<178;i++)
	{
		if(i%2==0) song1[i]=-1;
		else song1[i]=rand()%6;
	}
	song1[178]=-1;
	song1[179]=-1;
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

	rightScoreText=new TextActor("Score12");
	leftScoreText=new TextActor("Score12");

	rightScoreText->SetPosition(7,7);
	leftScoreText->SetPosition(-7,7);

	rightScoreText->SetColor(1,1,1);
	leftScoreText->SetColor(1,1,1);

	_objects.push_back(rightScoreText);
	_objects.push_back(leftScoreText);

	theWorld.Add(rightScoreText);
	theWorld.Add(leftScoreText);

	for(int i=0;i<14;i++)
	{
		buttons[i]=new Actor();
		buttons[i]->SetDrawShape(ADS_Square);
		buttons[i]->LoadSpriteFrames("Resources/Images/small_button.png");
		buttons[i]->SetColor(0.5,0.5,0.5);
		buttons[i]->SetSize(1.3);
	}

	buttons[0]->SetPosition(3,-2);
	for(int i=1;i<5;i++)
		buttons[i]->SetPosition((3+i*1.4),2.5);
	buttons[5]->SetPosition(10,-2);

	buttons[6]->SetPosition(6.5,-5);
	buttons[6]->SetSize(0);
	buttons[13]->SetPosition(-6.5,-5);
	buttons[13]->SetSize(0);

	buttons[7]->SetPosition(-3,-2);
	for(int i=8;i<12;i++)
		buttons[i]->SetPosition(-(1+i*1.4)+7.8,2.5);
	buttons[12]->SetPosition(-10,-2);

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

	if(theGameManager.rightSprite==0)
	{
		player1->LoadSpriteFrames("Resources/Images/becky_btn/becky_btn_001.png");
		player1Arm->LoadSpriteFrames("Resources/Images/becky_arm_vertical.png");
	} else if(theGameManager.rightSprite==1)
	{
		player1->LoadSpriteFrames("Resources/Images/Skelly/headbob_btn/skelly_bob_001.png");
		player1Arm->LoadSpriteFrames("Resources/Images/Skelly/Arms/Skelly_arms.png");
	}

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

	if(theGameManager.leftSprite==0)
	{
		player2->LoadSpriteFrames("Resources/Images/becky_alt_btn/becky_alt_btn_001.png");
		player2Arm->LoadSpriteFrames("Resources/Images/becky_alt_arms.png");
	} else if(theGameManager.leftSprite==1)
	{
		player2->LoadSpriteFrames("Resources/Images/Skelly_alt/headbob_btn/skelly_alt_btn_001.png");
		player2Arm->LoadSpriteFrames("Resources/Images/Skelly_alt/Arms/Skelly_alt_arms.png");
	}

	theWorld.Add(player2,1);
	theWorld.Add(player2Arm,3);

	_objects.push_back(player2);
	_objects.push_back(player2Arm);

	rightHit=-1;
	leftHit=-1;
	rightScore=0;
	leftScore=0;
	rightMul=1;
	leftMul=1;

	curr_note=0;
}

void MainGameScreen::Update(float dt)
{
	static int frames=0;
	static int leftFuckFrames=0;
	static int rightFuckFrames=0;

	//If there's no controller connected, this is kind of irrelevant.
	//  (Note that you can still query the controller object if the hardware
	//  isn't connected, but it will return default data (no buttons down,
	//  thumbsticks both at center, triggers untouched, no vibration.)
	if (!theController.IsConnected())
		return;

	//udate scores
	std::stringstream s;
	std::stringstream t;
	s<<leftScore;
	t<<rightScore;

	leftScoreText->SetDisplayString(s.str());
	rightScoreText->SetDisplayString(t.str());

	//animations
	if((frames%7)>5)
	{
		if(leftSmash && rightFuckFrames<10)
			player1->SetSpriteFrame((player1->GetSpriteFrame()+1)%3);
		else if(rightFuckFrames>10)
		{
			if(theGameManager.leftSprite==0)
			{
				player1->LoadSpriteFrames("Resources/Images/becky_btn/becky_btn_001.png");
			} else if(theGameManager.leftSprite==1)
			{
				player1->LoadSpriteFrames("Resources/Images/Skelly/headbob/skelly_bob_001.png");
			}
			player1->SetSpriteFrame((player1->GetSpriteFrame()+1)%2);
		} else
			player1->SetSpriteFrame((player1->GetSpriteFrame()+1)%2);

		if(rightSmash && leftFuckFrames<10)
			player2->SetSpriteFrame((player2->GetSpriteFrame()+1)%3);
		else if(leftFuckFrames>10)
		{
			if(theGameManager.rightSprite==0)
			{
				player2->LoadSpriteFrames("Resources/Images/becky_alt_btn/becky_alt_btn_001.png");
			} else if(theGameManager.rightSprite==1)
			{
				player2->LoadSpriteFrames("Resources/Images/Skelly_alt/headbob/skelly_bob_001.png");
			}
			player2->SetSpriteFrame((player2->GetSpriteFrame()+1)%2);
		}
		else
			player2->SetSpriteFrame((player2->GetSpriteFrame()+1)%2);
	}

	//Update position based on thumbstick
	Vec2i movementL = theController.GetLeftThumbstick(); //returns a 2d integer vector
	// where each component ranges
	// from -32768 to 32768

	Vec2i movementR = theController.GetRightThumbstick();

	bool stickL = theController.IsLeftThumbstickButtonDown();
	bool stickR = theController.IsRightThumbstickButtonDown();
	bool triggerL = theController.IsLeftTriggerPressed() || theController.IsLeftBumperDown();
	bool triggerR = theController.IsRightTriggerPressed() || theController.IsRightBumperDown();

	Vector2 position;
	if (movementR.X)
	{
		// Scale the thumbstick down to reasonable proportions and make the range of
		//  movement 3
		if(!leftSmash)
			position.X = 3.0f * ((float)movementR.X / 32768.0f)+7;
		else
			position.X = -3.0f * ((float)movementR.X / 32768.0f)+7;
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
		if(!rightSmash)
			position2.X = 3.0f * ((float)movementL.X / 32768.0f)-7;
		else
			position2.X = -3.0f * ((float)movementL.X / 32768.0f)-7;

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
	

	if(triggerL)
		checkLeftHit(position2);
	if(triggerR)
		checkRightHit(position);

	if(!(song1[curr_note]==song1[curr_note-1] && song1[curr_note]==-1))
	{
		if((frames%30)==29)
		{
			int note=song1[curr_note++];
			if(note>=0)
			{
				buttons[note]->SetColor(1,0,1);
				buttons[note+7]->SetColor(1,0,1);
			}
		} else
		{
			if(leftHit==song1[curr_note-1] && leftHit!=-1)
			{
				leftScore+=leftMul;
				leftMul++;
			} else
				leftMul=1;
			if(rightHit==song1[curr_note-1] && rightHit!=-1)
			{
				rightScore+=rightMul;
				rightMul++;
			} else
				rightMul=1;

			rightHit=-1;
			leftHit=-1;
		}
	}

	if(stickR && !rightSmash)
	{
		rightSmash=true;
		if(theGameManager.rightSprite==0)
			player1->LoadSpriteFrames("Resources/Images/becky_smash/becky_smash_001.png");
		else if(theGameManager.rightSprite==1)
			player1->LoadSpriteFrames("Resources/Images/Skelly_alt/headbob/skelly_bob_001.png");

		if(theGameManager.leftSprite==0)
			player2->LoadSpriteFrames("Resources/Images/becky_alt_panic/becky_alt_panic_001.png");
		else if(theGameManager.leftSprite==1)
			player2->LoadSpriteFrames("Resources/Images/Skelly_alt/headbob/skelly_bob_001.png");


	}
	if(stickL && !leftSmash)
	{
		leftSmash=true;
		if(theGameManager.leftSprite==0)
			player2->LoadSpriteFrames("Resources/Images/becky_alt_btn/becky_alt_btn_001.png");
		else if(theGameManager.leftSprite==1)
			player2->LoadSpriteFrames("Resources/Images/Skelly_alt/headbob/skelly_bob_001.png");

		if(theGameManager.rightSprite==0)
			player1->LoadSpriteFrames("Resources/Images/becky_btn/becky_btn_001.png");
		else if(theGameManager.rightSprite==1)
			player1->LoadSpriteFrames("Resources/Images/Skelly_alt/headbob/skelly_bob_001.png");
	}

	if(leftSmash)
	{
		rightFuckFrames++;
		if(rightFuckFrames>600)
		{
			leftSmash=false;
			rightFuckFrames=0;

			if(theGameManager.rightSprite==0)
				player1->LoadSpriteFrames("Resources/Images/becky_smash/becky_smash_001.png");
			else if(theGameManager.rightSprite==1)
				player1->LoadSpriteFrames("Resources/Images/Skelly_alt/headbob/skelly_bob_001.png");
		}
	}

	if(rightSmash)
	{
		leftFuckFrames++;
		if(leftFuckFrames>600)
		{
			rightSmash=false;
			leftFuckFrames=0;

			if(theGameManager.leftSprite==0)
				player2->LoadSpriteFrames("Resources/Images/becky_alt_smash/becky_alt_smash_001.png");
			else if(theGameManager.leftSprite==1)
				player2->LoadSpriteFrames("Resources/Images/Skelly_alt/headbob/skelly_bob_001.png");
		}
	}

	frames++;
}

void MainGameScreen::checkLeftHit(Vector2 pos)
{

	for(int i=7;i<13;i++)
		buttons[i]->SetColor(0.5,0.5,0.5);

	if(pos.Y<-2 && pos.Y>-8)
	{
		if(pos.X>-6)
		{
			buttons[7]->SetColor(1,1,1);
			leftHit=0;
		} else if(pos.X<-8)
		{
			buttons[12]->SetColor(1,1,1);
			leftHit=5;
		}
	} else if(pos.Y>0)
	{
		if(pos.X<-4&&pos.X>-4.6)
		{
			buttons[8]->SetColor(1,1,1);
			leftHit=1;
		} else if(pos.X<-5.2&&pos.X>-6.16)
		{
			buttons[9]->SetColor(1,1,1);
			leftHit=2;
		} else if(pos.X<-6.8&&pos.X>-7.3)
		{
			buttons[10]->SetColor(1,1,1);
			leftHit=3;
		} else if(pos.X<-8&&pos.X>-9)
		{
			buttons[11]->SetColor(1,1,1);
			leftHit=4;
		} else
			leftHit=-1;
	} else
	{
		leftHit=-1;
	}
}

void MainGameScreen::checkRightHit(Vector2 pos)
{
	for(int i=0;i<6;i++)
		buttons[i]->SetColor(0.5,0.5,0.5);

	if(pos.Y<-2 && pos.Y>-8)
	{
		if(pos.X<6)
		{
			buttons[0]->SetColor(1,1,1);
			rightHit=0;
		} else if(pos.X>8)
		{
			buttons[5]->SetColor(1,1,1);
			rightHit=5;
		}
	} else if(pos.Y>0)
	{
		if(pos.X>4&&pos.X<4.6)
		{
			buttons[1]->SetColor(1,1,1);
			rightHit=1;
		} else if(pos.X>5.2&&pos.X<6.16)
		{
			buttons[2]->SetColor(1,1,1);
			rightHit=2;
		} else if(pos.X>6.8&&pos.X<7.3)
		{
			buttons[3]->SetColor(1,1,1);
			rightHit=3;
		} else if(pos.X>8&&pos.X<9)
		{
			buttons[4]->SetColor(1,1,1);
			rightHit=4;
		} else
			rightHit=-1;
	} else
		rightHit=-1;
}
