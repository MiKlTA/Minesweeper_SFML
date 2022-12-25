#ifndef H_POPUP_GAME_SETTINGS
#define H_POPUP_GAME_SETTINGS



#include "Core/Game.h"

#include "GUI/Image.h"
#include "GUI/Layout.h"
#include "GUI/Button.h"

#include "Core/ResourceManager.h"
#include "Core/KeyManager.h"



class PopupGameSettings : public Widget
{
public:
    
    PopupGameSettings(Game *game);
    
    
    
    bool canBeFocused() const override;
    bool isPassEvent(const sf::Event &event) override; 
    
    
    
protected:
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    Layout m_layout;
    
    Image m_background;
    
    Button m_go_back;
    Button m_start;
};



#endif // H_POPUP_GAME_SETTINGS
