#ifndef H_SCROLL_BAR
#define H_SCROLL_BAR



#include "Widget.h"

#include "Image.h"



class ScrollBar : public Widget
{
public:
    
    enum Theme
    {
        White
    };
    
    enum Type
    {
        Horisontal,
        Vertical
    };
    
    ScrollBar(Theme theme, Type type, unsigned int range);
    
    
    
    void setRange(unsigned int range);
    
    
    
    unsigned int getSliderValue() const;
    unsigned int getRange() const;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() override;
    
    
    
protected:
    
    void onEvent_(const sf::Event &event) override;
    void onSizeChange(sf::Vector2f new_size) override;
    void onPositionChange(sf::Vector2f new_position) override;
    void onStateChange(State new_state) override;
    
    
    
private:
    
    bool            isSliderContainsPoint(sf::Vector2f point) const;
    sf::Vector2f    getSliderRelativePosition() const;
    unsigned int    toSliderValue(float slider_position) const;
    
    
    
    Image       m_slider_default;
    Image       m_slider_hovered;
    Image       m_slider_pressed;
    Image       m_horisontal_bar;
    Image       m_vertical_bar;
    Theme       m_theme;
    
    Type        m_type;
    
    unsigned int    m_range;
    unsigned int    m_slider_value; 
};



#endif // H_SCROLL_BAR
