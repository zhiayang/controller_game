// Controller.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once

#include "Util.h"
#include <thread>
#include "SDLWrapper.h"

namespace Game { struct Game; }
class Controller
{
	friend struct Game::Game;
	public:
		Controller();

		void Cleanup();
		void StartGame();

		void UpdateLoop();
		void RenderLoop();
		bool CheckSDLEventQueue();

		bool isRunning() { return this->run; }
		Controller* instance() { return this; }

	private:
		SDL::Window*	window;
		SDL::Renderer*	renderer;
		bool			run;
		Game::Game*		theGame;
		std::thread		updateLoop;
};
