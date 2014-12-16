// Scene.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Game/Scene.h"
namespace Game
{
	Scene::~Scene()
	{
	}

	void Scene::Render(SDL::Renderer* r)
	{
		this->Object::Render(r);
	}

	void Scene::Update(float dt)
	{
		this->Object::Update(dt);
	}
}
