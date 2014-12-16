// Controller.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Game.h"
#include <thread>
#include <chrono>
#include <unistd.h>
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

bool Controller::CheckSDLEventQueue()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				this->Cleanup();
				return false;

			// special handling for command-q
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_q && (SDLK_LGUI || SDLK_RGUI))
				{
					this->Cleanup();
					return false;
				}
				break;
		}
	}
	return true;
}

static const double fixedDeltaTimeNs = 50.0 * 1000.0 * 1000.0;
void Controller::UpdateLoop()
{
	using namespace std::chrono;
	// SDL::Texture* text = new SDL::Texture("aqua.png", this->renderer);
	// delete text;

	double accumulator = 0.0;
	double currentTime = this->theGame->gameTime.ns();

	// no point checking for this->run here, since we will exit out if its false first thing.
	while(this->run)
	{
		double newTime = this->theGame->gameTime.ns();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;

		while(this->run && accumulator >= fixedDeltaTimeNs)
		{
			this->theGame->Update((float) fixedDeltaTimeNs);
			accumulator -= fixedDeltaTimeNs;
		}

		printf("spent %f ms on this frame", frameTime);
	}
}

void Controller::RenderLoop()
{
	double fps = 0.0;
	while(this->run && this->CheckSDLEventQueue())
	{
		double begin = this->theGame->gameTime.ns();
		this->renderer->Clear();
		this->renderer->SetColour(Util::Colour::black());

		usleep(40000);
		this->theGame->Render(this->renderer);
		this->renderer->Flush();

		double end = this->theGame->gameTime.ns();
		double frameTime = end - begin;

		// frames per second is (1sec to ns) / 'frametime' (in ns)
		fps = S_TO_NS(1.0) / frameTime;
		fprintf(stderr, "spent %.3f µs on this frame, fps: %.2f                        \r", NS_TO_US(frameTime), fps);
	}
}







void Controller::StartGame()
{
	// init the game state first
	this->theGame = new Game::Game(this);

	// curiously, SDL's event processing *must* be done on the main thread
	// therefore start the gameloop in a separate thread

	// also curiously, SDL's rendering uses some thread-unsafe code from Cocoa (WHY, APPLE)
	// therefore, all rendering must also be done in the main thread.

	this->updateLoop = std::thread(&Controller::UpdateLoop, this);
	this->RenderLoop();


	this->updateLoop.join();
	SDL_Quit();
}











