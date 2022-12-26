#ifndef H_GAME
#define H_GAME



#include "../GUI/Widget.h"

#include "Config.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "KeyManager.h"

#include "SFML/Graphics.hpp"

#include <string>



class Game
{
public:
    
    Game(Config *config, SceneManager *core,
         ResourceManager *resource_manager, KeyManager *key_manager);
    ~Game();
    
    
    
    sf::Vector2f getViewSize() const;
    
    
    
    ResourceManager * getResourceManager();
    KeyManager * getKeyManager();
    const sf::RenderWindow * getWindow();
    
    
    
    void run();
    void quit();
    
    
    
    void goToCentre(Widget *widget) const;
    
    
    
private:
    
    Config             *m_config;
    SceneManager               *m_core;
    ResourceManager    *m_resource_manager;
    KeyManager         *m_key_manager;
    
    sf::RenderWindow   *m_window;
    sf::Clock           m_clock;
};



#endif // H_GAME
