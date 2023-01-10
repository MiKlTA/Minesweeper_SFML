#ifndef H_POPUP_CASE_NEW_GAME
#define H_POPUP_CASE_NEW_GAME



#include "GUI/Image.h"
#include "GUI/Text.h"
#include "GUI/Layout.h"
#include "GUI/Button.h"
          
#include "Core/Core.h"
#include "Core/Game.h"



class PopupGameSettings;

class PopupCaseNewGame : public Widget
{
public:
    
    PopupCaseNewGame(Core *core, Game *game,
                     PopupGameSettings *parent, Button::CallbackType apply_callback);
    
    
    
    bool isPassEvent(const sf::Event &event) override; 
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override;
    void onStateChange(State new_state) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    Layout m_layout_vertical;
    Layout m_layout_horisontal;
    
    Image m_background;
    
    Text m_title;
    
    Button m_cancel;
    Button m_finish_this_game;
    Button m_immediately_start;
};



#endif // H_POPUP_CASE_NEW_GAME
