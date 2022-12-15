#ifndef H_BUTTON
#define H_BUTTON



#include <functional>



#include "Widget.h"

#include "Text.h"



class Button : public Widget
{
private:
    
    using CallbackType = std::function<void(void)>;
    
    
    
public:
    
    enum Theme
    {
        Blue,
        Red
    };
    
    
    
    Button(Theme theme, std::wstring text, CallbackType callback);
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() override;
    
    
    
protected:
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override; 
    void onSizeChange(sf::Vector2f new_size) override;
    void onStateChange(State new_state) override;
    
    
    
private:
    
    void locateText(State new_state, sf::Vector2f position);
    
    
    
    Text m_text;
    
    CallbackType m_callback;
    
    sf::Sprite      m_default_sprite;
    sf::Sprite      m_hovered_sprite;
    sf::Sprite      m_pressed_sprite;
    float           m_sadding;
    sf::Vector2f    m_text_padding;
};



#endif // H_BUTTON
