#include "Tree.h"

Tree::Tree(sf::Vector2i pos)
	: Cell(pos, { 0, 255, 0 })
{ }

Tree::Tree(sf::Vector2i pos, sf::Color color)
	: Cell(pos, color)
{ }

void Tree::update() {}