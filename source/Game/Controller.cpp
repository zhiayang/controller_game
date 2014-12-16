// Controller.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Game.h"
#include <thread>
#include <chrono>
#include <SDL2/SDL.h>
#include "Resources.h"
#include "Controller.h"

Controller::Controller()
{
	this->run = true;
	this->window = new SDL::Window("Controller", 800, 600);
	this->renderer = new SDL::Renderer(this->window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Controller::Cleanup()
{
	this->run = false;

	delete this->window;
	delete this->renderer;

	SDL_Quit();
	exit(1);
}

void Controller::SDLEventLoop()
{
	SDL_Event event;
	while(true)
	{
		if(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					this->Cleanup();
					break;
			}
		}
	}
}

static const double fixedDeltaTimeMs = 10;
void Controller::GameLoop()
{
	// SDL::Texture* text = new SDL::Texture("aqua.png", this->renderer);
	// delete text;

	double accumulator = 0.0;
	double currentTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	while(this->run)
	{
		double newTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;

		while(this->run && accumulator >= fixedDeltaTimeMs)
		{
			accumulator -= fixedDeltaTimeMs;
			Game::Update((float) fixedDeltaTimeMs);
		}


		this->renderer->Clear();
		this->renderer->SetColour(Util::Colour::black());


		Game::Render(this->renderer);
		this->renderer->Flush();
	}

	printf("quit\n");
}

void Controller::StartGame()
{
	// init the game state first
	Game::Start(this);

	// start the event handler on a separate thread
	this->eventLoop = std::thread(&Controller::SDLEventLoop, this);
	this->GameLoop();

	this->eventLoop.join();
}











