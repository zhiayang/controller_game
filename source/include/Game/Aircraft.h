// Aircraft.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include "Object.h"

namespace Game
{
	struct Aircraft : Object
	{
		Aircraft(Object* p) : Object(p) { }
		~Aircraft();

		virtual void Render(SDL::Renderer* r) override;
		virtual void Update(float dt) override;
	};
}
