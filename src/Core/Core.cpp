#include "Core.h"

#include "../Scenes/MainMenu.h"
#include "../Scenes/Settings.h"
#include "../Scenes/GameScene.h"



Core::Core(Config *config, SceneManager *scene_manager,
           ResourceManager *resource_manager, SoundManager *sound_manager,
           KeyManager *key_manager,
           Game *game)
    : m_config(config),
      m_scene_manager(scene_manager),
      m_resource_manager(resource_manager),
      m_sound_manager(sound_manager),
      m_key_manager(key_manager)
{
    m_window = new sf::RenderWindow(
                sf::VideoMode(m_config->windowSize().x, m_config->windowSize().y),
                m_config->windowName(),
                sf::Style::Default
                );
    m_window->setVerticalSyncEnabled(true);
    m_window->setPosition({0, 0});
    m_window->setView(sf::View(m_config->viewSize() / 2.f, m_config->viewSize()));
    
    m_scene_manager->addScene("MainMenu", new MainMenu(this, game));
    m_scene_manager->addScene("Settings", new Settings(this, game));
    m_scene_manager->addScene("GameScene", new GameScene(this, game));
    m_scene_manager->setScene("MainMenu");
}

Core::~Core()
{
    delete m_window;
}



sf::Vector2f Core::getViewSize() const
{
    return m_window->getView().getSize();
}



Config * Core::getConfig()
{
    return m_config;
}

SceneManager * Core::getSceneManager()
{
    return m_scene_manager;
}

ResourceManager * Core::getResourceManager()
{
    return m_resource_manager;
}

SoundManager * Core::getSoundManager()
{
    return m_sound_manager;
}

KeyManager *Core::getKeyManager()
{
    return m_key_manager;
}

const sf::RenderWindow * Core::getWindow()
{
    return m_window;
}



void Core::run()
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
            
            m_scene_manager->getCurrentScene()->onEvent(event);
            
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
        }
        
        m_window->clear();
        
        Scene *current_scene = m_scene_manager->getCurrentScene();
        current_scene->update(m_clock.getElapsedTime().asSeconds() - prev_time);
        
        m_window->draw(*m_scene_manager->getCurrentScene());
        m_window->display();
        prev_time = m_clock.getElapsedTime().asSeconds();
    }
}

void Core::quit()
{
    m_window->close();
}




void Core::goToCentre(Widget *widget) const
{
    widget->setPosition(getViewSize() / 2.f - widget->getSize() / 2.f);
}
