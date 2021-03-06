// Aircraft.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include <string>
#include "Entity.h"
#include "Command.h"
#include "AIComponent.h"

namespace Game
{
	struct Aircraft : MovingEntity
	{
		Aircraft(Entity* p);
		~Aircraft();

		virtual void Render(SDL::Renderer* r) override;
		virtual void Update(float dt) override;

		std::string callsign;
		Util::Colour colour;
		PlaneAI ai;
	};
}
