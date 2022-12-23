#ifndef H_MAIN_MENU
#define H_MAIN_MENU



#include "../Core/Core.h"
#include "../Core/ResourceManager.h"

#include "../GUI/Image.h"



class MainMenu : public Scene
{
public:
    
    MainMenu(Core *core, ResourceManager *resource_manager, sf::RenderWindow *window);
    
    
    
    void onEvent(const sf::Event &event) override;
    
    void update(float frametime) override;
    
    void onOpen() override;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    Image m_image;
    
};



#endif // H_MAIN_MENU
