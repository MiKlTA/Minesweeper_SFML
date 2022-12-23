#ifndef H_SCENE
#define H_SCENE



#include "SFML/Graphics.hpp"



class Core;

class Scene : public sf::Drawable
{
public:
    
    Scene(Core *core);
    
    
    
    virtual void onEvent(const sf::Event &event) = 0;
    
    virtual void update(float frametime) = 0;
    
    virtual void onOpen() = 0;
    
    
    
private:
    
    Core *m_core;
};




#endif // H_SCENE
