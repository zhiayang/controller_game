// Primitives.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "MathPrimitives.h"

namespace Math
{
	SDL_Rect ToSDL(Rectangle rect)
	{
		SDL_Rect r;
		r.x = rect.origin.x;
		r.y = rect.origin.y;
		r.w = rect.width;
		r.h = rect.height;

		return r;
	}



	Vector3 Vector3::operator+(Vector3 other)
	{
		return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Vector3 Vector3::operator-(Vector3 other)
	{
		return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	Vector3 Vector3::operator+=(Vector3 other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	bool Vector3::operator==(Vector3 other)
	{
		return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
	}



	Vector2 Vector2::operator+(Vector2 other)
	{
		return Vector2(this->x + other.x, this->y + other.y);
	}

	Vector2 Vector2::operator-(Vector2 other)
	{
		return Vector2(this->x - other.x, this->y - other.y);
	}

	Vector2 Vector2::operator+=(Vector2 other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	bool Vector2::operator==(Vector2 other)
	{
		return (this->x == other.x) && (this->y == other.y);
	}
}
