#include "Game.h"

#include "../Scenes/MainMenu.h"



Game::Game(Config *config, Core *core, ResourceManager *resource_manager)
    : m_config(config),
      m_core(core),
      m_resource_manager(resource_manager)
{
    m_window = new sf::RenderWindow(
                sf::VideoMode(m_config->windowSize().x, m_config->windowSize().y),
                m_config->windowName(),
                sf::Style::Default
                );
    m_window->setPosition({0, 0});
    m_window->setView(sf::View(m_config->viewSize() / 2.f, m_config->viewSize()));
    
    m_core->addScene("MainMenu", new MainMenu(core, resource_manager, m_window));
    m_core->setScene("MainMenu");
}

Game::~Game()
{
    delete m_window;
}



void Game::run()
{
    m_clock.restart();
    float prev_time = m_clock.getElapsedTime().asSeconds();
    while (m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseMoved:
                break;
            default:
                break;
            }
            
            m_core->getCurrentScene()->onEvent(event);
            
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
        }
        
        m_window->clear();
        
        m_core->getCurrentScene()->update(m_clock.getElapsedTime().asSeconds() - prev_time);
        
        m_window->draw(*m_core->getCurrentScene());
        m_window->display();
        prev_time = m_clock.getElapsedTime().asSeconds();
    }
}
