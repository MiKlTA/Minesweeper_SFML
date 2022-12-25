#ifndef H_MAIN_MENU
#define H_MAIN_MENU



#include "../PopupGameSettings.h"

#include "../Core/Game.h"

#include "../GUI/Layout.h"
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
    
    static void configureButton(Button *button);
    
    
    
    Layout *m_layout;
    
    Image *m_background;
    
    Button *m_continue_game;
    Button *m_new_game;
    Button *m_settings;
    Button *m_exit;
    
    
    
    Button *m_go_back;
    Button *m_start_game;
    
    PopupGameSettings *m_game_settings;
    
};



#endif // H_MAIN_MENU
