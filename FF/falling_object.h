#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "object.h"

class FallingObject : public Object
{
public:
	FallingObject(const float& s_x, const float& s_y, const sf::Texture& s_texture);

	void fall();

	void landing(const sf::Sprite& s_sprite);
	bool& isOnGround();
	bool isOverlap(const sf::Sprite& s_sprite);
	
	void draw(RenderWindow& s_window);
protected:
	bool m_on_ground;
};