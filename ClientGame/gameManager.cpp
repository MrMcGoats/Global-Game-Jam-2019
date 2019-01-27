/*
 * =====================================================================================
 *
 *       Filename:  gameManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019-01-25 08:04:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob MacMillan
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "stdafx.h"
#include "gameManager.hpp"
#include "Screens/mainGame.hpp"
#include "Screens/menu.hpp"

GameScreen::GameScreen() {}

void GameScreen::Start() {}

void GameScreen::Stop()
{
	std::vector<Renderable*>::iterator it = _objects.begin();
	while(_objects.end() != it)
	{
		// we're pre-destroying physics bodies here because it 
		//  can mess with the pathfinding regeneration.
		PhysicsActor* pa = dynamic_cast<PhysicsActor*> (*it);
		if (pa != NULL)
		{
			if (pa->GetBody() != NULL)
			{
				pa->GetBody()->SetUserData(NULL);
				theWorld.GetPhysicsWorld().DestroyBody(pa->GetBody());
				pa->ResetBody();
			}
		}
		(*it)->Destroy();
		it++;
	}
	_objects.clear();
}

void GameScreen::Update(float dt) {}
void GameScreen::Render() {}

MainManager* MainManager::s_MainManager = NULL;

MainManager::MainManager()
{	
	//subscribe to messages
	//Player 1's Buttons
	theSwitchboard.SubscribeTo(this, "btnHit0");//left
	theSwitchboard.SubscribeTo(this, "btnHit1");
	theSwitchboard.SubscribeTo(this, "btnHit2");
	theSwitchboard.SubscribeTo(this, "btnHit3");
	theSwitchboard.SubscribeTo(this, "btnHit4");
	theSwitchboard.SubscribeTo(this, "btnHit5");//right-most button
	theSwitchboard.SubscribeTo(this, "btnHit6");//middle button
	//Player 2 buttons
	theSwitchboard.SubscribeTo(this, "btnHit7");//left-most button
	theSwitchboard.SubscribeTo(this, "btnHit8");
	theSwitchboard.SubscribeTo(this, "btnHit9");
	theSwitchboard.SubscribeTo(this, "btnHit10");
	theSwitchboard.SubscribeTo(this, "btnHit11");
	theSwitchboard.SubscribeTo(this, "btnHit12");//right-most
	theSwitchboard.SubscribeTo(this, "btnHit13");//middle button 

	theSwitchboard.SubscribeTo(this, "leftSmash");
	theSwitchboard.SubscribeTo(this, "rightSmash");

	_screens.push_back(new MenuScreen());
	_screens.push_back(new MainGameScreen());

	leftReady=false;
	rightReady=false;

	unsigned int startingIndex = 0;
	if (_screens.size() > startingIndex)
	{
		theWorld.Add(_screens[startingIndex]);
		_screens[startingIndex]->Start();
		_current = startingIndex;
	}
	else
	{
		_current = -1;
	}

	// We must set the sound callback method.  Although, I'm wondering if we should 
	// allow them to not specify it if they don't need the functionality.
	theSound.SetSoundCallback(this, &GameManager::SoundEnded);

	sample = theSound.LoadSample("Resources/Sounds/175bpm.wav", false /*no stream*/);
	theSound.PlaySound(sample);
}

MainManager& MainManager::GetInstance()
{
	if (s_MainManager == NULL)
	{
		s_MainManager = new MainManager();
	}
	return *s_MainManager;
}

GameScreen* MainManager::GetCurrentScreen()
{
	return _screens[_current];
}

void MainManager::ReceiveMessage(Message* message)
{
	if (message->GetMessageName() == "BtnHit0")
	{
	}else if (message->GetMessageName() == "BtnHit1")
	{
	}else if (message->GetMessageName() =="BtnHit2")
	{
	}else if (message->GetMessageName() =="BtnHit3")
	{
	}else if (message->GetMessageName() =="BtnHit4")
	{
	}else if (message->GetMessageName() =="BtnHit5")
	{
	}else if (message->GetMessageName() =="BtnHit6")
	{
	}else if (message->GetMessageName() =="BtnHit7")
	{
	}else if (message->GetMessageName() =="BtnHit8")
	{
	}else if (message->GetMessageName() =="BtnHit9")
	{
	}else if (message->GetMessageName() =="BtnHit10")
	{
	}else if (message->GetMessageName() =="BtnHit11")
	{
	}else if (message->GetMessageName() =="BtnHit12")
	{
	}else if (message->GetMessageName() =="BtnHit13")
	{
	}
}

void MainManager::hitButton()
{
	if ((_current >= 0) && (_current < (int)_screens.size() - 1))
	{
		_screens[_current]->Stop();
		theWorld.Remove(_screens[_current]);
		_screens[++_current]->Start();
		theWorld.Add(_screens[_current]);
	}
}

void MainManager::Render()
{
	//theSound.PlaySample(sample);
}

void MainManager::SoundEnded(AngelSoundHandle sound)
{	
	// Detect sounds that have ended here.
	// round ends 2.5 seconds after the song ends. 
	// do this by counting frames, calculate framerate in update
	//theWorld.Destroy();
	if(_current!=0) nextScreen();
}

void MainManager::nextScreen()
{
	rightReady=false;
	leftReady=false;

	_screens[_current]->Stop();
	theWorld.Remove(_screens[_current]);
	if(_current==1) _current=0;
	else _current=1;
	_screens[_current]->Start();
	theWorld.Add(_screens[_current]);
}
