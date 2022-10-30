#pragma once

#include "falling_object.h"

class Spawner
{
public:
	Spawner(std::vector<sf::Texture>& s_textures);

	bool check(const int& s_line, vector<Object*> s_object);

	FallingObject spawnObject(const int& s_line);
private:
	std::vector<sf::Texture>& m_textures;

	RectangleShape m_check_rect;
};
