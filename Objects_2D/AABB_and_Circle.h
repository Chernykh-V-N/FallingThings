#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

struct AABB
{
	Vector2f min;
	Vector2f max;
};

struct Circle
{
	Vector2f center;
	float radius;
};

enum Direction 
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};