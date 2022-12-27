#ifndef H_SETTINGS
#define H_SETTINGS



#include "../Core/SceneManager.h"
#include "../Core/Core.h"



class Settings : public Scene
{
public:
    
    Settings(SceneManager *scene_manager, Core *core);
    
    
    
    void onEvent(const sf::Event &event) override;
    
    void update(float frametime) override;
    
    void onOpen() override;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
};



#endif // H_SETTINGS
