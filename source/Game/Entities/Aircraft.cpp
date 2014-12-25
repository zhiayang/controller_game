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
		SDL::Font* f = Util::Font::get("pixelmix", 8, false);
		r->Render(this->callsign, f, c.origin + Math::Vector2(3, 3));

		// render our children
		this->MovingEntity::Render(r);
	}

	void Aircraft::Randomise()
	{
		// randomise location and velocity
		double x = Util::Random::get();
		double y = Util::Random::get();
		double z = Util::Random::get();

		this->pos(Math::Vector3(Config::GetResX() / 2, Config::GetResY() / 2, 0));
		this->velocity = Math::Vector3(x, y, z);
		this->speed = 50;


		// randomise callsign
		char letters[3] = { };
		letters[0] = 'A' + (char) Util::Random::get(0, 26);
		letters[1] = 'A' + (char) Util::Random::get(0, 26);
		letters[2] = 'A' + (char) Util::Random::get(0, 26);

		this->callsign = letters;
		int num = (int) Util::Random::get(10, 999);
		if(num < 100)
			this->callsign += "0";

		this->callsign += std::to_string(num);

		printf("callsign: %s\n", this->callsign.c_str());
	}

	void Aircraft::Update(float dt)
	{
		this->MovingEntity::Update(dt);
	}
}













