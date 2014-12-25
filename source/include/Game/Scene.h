// Scene.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once

#include <deque>
#include <vector>
#include "Game/Entity.h"
#include "Game/Aircraft.h"

namespace Game
{
	struct Scene : Entity
	{
		virtual ~Scene();
		virtual void Render(SDL::Renderer* r) override;
		virtual void Update(float dt) override;
	};

	struct FlightScene : Scene
	{
		virtual void Render(SDL::Renderer* r) override;
		virtual void Update(float dt) override;

		void SpawnRandomCraft();

		private:
			std::deque<Aircraft*> crafts;
	};
}
