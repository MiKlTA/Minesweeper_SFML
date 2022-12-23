#ifndef H_MAIN_MENU1
#define H_MAIN_MENU1



#include "../Core/Core.h"
#include "../Core/ResourceManager.h"
#include "../Core/KeyManager.h"

#include "../GUI/Image.h"
#include "../GUI/Button.h"



class Scene1 : public Scene
{
public:
    
    Scene1(Core *core, ResourceManager *resource_manager, KeyManager *key_manager, sf::RenderWindow *window);
    
    
    
    void onEvent(const sf::Event &event) override;
    
    void update(float frametime) override;
    
    void onOpen() override;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    Image m_image;
    
    Button m_button;
    
};



#endif // H_MAIN_MENU
