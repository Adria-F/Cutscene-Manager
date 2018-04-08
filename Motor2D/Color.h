#pragma once

struct Color
{
	int r, g, b, a;

	Color() : r(0), g(0), b(0), a(255)
	{}

	Color(float r, float g, float b, float a = 255) : r(r), g(g), b(b), a(a)
	{}

	void Set(float r, float g, float b, float a = 255)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	float* operator & ()
	{
		return (float*)this;
	}

};
 

static Color Red = Color(255, 0, 0);
static Color Green = Color(0, 255, 0);
static Color Blue = Color(0, 0, 255);
static Color Black = Color(0, 0, 0);
static Color White = Color(255, 255, 255);
static Color Gray = Color(200, 200, 200);
static Color Yellow = Color(255, 255, 102);
