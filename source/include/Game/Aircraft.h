// Aircraft.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include <string>
#include "Entity.h"

namespace Game
{
	struct Aircraft : MovingEntity
	{
		Aircraft(Entity* p) : MovingEntity(p) { }
		~Aircraft();

		void Randomise();

		virtual void Render(SDL::Renderer* r) override;
		virtual void Update(float dt) override;

		std::string callsign;
	};
}
