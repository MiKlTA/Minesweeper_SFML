#ifndef H_POPUP_GAME_SETTINGS
#define H_POPUP_GAME_SETTINGS



#include "Core/Core.h"

#include "GUI/Layout.h"

#include "GUI/Image.h"
#include "GUI/TextCell.h"

#include "GUI/Button.h"
#include "GUI/ScrollBar.h"

#include "Core/ResourceManager.h"
#include "Core/KeyManager.h"

#include "PopupCaseNewGame.h"



class PopupGameSettings : public Widget
{
public:
    
    PopupGameSettings(Core *core, Game *game, Button::CallbackType apply_callback);
    
    
    
    void returnSliderToActualPositions();
    
    
    
    bool isPassEvent(const sf::Event &event) override; 
    
    
    
    static void alignLayoutRelativeTo(const Layout *sample, Layout *target,
                                      float sample_element_heignt, float target_element_height);
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override;
    void onStateChange(State new_state) override; 
    void onHide(bool will_hide) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    void updateScrollbars();
    void updateLabels();
    void updateGame();
    void updateMineScrollbar();
    void updateDuckScrollbar();
    
    
    
    Game  *m_game;
    
    Layout m_main_layout;
    
    Layout m_scrollbars_layout;
    Layout m_labels_layout;
    Layout m_icons_layout;
    
    Layout m_main_horisontal_layout;
    Layout m_buttons_layout;
    
    Image m_background;
    
    
    sf::Vector2u m_default_field_size;
    unsigned int m_default_mines;
    unsigned int m_default_ducks;
    ScrollBar   m_field_width;
    ScrollBar   m_field_height;
    ScrollBar   m_mines_count;
    ScrollBar   m_ducks_count;
    
    TextCell    m_field_width_label;
    TextCell    m_field_height_label;
    TextCell    m_mines_count_label;
    TextCell    m_ducks_count_label;
    
    Image       m_width_image;
    Image       m_height_image;
    Image       m_mine_image;
    Image       m_duck_image;
    
    Button m_go_back;
    Button m_start;
    
    
    
    PopupCaseNewGame m_popup_case_new_game;
};



#endif // H_POPUP_GAME_SETTINGS
