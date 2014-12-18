// MathPrimitives.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include <cmath>
#include <SDL2/SDL_shape.h>
#include <stdint.h>

namespace Math
{
	struct Vector2
	{
		Vector2() : x(0), y(0) { }
		Vector2(int32_t x, int32_t y) : x(x), y(y) { }
		int32_t x;
		int32_t y;

		Vector2 operator+(Vector2 other);
		Vector2 operator-(Vector2 other);
		Vector2 operator+=(Vector2 other);
		Vector2 operator*=(int64_t scalar);
		Vector2 operator*=(double scalar);
		Vector2 operator*(double scalar);
		Vector2 operator*(int64_t scalar);
		bool operator==(Vector2 other);

		static Vector2 zero() { return Vector2(0, 0); }
	};

	struct Vector3
	{
		Vector3() : x(0), y(0), z(0) { }
		Vector3(double x, double y, double z) : x(x), y(y), z(z) { }
		Vector3(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) { }

		double x;
		double y;
		double z;

		Vector3 operator+(Vector3 other);
		Vector3 operator-(Vector3 other);
		Vector3 operator*(double scalar);
		Vector3 operator*(int64_t scalar);
		Vector3 operator*=(double scalar);
		Vector3 operator*=(int64_t scalar);
		Vector3 operator+=(Vector3 other);
		bool operator==(Vector3 other);

		static Vector3 zero() { return Vector3(0, 0, 0); }
	};

	struct Rectangle
	{
		Rectangle() : origin(0, 0), width(0), height(0) { }
		Rectangle(int32_t x, int32_t y, uint32_t w, uint32_t h) : origin(x, y), width(w), height(h) { }

		Vector2 origin;
		uint32_t width;
		uint32_t height;

		double area()
		{
			return this->width * this->height;
		}

		Vector2 centre()
		{
			return Vector2(this->origin.x + (this->width / 2), this->origin.y + (this->height / 2));
		}
	};

	struct Circle
	{
		Vector2 origin;
		uint32_t radius;

		double area()
		{
			return M_PI * this->radius * this->radius;
		}
	};

	SDL_Rect ToSDL(Rectangle rect);
}












