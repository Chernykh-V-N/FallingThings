#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class FallingObject
{
public:
	FallingObject(const float& s_x, const float& s_y, const sf::Texture& s_texture);

	void fall();

	void landing();
	bool& isOnGround();
	bool isOverlap(const sf::Sprite& s_sprite);
	

	sf::RenderWindow& draw(sf::RenderWindow& s_window);

private:
	std::pair<float, float> m_position;
	std::pair<float, float> m_position_tmp;

	bool m_on_ground;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};