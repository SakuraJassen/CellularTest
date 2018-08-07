#include "Dirt.h"
#include "../Util/Random.h"

Dirt::Dirt(sf::Vector2i pos)
	: Cell(pos, { 139, 69, 19 })
{ }

Dirt::Dirt(sf::Vector2i pos, sf::Color color)
	: Cell(pos, color)
{ }

void Dirt::update() {}