#ifndef APP_H
#define APP_H
#include <memory>
#include <SFML/Graphics.hpp>

#include "Util/FPSCounter.h"

#include "CellularAutomaton.h"

struct Config;

class App
{
public:
    App(const Config& config);
    virtual ~App();

    template<typename T>
    void init()
    {
        m_automaton = std::make_unique<T>(*m_pConfig, *this);
    }

    void run();

    const sf::RenderWindow& getWindow() const;

protected:

private:
    void pollEvents();
    void input  (float dt);
    void render ();

    void update();

    void resetView();

    std::unique_ptr<CellularAutomaton> m_automaton;

    sf::Texture      m_texture;
    sf::Sprite       m_sprite;
    sf::Uint8        *m_pixels;

    sf::RenderWindow m_window;
    FPSCounter m_fpsCounter;

    sf::Text            m_guiText;
    sf::View            m_view;

    const Config* m_pConfig = nullptr;
    unsigned m_cycle = 0;
    float m_zoom = 1;
};

#endif // APP_H
