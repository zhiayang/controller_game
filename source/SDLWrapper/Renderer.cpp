// Renderer.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "SDLWrapper.h"
using namespace Math;

namespace SDL
{
	void Renderer::Clear()
	{
		this->SetColour(Util::Colour::black());
		SDL_RenderClear(this->sdlRenderer);
	}

	void Renderer::Flush()
	{
		SDL_RenderPresent(this->sdlRenderer);
	}


	void Renderer::RenderPoint(Math::Vector2 pt)
	{
		SDL_RenderDrawPoint(this->sdlRenderer, pt.x, pt.y);
	}

	void Renderer::RenderCircle(Math::Circle circ, bool fill)
	{
		int32_t x = circ.radius;
		int32_t y = 0;
		double radiusError = 1.0 - x;

		while(x >= y)
		{
			auto nxpy = Vector2(-x + circ.origin.x, +y + circ.origin.y);
			auto pxpy = Vector2(+x + circ.origin.x, +y + circ.origin.y);
			auto nypx = Vector2(-y + circ.origin.x, +x + circ.origin.y);
			auto pypx = Vector2(+y + circ.origin.x, +x + circ.origin.y);
			auto nynx = Vector2(-y + circ.origin.x, -x + circ.origin.y);
			auto pynx = Vector2(+y + circ.origin.x, -x + circ.origin.y);
			auto nxny = Vector2(-x + circ.origin.x, -y + circ.origin.y);
			auto pxny = Vector2(+x + circ.origin.x, -y + circ.origin.y);


			if(fill)
			{
				this->RenderLine(Vector2(nxpy), Vector2(pxpy));
				this->RenderLine(Vector2(nypx), Vector2(pypx));
				this->RenderLine(Vector2(nynx), Vector2(pynx));
				this->RenderLine(Vector2(nxny), Vector2(pxny));
			}
			else
			{
				this->RenderPoint(nxpy);
				this->RenderPoint(pxpy);

				this->RenderPoint(nypx);
				this->RenderPoint(pypx);

				this->RenderPoint(nynx);
				this->RenderPoint(pynx);

				this->RenderPoint(nxny);
				this->RenderPoint(pxny);
			}

			y++;

			if(radiusError < 0)
			{
				radiusError += 2.0 * y + 1.0;
			}
			else
			{
				x--;
				radiusError += 2.0 * (y - x + 1.0);
			}
		}
	}

	void Renderer::RenderRect(Math::Rectangle rect, bool fill)
	{
		SDL_Rect r = Math::ToSDL(rect);
		if(fill)	SDL_RenderFillRect(this->sdlRenderer, &r);
		else		SDL_RenderDrawRect(this->sdlRenderer, &r);
	}

	void Renderer::RenderLine(Math::Vector2 start, Math::Vector2 end)
	{
		// do some math
		// if dX > dY, then increment x to get y
		// else if dX < dY, then increment y to get x.

		int32_t dx = end.x - start.x;
		int32_t dy = end.y - start.y;

		double err = 0.0;
		double derr = (dx != 0 ? fabs((double) dy / (double) dx) : 1.0);

		int32_t y = start.y;
		for(int32_t x = start.x; x < end.x; dx > 0 ? x++ : x--)
		{
			this->RenderPoint(Vector2(x, y));
			err += derr;

			if(err >= 0.5)
			{
				dy > 0 ? y++ : y--;
				err -= 1.0;
			}
		}
	}













	void Renderer::Render(Texture* text, Math::Vector2 pt)
	{
		this->Render(text, pt.x, pt.y);
	}

	void Renderer::Render(Texture* text, uint32_t x, uint32_t y)
	{
		SDL_Rect tgt;
		tgt.x = x;
		tgt.y = y;

		// get the texture's size
		SDL_QueryTexture(text->sdlTexture, 0, 0, &tgt.w, &tgt.h);
		SDL_RenderCopy(this->sdlRenderer, text->sdlTexture, 0, &tgt);
	}

	void Renderer::Render(Texture* text, Math::Rectangle dest)
	{
		SDL_Rect d = Math::ToSDL(dest);
		SDL_RenderCopy(this->sdlRenderer, text->sdlTexture, 0, &d);
	}

	void Renderer::Render(Texture* text, Math::Rectangle src, Math::Rectangle dest)
	{
		SDL_Rect s = Math::ToSDL(src);
		SDL_Rect d = Math::ToSDL(dest);

		SDL_RenderCopy(this->sdlRenderer, text->sdlTexture, &s, &d);
	}

	void Renderer::RenderText(std::string txt, SDL::Font* font, Math::Vector2 pt)
	{
		SDL::Surface* surface = new SDL::Surface(font, txt, this->drawColour);
		SDL::Texture* texture = new SDL::Texture(surface, this);

		this->Render(texture, pt);
		delete texture;				// this deletes surface as well.
	}

	void Renderer::SetColour(Util::Colour c)
	{
		SDL_SetRenderDrawBlendMode(this->sdlRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(this->sdlRenderer, c.r, c.g, c.b, c.a);
		this->drawColour = c;
	}
}



