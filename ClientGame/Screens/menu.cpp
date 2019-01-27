/*
 * =====================================================================================
 *
 *       Filename:  menu.cpp
 *
 *    Description:   nn
 *
 *        Version:  1.0
 *        Created:  2019-01-26 06:03:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob MacMillan
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "Screens/menu.hpp"

MenuScreen::MenuScreen() {}

void MenuScreen::Start()
{
	becky1=new Actor();
	becky2=new Actor();
	skelly1=new Actor();
	skelly2=new Actor();
	leftReady=new TextActor("Marker20","Ready!");
	rightReady=new TextActor("Marker20","Ready!");

	leftReady->SetColor(0.2,0.2,0.2);
	rightReady->SetColor(0.2,0.2,0.2);

	leftReady->SetPosition(-7,7);
	rightReady->SetPosition(7,7);

	_objects.push_back(leftReady);
	_objects.push_back(rightReady);

	theWorld.Add(leftReady);
	theWorld.Add(rightReady);

	becky1->LoadSpriteFrames("Resources/Images/becky_sprite_normal/beck_norm_001.bmp");

	skelly1->LoadSpriteFrames("Resources/Images/Skelly/headbob/skelly_bob_001.png");
	skelly2->LoadSpriteFrames("Resources/Images/Skelly_alt/headbob/skelly_bob_001.png");

	becky1->SetSize(5,6);
	becky2->SetSize(5,6);
	skelly1->SetSize(5,6);
	skelly2->SetSize(5,6);

	becky1->SetPosition(4,-2);
	becky2->SetPosition(-4,-2);
	skelly1->SetPosition(8,-2);
	skelly2->SetPosition(-8,-2);

	theWorld.Add(becky1);
	theWorld.Add(becky2);
	theWorld.Add(skelly1);
	theWorld.Add(skelly2);

	_objects.push_back(becky1);
	_objects.push_back(becky2);
	_objects.push_back(skelly1);
	_objects.push_back(skelly2);

}

void MenuScreen::Update(float dt)
{

	static int frames=0;
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

	bool stickL = theController.IsButtonDown(0x40);
	bool stickR = theController.IsButtonDown(0x80);


	if(!theGameManager.leftReady)
	{
		if(movementL.X)
		{
			if(movementL.X>0)
				leftSelect=0;
			else
				leftSelect=1;
		} else
			leftSelect=-1;


		if(leftSelect==0)
		{
			becky2->SetColor(1,1,1);
			skelly2->SetColor(0.2,0.2,0.2);
		} else if(leftSelect==1)
		{
			becky2->SetColor(0.2,0.2,0.2);
			skelly2->SetColor(1,1,1);
		} else
		{
			becky2->SetColor(0.2,0.2,0.2);
			skelly2->SetColor(0.2,0.2,0.2);
		}
	}

	if(!theGameManager.rightReady)
	{
		if(movementR.X)
		{
			if(movementR.X>0)
				rightSelect=0;
			else
				rightSelect=1;
		} else
			rightSelect=-1;

		if(rightSelect==1)
		{
			becky1->SetColor(1,1,1);
			skelly1->SetColor(0.2,0.2,0.2);
		} else if(rightSelect==0)
		{
			becky1->SetColor(0.2,0.2,0.2);
			skelly1->SetColor(1,1,1);
		} else
		{
			becky1->SetColor(0.2,0.2,0.2);
			skelly1->SetColor(0.2,0.2,0.2);
		}
	}

	if(stickL)
		toggleReadyLeft();

	if(stickR)
		toggleReadyRight();


	if(theGameManager.leftReady && theGameManager.rightReady)
	{
		if(frames>20)
		{
			theGameManager.nextScreen();
			frames=0;
		} else frames++;
	}
}

void MenuScreen::toggleReadyLeft()
{
	if(leftSelect<0  || theGameManager.leftReady)
		return;

	leftReady->SetColor(1,1,1);
	if(leftSelect==0)
		theGameManager.leftSprite="Resources/Images/becky_sprite_normal/beck_norm_001.bmp";
	else theGameManager.leftSprite="Resources/Images/Skelly_alt/headbob/skelly_bob_001.png";
	theGameManager.leftReady=true;
}

void MenuScreen::toggleReadyRight()
{
	if(rightSelect<0 || theGameManager.rightReady)
		return;

	rightReady->SetColor(1,1,1);
	if(rightSelect==1)
		theGameManager.rightSprite="Resources/Images/becky_sprite_normal/beck_norm_001.bmp";
	else theGameManager.rightSprite="Resources/Images/Skelly/headbob/skelly_bob_001.png";

	theGameManager.rightReady=true;
}
