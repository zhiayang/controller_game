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
	Aircraft::Aircraft(Entity* p) : MovingEntity(p), ai(this)
	{

	}

	Aircraft::~Aircraft()
	{
	}

	void Aircraft::Render(SDL::Renderer* r)
	{
		Math::Circle c;
		c.origin = Math::Vector2(this->pos().x, this->pos().y);
		c.radius = 3;

		glPushMatrix();

		// r->SetColour(this->colour);
		// r->RenderCircle(c, true);

		glTranslated(this->pos().x, this->pos().y, 0);
		glRotated(30, 0, 0, 1);
		glTranslated(-this->pos().x, -this->pos().y, 0);
		r->SetColour(this->colour);
		r->RenderEqTriangle(Math::Vector2(this->pos().x, this->pos().y), 10);

		glPopMatrix();

		// render our callsign
		r->SetColour(Util::Colour::white());
		SDL::Font* f = Util::Font::get("pixel", 8, false);
		r->RenderText(this->callsign, f, c.origin + Math::Vector2(3, 3));

		// render our children
		this->MovingEntity::Render(r);
	}

	void Aircraft::Update(float dt)
	{
		this->ai.UpdateAI(dt);
		this->MovingEntity::Update(dt);
	}
}













