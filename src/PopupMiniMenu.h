#ifndef H_POPUP_MINI_MENU
#define H_POPUP_MINI_MENU



#include "GUI/Image.h"
#include "GUI/Text.h"
#include "GUI/Layout.h"
#include "GUI/Button.h"
          
#include "Core/Core.h"
#include "Core/Game.h"

#include "PopupGameSettings.h"
#include "GameWidget.h"



class GameScene;

class PopupMiniMenu : public Widget
{
public:
    
    PopupMiniMenu(Core *core, Game *game, GameWidget *game_widget);
    
    
    
    bool isPassEvent(const sf::Event &event) override; 
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override; 
    void onStateChange(State new_state) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    Layout m_layout_vertical;
    
    Image m_background;
    
    Button m_back;
    Button m_go_settings;
    Button m_quit_and_save;
    
    PopupGameSettings *m_popup_game_settings;
};



#endif // H_POPUP_MINI_MENU
