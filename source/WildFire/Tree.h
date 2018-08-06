#pragma once

#include "../Cell.h"

class Tree : public Cell
{
    public:
    	Tree(sf::Vector2i pos);
        Tree(sf::Vector2i pos, sf::Color color);

        void update() override;
    private:

};
