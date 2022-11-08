#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <utility>
#include "AABB_and_Circle.h"

using namespace std;
using namespace sf;

void loadTextures(vector<Texture>& s_vector);


class Object
{
public:
	Object(const Vector2f& s_position, Texture& s_texture);
	Object(const Vector2f& s_position, Texture& s_texture, const float& s_mass);



	void enablePhysics();
	void disablePhysics();
	void enableStatic();
	void disableStatic();

	Sprite& getSprite();
	Texture& getTexture();
	bool& getStatic();

	AABB getAABB();

	void move(Vector2f s_vect);
	void fall();

	//
	void move1(const float& s_time);

	void useAcceleration(const float& s_time);

	void useForce(const Vector2f& s_force);
	void useResultForce();
	void resetForce();

	Vector2f getImpulse();
	void useImpulse(const Vector2f& s_impulse);

	//

	virtual void draw(RenderWindow& s_window, const float s_time);

protected:
	Texture& m_texture;
	Sprite m_sprite;

	Vector2f m_position;

	bool m_static;
	bool m_enable_physics;

	Vector2f m_velocity;
	bool m_on_ground;
	float m_fly_timer;
	float m_timer;

	//
	float m_last_time;
	float m_mass;
	Vector2f m_acceleration;
	Vector2f m_speed;
	Vector2f m_result_force;
	float m_width;
	float m_height;

	float m_elasticity;
};

class Player : public Object
{
public:
	Player(Vector2f s_position, Texture& s_texture);

	Circle getCircle();

	void jump();

	void draw(RenderWindow& s_window, const float s_time);
protected:

};

Object spawnObject(const int& s_line);