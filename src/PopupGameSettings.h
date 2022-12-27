#ifndef H_POPUP_GAME_SETTINGS
#define H_POPUP_GAME_SETTINGS



#include "Core/Core.h"

#include "GUI/Image.h"
#include "GUI/Layout.h"
#include "GUI/Button.h"

#include "Core/ResourceManager.h"
#include "Core/KeyManager.h"



class PopupGameSettings : public Widget
{
public:
    
    PopupGameSettings(Core *core);
    
    
    
    bool isPassEvent(const sf::Event &event) override; 
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override;
    void onStateChange(State new_state) override; 
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    Layout m_layout;
    
    Image m_background;
    
    Button m_go_back;
    Button m_start;
};



#endif // H_POPUP_GAME_SETTINGS
