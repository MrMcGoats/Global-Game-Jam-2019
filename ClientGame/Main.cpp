
#include "stdafx.h"


int main(int argc, char* argv[])
{
	// get things going
	//  optional parameters:
	//		int windowWidth			default: 1024
	//		int windowHeight		default: 768
	//		std::string windowName	default: "Angel Engine"
	//		bool antiAliasing		default: false
	//		bool fullScreen			default: false
	//		bool resizable			default: false
	theWorld.Initialize(1024,768,"Game");
	
	//adds the default grid so you can more easily place Actors
	theWorld.Add(new GridActor(), -1);

	//YOUR GAME SETUP CODE HERE
		
	//Create actors
	Actor *player1=new Actor();
	Actor *player1Arm=new Actor();
	Actor *player2=new Actor();
	Actor *player2Arm=new Actor();
	Actor *buttons[14];
	for(int i=0;i<14;i++)
	{
		buttons[i]=new Actor();
		buttons[i]->SetDrawShape(ADS_Circle);
		buttons[i]->SetColor(i*.1,i*.2,i*.3);
		buttons[i]->SetPosition(i,i);
		theWorld.Add(buttons[i]);
	}

	player1->SetDrawShape(ADS_Square);
	player1->SetColor(1,1,1);
	player1Arm->SetDrawShape(ADS_Square);
	player1Arm->SetColor(1,1,1);
	player2->SetDrawShape(ADS_Square);
	player2->SetColor(0,0,0);
	player2Arm->SetDrawShape(ADS_Square);
	player2Arm->SetColor(0,0,0);

	theWorld.Add(player1);
	theWorld.Add(player1Arm);
	theWorld.Add(player2);
	theWorld.Add(player2Arm);

	
	
	// do all your setup first, because this function won't return until you're exiting
	theWorld.StartGame();
	
	// any cleanup can go here
	theWorld.Destroy();
	
	return 0;
}
