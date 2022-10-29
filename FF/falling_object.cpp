#include "falling_object.h"
#include <SFML/Graphics.hpp>




FallingObject::FallingObject(const float& s_x, const float& s_y, const sf::Texture& s_texture)
	: Object(s_x, s_y, s_texture), m_on_ground(false)
{
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}


void FallingObject::fall()
{
	if (!m_on_ground)
	{
		m_position.second += 3;
	}
}

void FallingObject::landing(const sf::Sprite& s_sprite)
{
	m_position.second = (s_sprite.getPosition().y - s_sprite.getTexture()->getSize().y / 2) - (m_texture.getSize().y / 2);
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

void FallingObject::draw(RenderWindow& s_window)
{
	fall();
	m_sprite.setPosition(m_position.first, m_position.second);
	s_window.draw(m_sprite);
}