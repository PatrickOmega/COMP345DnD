#include "stdafx.h"
#include "SDLSetup.h"
#include <iostream>

SDLSetup::SDLSetup(bool* quit,int screenWidth, int screenHeight)
{
	//Create the game window
	window = NULL;
	window = SDL_CreateWindow("Character Window", 300, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL){
		std::cout << "Error loading window" << std::endl;
		*quit = true;
	}

	//Create the renderer
	render = NULL;
	render = SDL_CreateRenderer(window, -1, 0);
	if (render == NULL){
		std::cout << "Error loading renderer" << std::endl;
		*quit = true;
	}

	//Create an event object
	mainEvent = new SDL_Event();
}


SDLSetup::~SDLSetup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	delete mainEvent;
}

SDL_Renderer* SDLSetup::GetRenderer()
{
	return render;
}

SDL_Event* SDLSetup::GetEvent()
{
	return mainEvent;
}

void SDLSetup::Begin() {
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(render);
}

void SDLSetup::End() {
	SDL_RenderPresent(render);
}
