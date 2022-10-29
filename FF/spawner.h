#pragma once

#include "falling_object.h"

class Spawner
{
public:
	Spawner(const std::vector<sf::Texture>& s_textures);

	void spawnObject(const int& s_line, std::vector<FallingObject>& s_vector);
private:
	const std::vector<sf::Texture>& m_textures;

};
