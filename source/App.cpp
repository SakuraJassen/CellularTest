#include "App.h"

#include <iostream>
#include <ctime>
#include <thread>

#include "Util/Random.h"
#include "Util/Config.h"

#include "ResourceManager/ResourceHolder.h"

App::App(const Config& config)
    : m_window({ config.windowSize.x, config.windowSize.y }, "Cellular Automaton")
    , m_pConfig(&config)
{
    m_pixels = new sf::Uint8[config.simSize.y * config.simSize.x * 4];
    resetView();

    m_guiText.setFont(ResourceHolder::get().fonts.get("arial"));
    m_guiText.move(10, 3);
    m_guiText.setCharacterSize(18);
    m_guiText.setOutlineColor(sf::Color::Black);
    m_guiText.setOutlineThickness(2);

    m_texture.create(config.simSize.x, config.simSize.y );

    m_window.setFramerateLimit(config.fps);
}

App::~App()
{
    //dtor
}


void App::run()
{
    sf::Clock deltaClock;
    unsigned year = 0;
    while (m_window.isOpen()) {

        m_guiText.setString("Generation: " + std::to_string(year++)
                            + "/" + std::to_string(m_pConfig->updateTime));
        m_fpsCounter.update();

        input(deltaClock.restart().asSeconds());
        if(m_cycle++ > m_pConfig->updateTime)
        {
            m_cycle = 0;
            m_automaton->update();
        }

        render();
        pollEvents();
    }
}

const sf::RenderWindow & App::getWindow() const
{
    return m_window;
}

void App::pollEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e))
    {
        m_window.setView(m_view);
        m_automaton->input(e);
        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
        else if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Escape){
                m_window.close();
            }
            if (e.key.code == sf::Keyboard::P) {
                //std::thread(&App::makeImage, this).detach();
            }
            else if (e.key.code == sf::Keyboard::Up) {
                m_view.zoom(0.95f);
            }
            else if (e.key.code == sf::Keyboard::Down) {
                m_view.zoom(1.05f);
            }
            else if (e.key.code == sf::Keyboard::R) {
                resetView();
            }
            else if(e.key.code == sf::Keyboard::Dash) {
                //m_pConfig->setUpdateTime(m_pConfig->updateTime - 1);
            }
            else if(e.key.code == sf::Keyboard::Add) {
                //m_pConfig->setUpdateTime(m_pConfig->updateTime + 1);
            }
        }
    }
}

void App::input(float dt)
{
    float speed = 250;
    sf::Vector2f change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        change.y -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        change.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        change.x -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        change.x += speed;
    }

    m_view.move(change * dt);
}

void App::render()
{
    m_window.clear(m_pConfig->bgColour);

    //Cells
    m_window.setView(m_view);
    m_automaton->render(m_window);

    //GUI
    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_guiText);
    m_fpsCounter.draw(m_window);

    m_window.display();
}

void App::resetView()
{
    m_view = sf::View();
    m_view.setCenter({ (float)m_pConfig->windowSize.x / 2,  (float)m_pConfig->windowSize.y / 2 });
    m_view.setSize({ (float)m_pConfig->windowSize.x,        (float)m_pConfig->windowSize.y });
}

