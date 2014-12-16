// Game.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include <chrono>
#include "Controller.h"
#include "Game/Scene.h"
#include "Game/Aircraft.h"
namespace Game
{
	struct TimeInfo
	{
		double sec()
		{
			return this->ms() / 1000.0;
		}

		double ms()
		{
			return this->µs() / 1000.0;
		}

		double µs()
		{
			return this->ns() / 1000.0;
		}

		uint64_t ns()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	};

	struct Game
	{
		Game(Controller* c);
		void Render(SDL::Renderer* r);
		void Update(float dt);

		Scene* SwitchScene(Scene* newScene);
		Scene* GetCurrentScene();

		TimeInfo gameTime;
		Controller* controller;
		Scene* currentScene;
	};
}







