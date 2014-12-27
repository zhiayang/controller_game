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
		uint64_t GetDisplayAreaWidth();
		uint64_t GetDisplayAreaHeight();
		uint64_t GetSidebarWidth();
		uint64_t GetCmdPanelHeight();

		private:
			std::vector<Aircraft*> crafts;
	};
}
