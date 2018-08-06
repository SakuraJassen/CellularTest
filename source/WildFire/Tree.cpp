#include "Tree.h"

Tree::Tree(sf::Vector2i pos)
	: m_pos       (pos)
{
	m_cellColor = { 0, 255, 0 };
}

Tree::Tree(sf::Vector2i pos, sf::Color color)
	: m_pos       (pos)
	, m_cellColor (color);
{

}
