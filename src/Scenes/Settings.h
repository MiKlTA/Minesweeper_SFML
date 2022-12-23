#ifndef H_SETTINGS
#define H_SETTINGS



#include "../Core/Core.h"
#include "../Core/Game.h"



class Settings : public Scene
{
public:
    
    Settings(Core *core, Game *game);
    
    
    
    void onEvent(const sf::Event &event) override;
    
    void update(float frametime) override;
    
    void onOpen() override;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
};



#endif // H_SETTINGS
