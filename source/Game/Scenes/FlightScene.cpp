// FlightScene.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Config.h"
#include "Game/Scene.h"

namespace Game
{
	// globals, deal with it.
	// TODO: move out of here into instance variables, since they're all static anyway
	static const uint64_t panelWidth		= 200;
	static const uint64_t tabWidth			= 170;
	static const uint64_t tabHeight			= 50;
	static const uint64_t padding			= 10;
	static const uint64_t cmdPanelHeight	= 30;
	static const uint64_t offset			= (panelWidth - tabWidth) / 2;
	static const double SpawnChance			= 0.05;

	static void RandomiseCraft(FlightScene* scene, Aircraft* craft)
	{
		// randomise velocity
		double x = Util::Random::get(0.6, 1.0) * (Util::Random::get() > 0 ? 1 : -1);
		double y = Util::Random::get(0.6, 1.0) * (Util::Random::get() > 0 ? 1 : -1);
		double z = 0;

		craft->velocity = Math::Vector3(x, y, z);
		craft->speed = 100;

		// randomise callsign
		char letters[3] = { };
		letters[0] = 'A' + (char) Util::Random::get(0, 26);
		letters[1] = 'A' + (char) Util::Random::get(0, 26);
		letters[2] = 'A' + (char) Util::Random::get(0, 26);

		craft->callsign = letters;
		int num = (int) Util::Random::get(10, 999);
		if(num < 100)
			craft->callsign += "0";

		craft->callsign += std::to_string(num);

		// they shouldn't be able to come from near the corner, or the crafts
		// risk being missed and go the diagonal corner never to be seen again.
		uint64_t randxpos = 0;
		uint64_t randypos = 0;
		{
			// account for the bar on the left.

			uint64_t rx = Config::GetResX() - scene->GetSidebarWidth();
			uint64_t ry = Config::GetResY() - scene->GetCmdPanelHeight();

			// limited to the centre 1/3rd of the screen.
			randxpos = (uint64_t) Util::Random::get(rx / 3, rx - (rx / 3));
			randypos = (uint64_t) Util::Random::get(ry / 3, ry - (ry / 3));
		}

		// get the position that it appears on screen based on its random velocity
		// if it's moving primarily downwards (velocity y < 0, abs(vy) > abs(vx))
		if(y > 0 && fabs(y) > fabs(x))
		{
			craft->pos(Math::Vector3(randxpos, 0, 0));
		}

		// else if it's moving mainly right
		else if(x > 0 && fabs(x) > fabs(y))
		{
			craft->pos(Math::Vector3(panelWidth, randypos, 0));
		}

		// mainly up
		else if(y < 0 && fabs(y) > fabs(x))
		{
			craft->pos(Math::Vector3(randxpos, scene->GetDisplayAreaHeight(), 0));
		}

		// mainly left
		else
		{
			craft->pos(Math::Vector3(Config::GetResX(), randypos, 0));
		}


		craft->colour = Util::Colour::random();
	}







	void FlightScene::Render(SDL::Renderer* r)
	{
		// render all the crafts first, so the sidebar
		// will render on top of them.
		this->Scene::Render(r);

		// render the panel.
		r->SetColour(Util::Colour(150, 150, 150, 100));
		r->RenderRect(Math::Rectangle(0, 0, panelWidth, Config::GetResY()));

		// the amount of tabs that can fit on the screen is roughly resy / (tabHeight + padding)
		size_t numTabs = Config::GetResY() / (tabHeight + padding);

		for(size_t i = 0; i < (numTabs < this->crafts.size() ? numTabs : this->crafts.size()); i++)
		{
			auto xpos = offset;
			auto ypos = offset + (i * tabHeight) + (i * padding);

			r->SetColour(this->crafts[i]->colour);
			r->RenderRect(Math::Rectangle(xpos, ypos, tabWidth, tabHeight));

			r->SetColour(Util::Colour::white());
			r->RenderText(this->crafts[i]->callsign, Util::Font::get("pixel", 16), Math::Vector2(xpos + 10, ypos + 10));
		}
	}

	void FlightScene::Update(float dt)
	{
		double norm = Util::Random::get(0, 1);
		if(norm > (1.0 - SpawnChance))
			this->SpawnRandomCraft();

		this->Scene::Update(dt);
	}

	void FlightScene::SpawnRandomCraft()
	{
		Aircraft* a = new Aircraft(this);
		RandomiseCraft(this, a);

		this->addChild(a);
		this->crafts.push_back(a);
	}

	uint64_t FlightScene::GetDisplayAreaWidth()
	{
		return Config::GetResX() - panelWidth;
	}

	uint64_t FlightScene::GetDisplayAreaHeight()
	{
		return Config::GetResY() - cmdPanelHeight;
	}

	uint64_t FlightScene::GetSidebarWidth()
	{
		return panelWidth;
	}

	uint64_t FlightScene::GetCmdPanelHeight()
	{
		return cmdPanelHeight;
	}
}
