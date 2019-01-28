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
#include "Screens/title.hpp"

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
	_screens.push_back(new GameScreen());
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

	game1 = theSound.LoadSample("Resources/Sounds/175bpm1.wav", false /*no stream*/);
	game=theSound.LoadSample("Resources/Sounds/175bpm.wav",false);
	menu=theSound.LoadSample("Resources/Sounds/menu.wav", false);

	menu_p=theSound.PlaySound(menu);

	bg=new Actor();
	bg->LoadSpriteFrames("Resources/Images/intro/intro_background_001.png");
	bg->SetSize(27,20);
	theWorld.Add(bg, -1);

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
	if(theController.IsStartButtonDown() && _current==0)
	{
		bg=new Actor();
		bg->LoadSpriteFrames("Resources/Images/cool_background/cool_background_001.png");
		bg->SetSize(27,20);
		theWorld.Add(bg,-1);
		nextScreen();
	}
	static int frames=0;
	if(frames%40==39)
		bg->SetSpriteFrame((bg->GetSpriteFrame()+1)%6);
	frames++;
}

void MainManager::SoundEnded(AngelSoundHandle sound)
{	
	// Detect sounds that have ended here.
	// round ends 2.5 seconds after the song ends. 
	// do this by counting frames, calculate framerate in update
	//theWorld.Destroy();
	if(_current!=0) nextScreen();
	else menu_p=theSound.PlaySound(menu);
}

void MainManager::nextScreen()
{
	//theSound.Shutdown();
	//game = theSound.LoadSample("Resources/Sounds/175bpm.wav", false /*no stream*/);
	//game=theSound.LoadSample("Resources/Sounds/5sec.mp3",false);
	//menu=theSound.LoadSample("Resources/Sounds/175bpm.wav", false);

	rightReady=false;
	leftReady=false;

	_screens[_current]->Stop();
	theWorld.Remove(_screens[_current]);
	if(_current==2) 
	{
		theSound.StopSound(game_p); //probably already stopped, but just in case
		menu_p=theSound.PlaySound(menu);
		_current=1;
	}
	else if(_current==1)
	{
		theSound.PauseSound(menu_p,1);
		srand(time(NULL));
		if(rand()%2)
			game_p=theSound.PlaySound(game);
		else
			game_p=theSound.PlaySound(game1);
		_current=2;
	}
	else
		_current++;
	_screens[_current]->Start();
	theWorld.Add(_screens[_current]);
}
