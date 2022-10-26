#include "falling_object.h"
#include <SFML/Graphics.hpp>

FallingObject::FallingObject(const float& s_x, const float& s_y, const sf::Texture& s_texture)
	: m_position(s_x, s_y), m_texture(s_texture), m_on_ground(false)
{
	m_position_tmp = m_position;
	m_sprite.setTexture(m_texture);
}

void FallingObject::fall()
{
	if (!m_on_ground)
	{
		m_position_tmp.second += 3;
	}
}

void FallingObject::landing()
{
	m_on_ground = true;
}

bool& FallingObject::isOnGround()
{
	return m_on_ground;
}

bool FallingObject::isOverlap(const sf::Sprite& s_sprite)
{
	return m_sprite.getGlobalBounds().intersects(s_sprite.getGlobalBounds());
}

sf::RenderWindow& FallingObject::draw(sf::RenderWindow& s_window)
{

	m_position = m_position_tmp;
	m_sprite.setPosition(m_position.first, m_position.second);
	s_window.draw(m_sprite);
	return s_window;
}
