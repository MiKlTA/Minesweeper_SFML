#ifndef H_MAIN_MENU
#define H_MAIN_MENU



#include "../Core/Game.h"

#include "../GUI/Button.h"
#include "../GUI/Image.h"



class MainMenu : public Scene
{
public:
    
    MainMenu(Core *core, Game *game);
    
    
    
    void onEvent(const sf::Event &event) override;
    
    void update(float frametime) override;
    
    void onOpen() override;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    Image *m_background;
    
    Button *m_continue_game;
    Button *m_new_game;
    Button *m_settings;
    Button *m_exit;
    
};



#endif // H_MAIN_MENU
