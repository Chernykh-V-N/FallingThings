#include "falling_object.h"
#include <SFML/Graphics.hpp>




FallingObject::FallingObject(const float& s_x, const float& s_y, sf::Texture& s_texture)
	: Object(s_x, s_y, s_texture), m_on_ground(false)
{
	m_type = ObjectType::Movable;
}


void FallingObject::fall()
{
	if (!m_on_ground)
	{
		m_position.second += 3;
	}
}

void FallingObject::landing(Object *s_object)
{
	m_position.second = (s_object->getSprite().getPosition().y - s_object->getSprite().getTexture()->getSize().y / 2) - (m_texture.getSize().y / 2);
	m_on_ground = true;
}

bool& FallingObject::isOnGround()
{
	return m_on_ground;
}

bool FallingObject::isCollision(vector<Object*> s_vector)
{
	for (auto item : s_vector)
	{
		if (item != this)
		{
			
			if (item->getType() == ObjectType::Solid)
			{
				if (((item->getPosition().first - m_position.first)
					* (item->getPosition().first - m_position.first))
					+ ((item->getPosition().second - m_position.second)
					* (item->getPosition().second - m_position.second))
					< 250000)
				{
					if (this->isOverlap(item))
					{
						landing(item);
						return true;
					}
				}
			}
			else
			{

				if (item->getPosition().second - m_position.second < 150
					&& item->getPosition().first == m_position.first)
				{
					if (this->isOverlap(item))
					{
						landing(item);
						return true;
					}
				}
			}
		}
	}

	return false;
}

void FallingObject::draw(RenderWindow& s_window)
{
	fall();
	m_speed.first = m_position.first - m_sprite.getPosition().x;
	m_speed.second = m_position.second - m_sprite.getPosition().y;

	m_sprite.setPosition(m_position.first, m_position.second);
	s_window.draw(m_sprite);
}