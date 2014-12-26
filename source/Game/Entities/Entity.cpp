// Entity.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Game/Entity.h"
namespace Game
{
	void Entity::pos(Math::Vector3 v3)
	{
		this->_pos = v3;
	}

	Math::Vector3 Entity::pos()
	{
		// non-overridable -- uses the transform of parents plus the transform of self to move.
		if(this->parent)
			return this->_pos + this->parent->pos();

		else
			return this->_pos;
	}

	void Entity::removeChild(Entity* child)
	{
		for(auto i = this->objects.begin(); i != this->objects.end(); i++)
		{
			if(*i == child)
			{
				this->objects.erase(i);
				return;
			}
		}

		assert(0);
	}

	void Entity::addChild(Entity* child)
	{
		assert(child);
		this->objects.push_back(child);
	}

	void Entity::Update(float dt)
	{
		if(this->objects.size() > 0)
		{
			for(auto o : this->objects)
				if(o) o->Update(dt);
		}
	}

	void Entity::Render(SDL::Renderer* r)
	{
		if(this->objects.size() > 0)
		{
			for(auto o : this->objects)
				if(o) o->Render(r);
		}
	}
}










