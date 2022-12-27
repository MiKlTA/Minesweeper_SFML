#ifndef H_SCENE
#define H_SCENE



#include "SFML/Graphics.hpp"



class SceneManager;

class Scene : public sf::Drawable
{
public:
    
    Scene(SceneManager *scene_manager);
    
    
    
    virtual void onEvent(const sf::Event &event) = 0;
    
    virtual void update(float frametime) = 0;
    
    virtual void onOpen() = 0;
    
    
    
private:
    
    SceneManager *m_scene_manager;
};




#endif // H_SCENE
