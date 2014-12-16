// Game.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Game.h"
namespace Game
{
	bool x = false;
	Game::Game(Controller* c)
	{
		this->controller = c;
		this->currentScene = new Scene();
	}

	void Game::Render(SDL::Renderer* r)
	{
		x = !x;
		Math::Rectangle c;
		c = Math::Rectangle(0, 0, 200, 300);

		if(x)	r->SetColour(Util::Colour::blue());
		else	r->SetColour(Util::Colour::red());

		r->RenderRect(c);
		// this->currentScene->Render(r);
	}

	void Game::Update(float dt)
	{
		this->currentScene->Update(dt);
	}

	Scene* Game::SwitchScene(Scene* newScene)
	{
		Scene* old = this->currentScene;
		this->currentScene = newScene;
		return old;
	}

	Scene* Game::GetCurrentScene()
	{
		return this->currentScene;
	}
}

