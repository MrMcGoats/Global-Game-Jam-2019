#include "Screens/title.hpp"

TitleScreen::TitleScreen() {}

void TitleScreen::Start()
{
	theGameManager.bg=new Actor();
	theGameManager.bg->LoadSpriteFrames("Resources/Images/cool_background/cool_background_001.png");
	theGameManager.bg->SetSize(27,20);
	theWorld.Add(theGameManager.bg, -1);
}

void TitleScreen::Update(float dt)
{
	theGameManager.nextScreen();
}
