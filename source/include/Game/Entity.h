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

		// TODO: somehow NULLs end up in the objects list...?
		// Investigate.
		virtual void Render(SDL::Renderer* r);
		virtual void Update(float deltaTime);
		virtual void addChild(Entity* o);
		virtual void removeChild(Entity* o);
		virtual Math::Vector3 pos() final;
		virtual void pos(Math::Vector3 v3) final;

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








