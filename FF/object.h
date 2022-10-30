#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum ObjectType
{
	Solid,
	Movable,
	Controlled,
	Service
};

class Object
{
public:
	Object(const float& s_x, const float& s_y, Texture& s_texture);

	virtual void draw(RenderWindow& s_window);

	bool isOverlap(Object *s_object);

	Sprite& getSprite();
	pair<float, float> getSpeed();
	ObjectType& getType();
	pair<float, float>& getPosition();

	virtual bool isCollision(vector<Object*> s_vector);


protected:
	Texture& m_texture;
	Sprite m_sprite;

	pair<float, float> m_speed;
	pair<float, float> m_position;

	ObjectType m_type;
};