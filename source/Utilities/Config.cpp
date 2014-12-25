// Config.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "Config.h"
namespace Config
{
	// lol such place many holder
	uint64_t rx = 1024;
	uint64_t ry = 640;

	uint64_t GetResX()
	{
		return rx;
	}

	uint64_t GetResY()
	{
		return ry;
	}

	void SetResX(uint64_t x)
	{
		rx = x;
	}

	void SetResY(uint64_t y)
	{
		ry = y;
	}
}
