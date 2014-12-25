
// Util.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include <map>
#include "Util.h"
#include <stdio.h>
#include "SDLWrapper.h"

namespace Util
{
	namespace Random
	{
		static std::random_device g;
		static std::uniform_real_distribution<double> d(-1.0, 1.0);

		double get(double scale)
		{
			return d(g) * scale;
		}

		double get(double lower, double upper)
		{
			std::uniform_real_distribution<double> something(lower, upper);
			return something(g);
		}
	}

	namespace Font
	{
		typedef std::tuple<std::string, int, bool> FontTuple;
		std::map<FontTuple, SDL::Font*> fontMap;

		SDL::Font* get(std::string name, int size, bool hinting)
		{
			FontTuple tup(name, size, hinting);
			if(fontMap.find(tup) != fontMap.end())
			{
				return fontMap[tup];
			}

			SDL::Font* f = new SDL::Font(AssetLoader::getResourcePath() + name + ".ttf", size, hinting);
			fontMap[tup] = f;

			return f;
		}

		void closeAll()
		{
			for(auto pair : fontMap)
			{
				assert(pair.second);
				delete pair.second;
			}
		}
	}
}













