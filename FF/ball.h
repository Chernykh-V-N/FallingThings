#pragma once

#include <SFML/Graphics.hpp>

#define PI 3.1415
#define G 9.8

class Ball
{
public:
	Ball();

	const std::pair<float, float>& getPosition();
	void setPosition(const float& s_x, const float& s_y);
	void move(const float& s_x, const float& s_y);

	bool getOnGround();

	void jump();
	void fall();
	void landing();



	void cancelMove(const bool& s_x, const bool& s_y, const sf::Sprite& s_sprite);
	void finalThisFrame(const float& s_time);
private:
	std::pair<float, float> m_position;
	std::pair<float, float> m_position_tmp;
	float m_fly_timer;
	bool m_on_ground;

	void setSpeed();
	float m_speed_x;
	float m_speed_y;
	
};