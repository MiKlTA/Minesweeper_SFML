#ifndef H_GAME
#define H_GAME



#include "Config.h"
#include "Core.h"
#include "ResourceManager.h"

#include "SFML/Graphics.hpp"

#include <string>



class Game
{
public:
    
    Game(Config *config, Core *core, ResourceManager *resource_manager);
    ~Game();
    
    
    
    void run();
    
    
    
private:
    
    Config             *m_config;
    Core               *m_core;
    ResourceManager    *m_resource_manager;
    
    sf::RenderWindow   *m_window;
    sf::Clock           m_clock;
};



#endif // H_GAME
