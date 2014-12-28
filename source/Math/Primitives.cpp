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

	Vector3 Vector3::operator*(double sc)
	{
		return Vector3(this->x * sc, this->y * sc, this->z * sc);
	}

	Vector3 Vector3::operator+=(Vector3 other)
	{
		*this = *this + other;
		return *this;
	}

	Vector3 Vector3::operator*=(double scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	bool Vector3::operator==(Vector3 other)
	{
		double xdiff = fabs(this->x - other.x);
		double ydiff = fabs(this->y - other.y);
		double zdiff = fabs(this->z - other.z);

		return (xdiff <= 0.000001) && (ydiff <= 0.000001) && (zdiff <= 0.000001);
	}





	Vector2::Vector2(double degrees)
	{
		this->x = cos(degreesToRadians(degrees));
		this->y = -sin(degreesToRadians(degrees));
	}

	double Vector2::angle()
	{
		return radiansToDegrees(atan2(this->x, -this->y));
	}

	Vector2 Vector2::operator+(Vector2 other)
	{
		return Vector2(this->x + other.x, this->y + other.y);
	}

	Vector2 Vector2::operator-(Vector2 other)
	{
		return Vector2(this->x - other.x, this->y - other.y);
	}

	Vector2 Vector2::operator*(double sc)
	{
		return Vector2(this->x * sc, this->y * sc);
	}

	Vector2 Vector2::operator+=(Vector2 other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	Vector2 Vector2::operator*=(double scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	bool Vector2::operator==(Vector2 other)
	{
		return (this->x == other.x) && (this->y == other.y);
	}
}
