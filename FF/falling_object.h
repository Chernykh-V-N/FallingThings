#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "object.h"

class FallingObject : public Object
{
public:
	FallingObject(const float& s_x, const float& s_y, sf::Texture& s_texture);

	void fall();

	void landing(Object *object);
	bool& isOnGround();
	
	bool isCollision(vector<Object*> s_vector);

	void draw(RenderWindow& s_window);
protected:
	bool m_on_ground;
};