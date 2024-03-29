/*
 * =====================================================================================
 *
 *       Filename:  gameManager.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019-01-25 07:56:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob MacMillan
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __GAMEMANAGER_HPP
#define __GAMEMANAGER_HPP

#include "stdafx.h"
#include <vector>
#include <string>

class GameScreen: public Renderable
{
	public:
		GameScreen();

		virtual void Start();
		virtual void Stop(); //calls remove on all _objects and deletes them
		virtual void Update(float dt);
		virtual void Render();

		std::string toggleReadyLeft() {}
		std::string toggleReadyRight() {}


		virtual void ReceiveMessage(Message *message) {}

	protected:
		std::vector<Renderable*> _objects;
};


#define theGameManager MainManager::GetInstance()
class MainManager : public GameManager
{
	public:

		static MainManager &GetInstance();

		GameScreen* GetCurrentScreen();

		virtual void Render();

		virtual void SoundEnded(AngelSoundHandle sound);

		virtual void ReceiveMessage(Message* message);

		void hitButton();

		void nextScreen();

		int leftSprite;
		int rightSprite;
		bool leftReady;
		bool rightReady;

		Actor *bg;
	protected:
		MainManager();
		static MainManager *s_MainManager;

	private:
		std::vector<GameScreen*> _screens;
		int _current;
		AngelSampleHandle game;
		AngelSampleHandle game_p;
		AngelSampleHandle game1;
		AngelSampleHandle menu;
		AngelSampleHandle menu_p;




};

#endif //__GAMEMANAGER_HPP
