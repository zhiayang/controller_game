// Game.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Game.h"
namespace Game
{
	Scene* currentScene;
	Controller* controller;

	void Start(Controller* c)
	{
		controller = c;
		SwitchScene(new Scene());
	}

	void Render(SDL::Renderer* r)
	{
		assert(currentScene);
		currentScene->Render(r);
	}

	void Update(float dt)
	{
		assert(currentScene);
		currentScene->Update(dt);
	}

	Scene* SwitchScene(Scene* newScene)
	{
		Scene* old = currentScene;
		currentScene = newScene;
		return old;
	}

	Scene* GetScene()
	{
		return currentScene;
	}
}

