// FlightScene.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Config.h"
#include "Game/Scene.h"

namespace Game
{
	static constexpr double SpawnChance = 0.02;
	void FlightScene::Render(SDL::Renderer* r)
	{
		// r->SetColour(Util::Colour(150, 150, 150, 100));
		// r->RenderRect(Math::Rectangle(0, 0, 200, Config::GetResY()));

		this->Scene::Render(r);
	}

	void FlightScene::Update(float dt)
	{
		double norm = Util::Random::get(0, 1);
		if(norm > 1.0 - SpawnChance)
		{
			this->SpawnRandomCraft();
		}

		this->Scene::Update(dt);
	}

	void FlightScene::SpawnRandomCraft()
	{
		Aircraft* a = new Aircraft(this);
		a->Randomise();
		this->addChild(a);
	}
}
