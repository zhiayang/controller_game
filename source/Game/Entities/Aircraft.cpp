// Aircraft.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Game.h"
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

		r->SetColour(Util::Colour::white());
		r->RenderCircle(c, false);

		// render our children
		this->MovingEntity::Render(r);
	}

	void Aircraft::Randomise()
	{
		this->pos(Math::Vector3(300, 300, 0));
		this->velocity = Math::Vector3(1, 0, 0);
		this->speed = 10;
	}

	void Aircraft::Update(float dt)
	{
		this->MovingEntity::Update(dt);
	}
}
