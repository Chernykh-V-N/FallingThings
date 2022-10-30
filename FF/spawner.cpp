#include "spawner.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;


Spawner::Spawner(vector<sf::Texture>& s_textures)
	: m_textures(s_textures)
{
	m_check_rect.setScale(108, 300);
}

bool Spawner::check(const int& s_line, vector<Object*> s_vector)
{
	m_check_rect.setPosition(64 + (s_line * 111), -200);
	for (auto item : s_vector)
	{
		if (m_check_rect.getGlobalBounds().intersects(item->getSprite().getGlobalBounds()))
		{
			return false;
		}
	}
	return true;
}

FallingObject Spawner::spawnObject(const int& s_line)
{
	return FallingObject(64 + (s_line * 111), -200, m_textures[rand() % m_textures.size()]);
}