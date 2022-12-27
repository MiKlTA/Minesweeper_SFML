#ifndef H_POPUP_GAME_SETTINGS
#define H_POPUP_GAME_SETTINGS



#include "Core/Core.h"

#include "GUI/Layout.h"

#include "GUI/Image.h"
#include "GUI/Text.h"

#include "GUI/Button.h"
#include "GUI/ScrollBar.h"

#include "Core/ResourceManager.h"
#include "Core/KeyManager.h"



class PopupGameSettings : public Widget
{
public:
    
    PopupGameSettings(Core *core, Game *game);
    
    
    
    bool isPassEvent(const sf::Event &event) override; 
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override;
    void onStateChange(State new_state) override; 
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    Layout m_main_layout;
    Layout m_scrollbars_layout;
    Layout m_labels_layout;
    Layout m_main_horisontal_layout;
    Layout m_buttons_layout;
    
    Image m_background;
    
    
    
    ScrollBar   m_field_width;
    ScrollBar   m_field_height;
    ScrollBar   m_mines_count;
    ScrollBar   m_ducks_count;
    
    Text        m_field_width_label;
    Text        m_field_height_label;
    Text        m_mines_count_label;
    Text        m_ducks_count_label;
    
    Button m_go_back;
    Button m_start;
};



#endif // H_POPUP_GAME_SETTINGS
