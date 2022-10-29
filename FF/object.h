#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Object
{
public:
	Object(const float& s_x, const float& s_y, const Texture& s_texture);

	void draw(RenderWindow& s_window);

protected:
	const Texture& m_texture;
	Sprite m_sprite;

	pair<float, float> m_position;
};