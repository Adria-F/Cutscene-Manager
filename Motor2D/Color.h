#pragma once

struct Color
{
	float r, g, b, a;

	Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f)
	{}

	Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a)
	{}

	void Set(float r, float g, float b, float a = 1.0f)
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
 

static Color Red = Color(1.0f, 0.0f, 0.0f);
static Color Green = Color(0.0f, 1.0f, 0.0f);
static Color Blue = Color(0.0f, 0.0f, 1.0f);
static Color Black = Color(0.0f, 0.0f, 0.0f);
static Color White = Color(1.0f, 1.0f, 1.0f);
static Color Grey = Color(0.7f, 0.7f, 0.7f);
static Color Yellow = Color(1.0f, 1.0f, 0.4f);
