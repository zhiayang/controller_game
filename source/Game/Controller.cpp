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
}

bool Controller::CheckSDLEventQueue(int max)
{
	int done = 0;

	SDL_Event event;
	while(this->run && done < max)
	{
		if(SDL_PollEvent(&event))
		{
			done++;
			switch(event.type)
			{
				case SDL_QUIT:
					this->Cleanup();
					return false;
			}
		}
	}

	return true;
}

static const double fixedDeltaTimeMs = 10;
void Controller::UpdateLoop()
{
	// SDL::Texture* text = new SDL::Texture("aqua.png", this->renderer);
	// delete text;

	double accumulator = 0.0;
	double currentTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	// no point checking for this->run here, since we will exit out if its false first thing.
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
	}
}

void Controller::RenderLoop()
{
	while(this->run && this->CheckSDLEventQueue(4))
	{
		this->renderer->Clear();
		this->renderer->SetColour(Util::Colour::black());


		Game::Render(this->renderer);
		this->renderer->Flush();
	}
}







void Controller::StartGame()
{
	// init the game state first
	Game::Start(this);

	// curiously, SDL's event processing *must* be done on the main thread
	// therefore start the gameloop in a separate thread

	// also curiously, SDL's rendering uses some thread-unsafe code from Cocoa (WHY, APPLE)
	// therefore, all rendering must also be done in the main thread.

	this->updateLoop = std::thread(&Controller::UpdateLoop, this);
	this->RenderLoop();


	this->updateLoop.join();
	SDL_Quit();
}











