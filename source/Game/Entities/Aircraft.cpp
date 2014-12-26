// Aircraft.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Game.h"
#include <random>
#include "Config.h"
#include "Game/Scene.h"
#include "Game/Aircraft.h"

namespace Game
{
	Aircraft::~Aircraft()
	{
	}

	void Aircraft::Render(SDL::Renderer* r)
	{
		Math::Circle c;
		c.origin = Math::Vector2(this->pos().x, this->pos().y);
		c.radius = 3;

		r->SetColour(Util::Colour::red());
		r->RenderCircle(c, true);

		// render our callsign
		r->SetColour(Util::Colour::white());
		SDL::Font* f = Util::Font::get("pixel", 8, false);
		r->RenderText(this->callsign, f, c.origin + Math::Vector2(3, 3));

		// render our children
		this->MovingEntity::Render(r);
	}

	void Aircraft::Update(float dt)
	{
		this->MovingEntity::Update(dt);
	}
}













