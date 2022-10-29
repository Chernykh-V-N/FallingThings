#include "spawner.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;


Spawner::Spawner(const vector<sf::Texture>& s_textures)
	: m_textures(s_textures)
{}

void Spawner::spawnObject(const int& s_line, vector<FallingObject>& s_vector)
{
	s_vector.push_back(FallingObject(64 + (s_line * 108), -100, m_textures[rand() % m_textures.size()]));
	//return FallingObject(64 + (s_index * 108), -100, m_textures[rand() % m_textures.size()]);
}