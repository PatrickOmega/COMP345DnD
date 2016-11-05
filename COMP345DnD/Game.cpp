#include "stdafx.h"
#include "Game.h"
#include "Character.h"
#include <iostream>
#include <string>

Game::Game(int screenWidth, int screenHeight)
{
	quit = false;

	//Initialize SDL and TTF
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init failed" << std::endl;
		quit = true;
	}
	if (TTF_Init() == -1) {
		std::cout << "TTF Init failed" << std::endl;
		quit = true;
	}

	myCharacter = new Character(10);
	setup = new SDLSetup(&quit, screenWidth, screenHeight);
	
	//Set up for character hp text sprite
	text = "Hp: " + std::to_string(myCharacter->getHp());
	font = TTF_OpenFont("data/arial.ttf", 20);
	color = { 255,255,255 };
	characterHpSprite = new TextSprite(setup->GetRenderer(), &quit, text, font, color, 0,0);

	//Test instruction text sprite (damage)
	text = "Press 'H' key to trigger event that will decrease hp by 'x' entered"; 
	testInstructions1 = new TextSprite(setup->GetRenderer(), &quit, text, font, color, 0, screenHeight/2);

	//Test instruction text sprite (heal)
	text = "Press 'U' key to trigger event that will heal hp by 1";
	testInstructions2 = new TextSprite(setup->GetRenderer(), &quit, text, font, color, 0, screenHeight / 2 + 25);
}


Game::~Game()
{
	delete myCharacter;
	delete characterHpSprite;
	delete testInstructions1;
	delete testInstructions2;
	delete setup;
	TTF_Quit();
	SDL_Quit();
}

void Game::GameLoop()
{
	while (!quit && setup->GetEvent()->type != SDL_QUIT) {
		setup->Begin();

		characterHpSprite->Draw();
		switch (setup->GetEvent()->type)
		{
		case SDL_KEYDOWN:
			if (setup->GetEvent()->key.keysym.sym == SDLK_h) {
				myCharacter->hit(1);
				break;
			}
		default:
			break;
		}
		text = "Hp: " + std::to_string(myCharacter->getHp());
		characterHpSprite->SetText("Hp: " + std::to_string(myCharacter->getHp()));

		setup->End();
	}
}
void Game::DriverGameLoop(int amountHit)
{
	while (!quit && setup->GetEvent()->type != SDL_QUIT) {
		setup->Begin();

		characterHpSprite->Draw();
		testInstructions1->Draw();
		testInstructions2->Draw();
		switch (setup->GetEvent()->type)
		{
		case SDL_KEYDOWN:
			if (setup->GetEvent()->key.keysym.sym == SDLK_h) {
				myCharacter->hit(amountHit);
				break;
			}
			if (setup->GetEvent()->key.keysym.sym == SDLK_u) {
				myCharacter->setHp(myCharacter->getHp() + 1);
				break;
			}
		default:
			break;
		}
		text = "Hp: " + std::to_string(myCharacter->getHp());
		characterHpSprite->SetText("Hp: " + std::to_string(myCharacter->getHp()));

		setup->End();
	}
}
