#pragma once

class Cell
{
    public:
    	Cell() = default;
        Cell(sf::Vector2i pos, sf::Color color);
        virtual ~Cell() = default;

        virtual sf::Color getColor() { return m_cellColor;};
        virtual void update() { m_life++; };

        sf::Vector2i m_pos;
        uint m_life;
    private:
        sf::Color m_cellColor;

};
