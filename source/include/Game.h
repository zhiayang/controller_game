// Game.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include "Controller.h"
#include "Game/Scene.h"
#include "Game/Aircraft.h"
namespace Game
{
	void Start(Controller* c);
	void Render(SDL::Renderer* r);
	void Update(float dt);

	Scene* SwitchScene(Scene* newScene);
	Scene* GetCurrentScene();
}
