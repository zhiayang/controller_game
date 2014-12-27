// AIComponent.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include <deque>
#include "Entity.h"
#include "Command.h"
namespace Game
{
	struct PlaneAI
	{
		PlaneAI(Entity* e) : body(e) { }
		Math::Vector3 target;
		void UpdateAI(float dt);


		Entity* body;
		bool isBusy;
		std::deque<Command*> commandStack;
	};
}
