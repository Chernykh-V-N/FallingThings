#include <iostream>
#include <SFML/Graphics.hpp>
#include "object.h"
#include <time.h>
#include <algorithm>

using namespace std;
using namespace sf;



vector<Texture> local_texture_vector;



void loadTextures(vector<Texture>& s_vector)
{
	local_texture_vector = s_vector;
}


Object spawnObject(const int& s_line)
{
	{
		return Object(Vector2f(64 + (s_line * 113), 0), local_texture_vector[rand() % local_texture_vector.size()]);
	}

}


Object::Object(const Vector2f& s_position, Texture& s_texture)
	: m_position(s_position), m_texture(s_texture), m_enable_physics(false),
	m_fly_timer(0.0), m_on_ground(0), m_timer(time(NULL)), m_velocity(Vector2f(0, 0)),
	m_static(0), m_mass(1), m_elasticity(0.1)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	m_width = m_sprite.getGlobalBounds().width;
	m_height = m_sprite.getGlobalBounds().height;
}

Object::Object(const Vector2f& s_position, Texture& s_texture, const float& s_mass)
	: m_position(s_position), m_texture(s_texture), m_enable_physics(false),
	m_fly_timer(0.0), m_on_ground(0), m_timer(time(NULL)), m_velocity(Vector2f(0, 0)),
	m_static(0), m_mass(s_mass), m_elasticity(0.1)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	m_width = m_sprite.getGlobalBounds().width;
	m_height = m_sprite.getGlobalBounds().height;
}

Object::Object(const Vector2f& s_position, Texture& s_texture, const float& s_mass, const float& s_elasticity)
	: m_position(s_position), m_texture(s_texture), m_enable_physics(false),
	m_fly_timer(0.0), m_on_ground(0), m_timer(time(NULL)), m_velocity(Vector2f(0, 0)),
	m_static(0), m_mass(s_mass), m_elasticity(s_elasticity)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	m_width = m_sprite.getGlobalBounds().width;
	m_height = m_sprite.getGlobalBounds().height;
}



void Object::enablePhysics()
{
	m_enable_physics = true;
}

void Object::disablePhysics()
{
	m_enable_physics = false;
}

void Object::enableStatic()
{
	m_static = true;
}

void Object::disableStatic()
{
	m_static = false;
}

Sprite& Object::getSprite()
{
	return m_sprite;
}

Texture& Object::getTexture()
{
	return m_texture;
}

bool& Object::getStatic()
{
	return m_static;
}

AABB Object::getAABB()
{
	return AABB{Vector2f(m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top),
		Vector2f(m_sprite.getGlobalBounds().left + m_width,
			m_sprite.getGlobalBounds().top + m_height)};
}

void Object::move(Vector2f s_vect)
{
	m_position += s_vect;
}

void Object::fall()
{
	move(Vector2f(0, 3 * m_fly_timer));
}

//
void Object::move1(const float& s_time)
{
	//m_position.x += m_speed.x * s_time;
	//m_position.y += m_speed.y * s_time;
	m_position += m_speed * s_time;
}

void Object::useAcceleration(const float& s_time)
{
	m_speed += m_acceleration * s_time;
}

void Object::useForce(const Vector2f& s_force)
{
	m_result_force += s_force;
}

void Object::useResultForce()
{
	m_acceleration = m_result_force / m_mass;
}

void Object::resetForce()
{
	m_result_force = Vector2f(0, 0);
}

Vector2f Object::getImpulse()
{
	return Vector2f(m_speed * m_mass);
}

void Object::useImpulse(const Vector2f& s_impulse)
{
	Vector2f tmp = s_impulse / m_mass;

	m_speed += tmp;
}

Vector2f Object::getSpeed()
{
	return m_speed;
}

void Object::setSpeed(const Vector2f& s_speed)
{
	m_speed = s_speed;
}

void Object::invertSpeedX()
{
	m_speed.x *= -1;
}

void Object::invertSpeedY()
{
	m_speed.y *= -1;
}

float Object::getMass()
{
	return m_mass;
}

float Object::getElasticity()
{
	return m_elasticity;
}

//

void Object::draw(RenderWindow& s_window, const float s_time)
{
	if (!m_static)
	{
			
		float tmp_delta_time = s_time;
		tmp_delta_time /= 1000;
		//

		useResultForce();
		useAcceleration(tmp_delta_time);
		
		move1(tmp_delta_time);
		//
		m_last_time += tmp_delta_time;

		m_fly_timer += tmp_delta_time;

		m_velocity.x = (m_position.x - m_sprite.getPosition().x) / tmp_delta_time;
		m_velocity.y = (m_position.y - m_sprite.getPosition().y) / tmp_delta_time;

	}

	m_sprite.setPosition(m_position);
	s_window.draw(m_sprite);
}


Player::Player(Vector2f s_position, Texture& s_texture)
	: Object(s_position, s_texture)
{
	enablePhysics();
}

Player::Player(Vector2f s_position, Texture& s_texture, const float& s_mass, const float& s_elasticity)
	: Object(s_position, s_texture, s_mass, s_elasticity)
{
	enablePhysics();
}

Circle Player::getCircle()
{
	return Circle{ m_position, (m_sprite.getGlobalBounds().height / 2)};
}

void Player::jump()
{
	m_fly_timer = -1.5;
}

void Player::draw(RenderWindow& s_window, const float s_time)
{
	if (!m_static)
	{
			
		float tmp_delta_time = s_time;
		tmp_delta_time /= 1000;
		//

		useResultForce();
		useAcceleration(tmp_delta_time);
		
		move1(tmp_delta_time);
		//
		m_last_time += tmp_delta_time;

		m_fly_timer += tmp_delta_time;

		m_velocity.x = (m_position.x - m_sprite.getPosition().x) / tmp_delta_time;
		m_velocity.y = (m_position.y - m_sprite.getPosition().y) / tmp_delta_time;
		//cout << getImpulse().x << "; " << getImpulse().y << endl;
	}

	m_sprite.setPosition(m_position);
	s_window.draw(m_sprite);
}
