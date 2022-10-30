#include "object.h"

Object::Object(const float& s_x, const float& s_y, Texture& s_texture)
	:m_position(s_x, s_y), m_texture(s_texture), m_type(ObjectType::Solid)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);

}

void Object::draw(RenderWindow& s_window)
{

	m_speed.first = m_position.first - m_sprite.getPosition().x;
	m_speed.second = m_position.second - m_sprite.getPosition().y;

	m_sprite.setPosition(m_position.first, m_position.second);
	s_window.draw(m_sprite);
}

bool Object::isOverlap(Object *s_object)
{
	return m_sprite.getGlobalBounds().intersects(s_object->getSprite().getGlobalBounds());
}

Sprite& Object::getSprite()
{
	return m_sprite;
}

pair<float, float> Object::getSpeed()
{
	return m_speed;
}

pair<float, float>& Object::getPosition()
{
	return m_position;
}

ObjectType& Object::getType()
{
	return m_type;
}

bool Object::isCollision(vector<Object*> s_vector)
{
	for (auto item : s_vector)
	{
		if (item != this)
		{
			if (isOverlap(item))
			{
				return true;
			}
		}
	}

	return false;
}