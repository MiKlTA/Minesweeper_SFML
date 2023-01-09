#ifndef H_CORE
#define H_CORE



#include "../GUI/Widget.h"

#include "Game.h"
#include "Config.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "KeyManager.h"

#include "SFML/Graphics.hpp"

#include <string>



class Core
{
public:
    
    Core(Config *config, SceneManager *scene_manager,
         ResourceManager *resource_manager, SoundManager *sound_manager,
         KeyManager *key_manager,
         Game *game);
    ~Core();
    
    
    
    sf::Vector2f getViewSize() const;
    
    
    
    Config * getConfig();
    SceneManager * getSceneManager();
    ResourceManager * getResourceManager();
    SoundManager * getSoundManager();
    KeyManager * getKeyManager();
    const sf::RenderWindow * getWindow();
    
    
    
    void run();
    void quit();
    
    
    
    void goToCentre(Widget *widget) const;
    
    
    
private:
    
    Config             *m_config;
    SceneManager       *m_scene_manager;
    ResourceManager    *m_resource_manager;
    SoundManager       *m_sound_manager;
    KeyManager         *m_key_manager;
    
    sf::RenderWindow   *m_window;
    sf::Clock           m_clock;
};



#endif // H_CORE
