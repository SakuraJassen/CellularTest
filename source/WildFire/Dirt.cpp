#include "Dirt.h"
#include "../Util/Random.h"

Dirt::Dirt(sf::Vector2i pos)
	: m_pos       (pos)
{
	m_cellColor = { 139, 69, 19 };
}

Dirt::Dirt(sf::Vector2i pos, sf::Color color)
	: m_pos       (pos)
	, m_cellColor (color);
{

}

void Dirt::update();