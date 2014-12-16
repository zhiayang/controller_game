// SDLWrapper.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include "Util.h"
#include "MathPrimitives.h"
#include <stdint.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include "AssetLoader.h"
#include <SDL2/SDL_image.h>

namespace SDL
{
	struct Texture;

	struct Window
	{
		Window(const char* title, int w, int h) : width(w), height(h)
		{
			this->sdlWin = SDL_CreateWindow(title, 100, 100, w, h, SDL_WINDOW_SHOWN);
			if(!this->sdlWin) ERROR("Failed to initialise SDL Window! (%dx%d)", w, h);

			LOG("Created new SDL Window with dimensions %dx%d", this->width, this->height);
		}

		~Window() { SDL_DestroyWindow(this->sdlWin); }
		SDL_Window* sdlWin;

		int width;
		int height;
	};

	struct Renderer
	{
		Renderer(Window* win, uint32_t flags)
		{
			assert(win);
			this->window = win;

			this->sdlRenderer = SDL_CreateRenderer(this->window->sdlWin, -1, flags);
			if(!this->sdlRenderer) ERROR("Failed to create SDL Rendrer");

			LOG("Created new SDL Renderer");
		}

		void Clear();
		void Flush();


		// primitive shapes
		void RenderPoint(Math::Vector2 pt);
		void RenderCircle(Math::Circle circ, bool fill = true);
		void RenderRect(Math::Rectangle rect, bool fill = true);
		void RenderLine(Math::Vector2 start, Math::Vector2 end);

		// textures
		void Render(Texture* text, Math::Vector2 at);
		void Render(Texture* text, uint32_t x, uint32_t y);
		void Render(Texture* text, Math::Rectangle dest);
		void Render(Texture* text, Math::Rectangle src, Math::Rectangle dest);

		void SetColour(Util::Colour c) { this->drawColour = c; }
		Util::Colour GetColour() { return this->drawColour; }

		SDL_Renderer* sdlRenderer;
		Util::Colour drawColour;
		Window* window;
	};

	struct Surface
	{
		Surface(const char* path);
		Surface(AssetLoader::Asset* ass);
		~Surface();

		SDL_Surface* sdlSurf;
		AssetLoader::Asset* asset;
	};

	struct Texture
	{
		Texture(const char* path, Renderer* rend);
		Texture(AssetLoader::Asset* ass, Renderer* rend);
		Texture(Surface* surf, Renderer* rend);
		~Texture();

		SDL_Texture* sdlTexture;
		Surface* surf;
	};















	void Initialise();
	void Initialise(uint32_t subs);
}














