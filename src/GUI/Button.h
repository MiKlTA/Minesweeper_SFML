#ifndef H_BUTTON
#define H_BUTTON



#include <functional>

#include "SFML/Audio.hpp"



#include "Widget.h"

#include "Image.h"
#include "Text.h"



class ResourceManager;
class SoundManager;
class KeyManager;

class Button : public Widget
{
public:
    using CallbackType = std::function<void(void)>;
    
    enum Theme
    {
        Default
    };
    
    
    
    Button(ResourceManager *resource_manager, SoundManager *sound_manager,
           KeyManager *key_manager,
            const sf::RenderWindow &window,
            Theme theme, std::wstring text);
    
    
    
    void setCharacterSize(unsigned int character_size);
    
    void setCallback(CallbackType callback);
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override;
    void onSizeChange(sf::Vector2f new_size) override;
    void onStateChange(State new_state) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    enum PressEvents
    {
        Mouse,
        Key
    };
    
    
    
    void locateText(State new_state, sf::Vector2f new_size, sf::Vector2f new_position);
    
    
    
    KeyManager *m_key_manager;
    
    
    
    Text m_text;
    
    CallbackType m_callback;
    
    Image           m_button_default;
    Image           m_button_hovered;
    Image           m_button_pressed;
    float           m_sagging;
    sf::Vector2f    m_text_padding;
    
    PressEvents     m_press_event_type;
    
    sf::Sound       m_hover_sound;
    sf::Sound       m_press_sound;
};



#endif // H_BUTTON
