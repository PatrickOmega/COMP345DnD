#include "stdafx.h"
#include "TextSprite.h"
#include <iostream>

TextSprite::TextSprite(SDL_Renderer* renderer, bool* quit, std::string textContent,TTF_Font* textFont, SDL_Color textColor, int x, int y)
{
	this->x = x;
	this->y = y;

	render = renderer;
	text = textContent;
	font = textFont;
	color = textColor;
	if (font == NULL) {
		std::cout << "Could not load specified font" << std::endl;
		*quit = true;
	}

	//Create surface for font
	surface = NULL;
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == NULL) {
		std::cout << "Surface could not be created" << std::endl;
		*quit = true;
	}
	//Create a texture
	texture = NULL;
	texture = SDL_CreateTextureFromSurface(render, surface);
	if (texture == NULL) {
		std::cout << "Error creating texture" << std::endl;
		*quit = true;
	}

	//Determine exact text size
	textHeight = 0;
	textWidth = 0;
	SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
	rect = { x,y,textWidth,textHeight };
}


TextSprite::~TextSprite()
{
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void TextSprite::Draw()
{
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(render, surface);
	textHeight = 0;
	textWidth = 0;
	SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
	rect = { x,y,textWidth,textHeight };
	SDL_RenderCopy(render, texture, NULL, &rect);
}
