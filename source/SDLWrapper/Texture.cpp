// Texture.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "SDLWrapper.h"
namespace SDL
{
	Texture::Texture(std::string path, Renderer* r) : Texture(AssetLoader::Load(path.c_str()), r)
	{

	}

	Texture::Texture(AssetLoader::Asset* ass, Renderer* r) : Texture(new Surface(ass), r)
	{

	}

	Texture::Texture(Surface* surf, Renderer* r)
	{
		assert(surf);
		assert(r);
		this->surf = surf;
		this->sdlTexture = SDL_CreateTextureFromSurface(r->sdlRenderer, this->surf->sdlSurf);
		if(!this->sdlTexture)
			ERROR("Failed to create texture from surface");
	}

	Texture::~Texture()
	{
		SDL_DestroyTexture(this->sdlTexture);
		delete this->surf;
	}
}
