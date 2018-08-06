#pragma once

#include "../Cell.h"

class Dirt : public Cell
{
    public:
    	Dirt(sf::Vector2i pos);
        Dirt(sf::Vector2i pos, sf::Color color);

        void update() override;
    private:

};
