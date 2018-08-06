#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
struct Config
{
    Config() = default;
    Config(const sf::Vector2u& winSize, unsigned cellSize)
        : windowSize    (winSize)
        ,   cellSize    (cellSize)
    {
        init();
    }

    void init()
    {
        windowSize.x -= windowSize.x % cellSize;
        windowSize.y -= windowSize.y % cellSize;

        simSize.x = windowSize.x / cellSize;
        simSize.y = windowSize.y / cellSize;
    }

    sf::Vector2u windowSize = { 1280, 720 };
    sf::Vector2u simSize;

    unsigned cellSize = 4;
    unsigned fps = 30;

    unsigned updateTime = fps/fps;

    sf::Color bgColour = { 0, 0, 0 };
    sf::Color fgColour = { 126, 126, 126};
};

#endif // CONFIG_H_INCLUDED
