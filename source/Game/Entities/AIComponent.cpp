// AIComponent.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Config.h"
#include "Game/Scene.h"
#include "Game/Entity.h"
#include "Game/AIComponent.h"
namespace Game
{
	// in px.
	#define EDGE_BOUNDARY		-1

	void PlaneAI::UpdateAI(float dt)
	{
		// make sure we have a body
		MovingEntity* me = 0;
		assert(this->body && (me = dynamic_cast<MovingEntity*>(this->body)));

		// and that the body's parent is a flightscene.
		FlightScene* scene = dynamic_cast<FlightScene*>(this->body->parent);
		assert(scene);

		// to make things easier, we manipulate the 'velocity' and 'speed' variables of the MovingEntity.
		// but first, process commands.
		if(this->commandStack.size() > 0)
		{
			this->isBusy = true;

			// get the first command
			Command* c = this->commandStack.front();
			this->commandStack.pop_front();

			switch(c->type)
			{
				default:
					ERROR("Internal state invalid, received invalid command");
			}
		}
		else
		{
			// default idle movement


			// if we're going to leave the screen, reverse direction.
			// actually pick a direction that's random and not in the current direction.
			if(this->body->pos().x + EDGE_BOUNDARY >= Config::GetResX())
			{
				Math::Vector3 newvel;
				newvel.x = me->velocity.x * -1;
				newvel.z = me->velocity.z;			// keep z the same, it represents altitude

				// randomise the y.
				newvel.y = Util::Random::get(0.6, 1.0) * (Util::Random::get() > 0 ? 1 : -1);

				me->velocity = newvel;
			}
			else if(this->body->pos().x <= scene->GetSidebarWidth() + EDGE_BOUNDARY)
			{
				Math::Vector3 newvel;
				newvel.x = me->velocity.x * -1;
				newvel.z = me->velocity.z;			// keep z the same, it represents altitude

				// randomise the y.
				newvel.y = Util::Random::get(0.6, 1.0) * (Util::Random::get() > 0 ? 1 : -1);

				me->velocity = newvel;
			}
			else if(this->body->pos().y <= EDGE_BOUNDARY)
			{
				Math::Vector3 newvel;
				newvel.x = Util::Random::get(0.6, 1.0) * (Util::Random::get() > 0 ? 1 : -1);
				newvel.z = me->velocity.z;			// keep z the same, it represents altitude

				// randomise the x.
				newvel.y = -1 * me->velocity.y;

				me->velocity = newvel;
			}
			else if(this->body->pos().y + EDGE_BOUNDARY >= scene->GetDisplayAreaHeight())
			{
				Math::Vector3 newvel;
				newvel.x = Util::Random::get(0.6, 1.0) * (Util::Random::get() > 0 ? 1 : -1);
				newvel.z = me->velocity.z;			// keep z the same, it represents altitude

				// randomise the x.
				newvel.y = -1 * me->velocity.y;

				me->velocity = newvel;
			}
		}
	}
}









