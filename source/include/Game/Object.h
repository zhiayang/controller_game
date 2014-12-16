// Object.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include <vector>
#include "SDLWrapper.h"
#include "MathPrimitives.h"

namespace Game
{
	struct Object
	{
		Object() { }
		Object(Object* p) : parent(p) { }

		virtual ~Object() { }
		virtual void Render(SDL::Renderer* r) { for(auto o : this->objects) o->Render(r); }
		virtual void Update(float deltaTime) { for(auto o : this->objects) o->Update(deltaTime); }

		virtual void AddObject(Object* o) { this->objects.push_back(o); }
		virtual void RemoveObject(Object* o)
		{
			for(auto i = this->objects.begin(); i != this->objects.end(); i++)
			{
				if(*i == o)
				{
					this->objects.erase(i);
					return;
				}
			}

			assert(0);
		}

		virtual Math::Vector3 GetPos() final
		{
			// non-overridable -- uses the transform of parents plus the transform of self to move.
			if(this->parent)
				return this->pos + this->parent->GetPos();

			else
				return this->pos;
		}


		std::vector<Object*> objects;
		Math::Vector3 pos;
		Object* parent = 0;
	};
}
