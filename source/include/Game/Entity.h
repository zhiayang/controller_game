// Entity.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include <vector>
#include "SDLWrapper.h"
#include "MathPrimitives.h"

namespace Game
{
	struct Entity
	{
		Entity() { }
		Entity(Entity* p) : parent(p) { }

		virtual ~Entity() { }
		virtual void Render(SDL::Renderer* r) { for(auto o : this->objects) o->Render(r); }
		virtual void Update(float deltaTime) { for(auto o : this->objects) o->Update(deltaTime); }

		virtual void addChild(Entity* o) { this->objects.push_back(o); }
		virtual void removeChild(Entity* o)
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

		virtual Math::Vector3 pos() final
		{
			// non-overridable -- uses the transform of parents plus the transform of self to move.
			if(this->parent)
				return this->_pos + this->parent->pos();

			else
				return this->_pos;
		}

		virtual void pos(Math::Vector3 v3) final
		{
			this->_pos = v3;
		}

		std::vector<Entity*> objects;
		Entity* parent = 0;

		// pos is private, we only ever want to use the method
		// ever.
		private:
			Math::Vector3 _pos;
	};

	struct MovingEntity : Entity
	{
		MovingEntity() { }
		MovingEntity(Entity* p) : Entity(p) { }

		// moving entities
		// these need to track speed and velocity.
		// velocity would be a normalised vector3 (-1 -> +1)

		virtual void Update(float deltaTime) override
		{
			double actualSpeed = this->speed * deltaTime;
			Math::Vector3 newpos = this->pos() + (this->velocity * actualSpeed);

			this->pos(newpos);
		}

		double speed;
		Math::Vector3 velocity;
	};
}








