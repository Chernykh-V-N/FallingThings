#include "object.h"

Object::Object(const float& s_x, const float& s_y, const Texture& s_texture)
	:m_position(s_x, s_y), m_texture(s_texture)
{
	m_sprite.setTexture(m_texture);
}

void Object::draw(RenderWindow& s_window)
{
	m_sprite.setPosition(m_position.first, m_position.second);
	s_window.draw(m_sprite);
}