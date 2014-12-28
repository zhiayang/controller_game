// Controller.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Game.h"
#include <thread>
#include <chrono>
#include "Config.h"
#include <unistd.h>
#include <SDL2/SDL.h>
#include "Resources.h"
#include "Controller.h"

#define DRAWFPS		1

Controller::Controller()
{
	this->run = true;
	this->window = new SDL::Window("Controller", Config::GetResX(), Config::GetResY());
	this->renderer = new SDL::Renderer(this->window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	this->debugFont = Util::Font::get("pixel", 8, false);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	this->oglContext = SDL_GL_CreateContext(this->window->sdlWin);
	SDL_GL_SetSwapInterval(1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(0, Config::GetResX(), Config::GetResY(), 0, 0, 100);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glClearColor(0, 0, 0, 1.0);
}

void Controller::Cleanup()
{
	LOG("SDL Sent QUIT message.");
	this->run = false;

	Util::Font::closeAll();
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
			case SDL_KEYUP:
				// set the boolean flags. this is useful for polling
				Input::HandleInput(&this->inputState, &event);
				if((this->inputState.isKeyDown(Input::Keys::SuperL) || this->inputState.isKeyDown(Input::Keys::SuperR))
					&& this->inputState.isKeyDown(Input::Keys::Q))
				{
					this->Cleanup();
					return false;
				}

				// TODO: delegate callbacks for keys maybe?
				// Investigate usefulness vs need.
				break;
		}
	}
	return true;
}

static const double fixedDeltaTimeNs	= 20.0 * 1000.0 * 1000.0;
static const double targetFramerate		= 60.0;
static const double targetFrameTimeNs	= S_TO_NS(1.0) / targetFramerate;
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
			this->theGame->Update((float) NS_TO_S(fixedDeltaTimeNs));
			accumulator -= fixedDeltaTimeNs;
		}
	}
}

void Controller::RenderLoop()
{
	double frameTime = 16666666.67;
	while(this->run && this->CheckSDLEventQueue())
	{
		double begin = this->theGame->gameTime.ns();
		this->renderer->Clear();

		this->theGame->Render(this->renderer);





		// frames per second is (1sec to ns) / 'frametime' (in ns)
		double fps = S_TO_NS(1.0) / frameTime;
		if(DRAWFPS)
		{
			this->renderer->RenderText(std::string("FPS: ") + (fps > 60 ? "> 60" : std::to_string((int) fps)), this->debugFont, Math::Vector2(10, 4));
		}












		this->renderer->Flush();

		double end = this->theGame->gameTime.ns();
		frameTime = end - begin;

		// don't kill the CPU
		{
			double toWait = targetFrameTimeNs - frameTime;
			if(toWait > 0)
			{
				usleep(NS_TO_US(toWait));
			}
			else
			{
				// todo: we missed our framerate.
			}
		}

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











