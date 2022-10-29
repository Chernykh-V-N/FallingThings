#include "ball.h"
#include <time.h>

#include <iostream>

Ball::Ball()
: m_fly_timer(0), m_position(250, 400), m_on_ground(false), m_speed_x(0), m_speed_y(0)
{}

const std::pair<float, float>& Ball::getPosition()
{
	return m_position_tmp;
}

void Ball::setPosition(const float& s_x, const float& s_y)
{
	m_position.first = s_x;
	m_position.second = s_y;
}

void Ball::move(const float& s_x, const float& s_y)
{
	m_position_tmp.first += s_x;
	m_position_tmp.second += s_y;
}

bool Ball::getOnGround()
{
	return m_on_ground;
}

void Ball::jump()
{
	m_on_ground = false;
	m_fly_timer = -1;
}

void Ball::fall()
{
	if (!m_on_ground)
	{
		if (m_fly_timer >= 0)
		{
			m_position_tmp.second = m_position.second + (m_speed_y * m_fly_timer) + ((G * m_fly_timer * m_fly_timer) / 2);
		}
		else
		{
			m_position_tmp.second = m_position.second + (m_speed_y * m_fly_timer) - ((G * m_fly_timer * m_fly_timer) / 2);
		}
	}
}

void Ball::landing()
{
	m_on_ground = true;
}

void Ball::cancelMove(const bool& s_x, const bool& s_y, const sf::Sprite& s_sprite)
{
	if (s_x)
	{
		m_position_tmp.first = s_sprite.getPosition().x - 60;
	}
	if (s_y)
	{
		m_position_tmp.second = s_sprite.getPosition().y - (s_sprite.getTexture()->getSize().y / 2) - 60;
	}
}

void Ball::setSpeed()
{
	m_speed_x = m_position_tmp.first - m_position.first;
	m_speed_y = m_position_tmp.second - m_position.second;
}

void Ball::finalThisFrame(const float& s_time)
{
	m_fly_timer += s_time;
	setSpeed();
	m_position = m_position_tmp;

	//std::cout << m_fly_timer << std::endl;
}
