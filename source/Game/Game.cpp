// Game.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Game.h"

using AssetLoader::Asset;
namespace Game
{
	int x = 0;
	SDL::Texture* one;
	SDL::Texture* two;
	SDL::Texture* three;
	SDL::Texture* four;

	Game::Game(Controller* c)
	{
		this->controller = c;
		this->currentScene = new FlightScene();
	}

	void Game::Render(SDL::Renderer* r)
	{
		// x = !x;

		// Math::Rectangle c;
		// c = Math::Rectangle(0, 0, 200, 300);

		// if(x)	r->SetColour(Util::Colour::blue());
		// else	r->SetColour(Util::Colour::red());

		// r->RenderRect(c);

		// if(!one)
		// {
		// 	one = new SDL::Texture("1.png", r);
		// 	two = new SDL::Texture("2.png", r);
		// 	three = new SDL::Texture("3.png", r);
		// 	four = new SDL::Texture("4.png", r);
		// }

		// if(x == 0)		r->Render(one, 100, 100);
		// else if(x == 1)	r->Render(two, 100, 100);
		// else if(x == 2)	r->Render(three, 100, 100);
		// else			r->Render(four, 100, 100);

		// x++;
		// x = x % 4;

		this->currentScene->Render(r);
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

