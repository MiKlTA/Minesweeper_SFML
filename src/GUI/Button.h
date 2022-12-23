#ifndef H_BUTTON
#define H_BUTTON



#include <functional>



#include "Widget.h"

#include "Image.h"
#include "Text.h"



class ResourceManager;
class KeyManager;

class Button : public Widget
{
private:
    
    using CallbackType = std::function<void(void)>;
    
    
    
public:
    
    enum Theme
    {
        Default
    };
    
    
    
    Button(ResourceManager *resource_manager, KeyManager *key_manager,
            const sf::RenderWindow &window,
            Theme theme, std::wstring text);
    
    
    
    void setCharacterSize(unsigned int character_size);
    
    void setCallback(CallbackType callback);
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() const override;
    
    
    
protected:
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override;
    void onSizeChange(sf::Vector2f new_size) override;
    void onStateChange(State new_state) override;
    
    
    
private:
    
    enum PressEvents
    {
        Mouse,
        Key
    };
    
    
    
    void locateText(State new_state, sf::Vector2f position);
    
    
    
    KeyManager *m_key_manager;
    
    
    
    Text m_text;
    
    CallbackType m_callback;
    
    Image           m_button_default;
    Image           m_button_hovered;
    Image           m_button_pressed;
    float           m_sagging;
    sf::Vector2f    m_text_padding;
    
    PressEvents     m_press_event_type;
};



#endif // H_BUTTON
