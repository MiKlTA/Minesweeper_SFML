#ifndef H_SCROLL_BAR
#define H_SCROLL_BAR



#include <functional>

#include "Widget.h"

#include "Image.h"



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
    
    ScrollBar(const sf::RenderWindow &window,
              Theme theme, Type type, unsigned int range);
    
    
    
    void setOnValueChangeCallback(OnValueChangeCallbackType callback);
    
    
    
    void setRange(unsigned int range);
    
    
    
    unsigned int getSliderValue() const;
    unsigned int getRange() const;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() const override;
    bool isPassEvent(const sf::Event &event) override;
    
    
    
protected:
    
    void onEvent_(const sf::Event &event) override;
    
    
    
private:
    
    bool            isSliderContainsPoint(sf::Vector2i pixel_point) const;
    sf::Vector2f    getSliderRelativePosition() const;
    unsigned int    toSliderValue(float slider_position) const;
    
    void            addSliderValue(int value);
    
    
    
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
