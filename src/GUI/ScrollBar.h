#ifndef H_SCROLL_BAR
#define H_SCROLL_BAR



#include <functional>

#include "Widget.h"

#include "Image.h"



class KeyManager;

class ScrollBar : public Widget
{
public:
    
    using OnValueChangeCallbackType = std::function<void(unsigned int)>;
    
    enum Theme
    {
        White
    };
    
    enum Type
    {
        Horisontal,
        Vertical
    };
    
    ScrollBar(ResourceManager *resource_manager, KeyManager *key_manager,
            const sf::RenderWindow &window,
            Theme theme, Type type, unsigned int range);
    
    
    
    void setOnValueChangeCallback(OnValueChangeCallbackType callback);
    
    
    
    void setRange(unsigned int range);
    
    
    
    unsigned int getSliderValue() const;
    unsigned int getRange() const;
    
    
    
    bool isPassEvent(const sf::Event &event) override;
    
    
    
protected:
    
    
    
    bool canBeFocused_() const override;
    
    
    
    void onEvent_(const sf::Event &event) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    bool            isSliderContainsPoint(sf::Vector2i pixel_point) const;
    sf::Vector2f    getSliderRelativePosition() const;
    unsigned int    toSliderValue(float slider_position) const;
    
    void            addSliderValue(int value);
    
    
    
    KeyManager *m_key_manager;
    
    
    
    Image       m_slider_default;
    Image       m_slider_hovered;
    Image       m_slider_pressed;
    Image       m_horisontal_bar;
    Image       m_vertical_bar;
    Theme       m_theme;
    
    Type        m_type;
    
    unsigned int    m_range;
    unsigned int    m_slider_value;
    
    OnValueChangeCallbackType m_onValueChange;
};



#endif // H_SCROLL_BAR
