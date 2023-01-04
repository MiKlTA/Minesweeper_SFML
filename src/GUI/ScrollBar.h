#ifndef H_SCROLL_BAR
#define H_SCROLL_BAR



#include <functional>
#include <cmath>

#include "Widget.h"

#include "Image.h"



class KeyManager;

class ScrollBar : public Widget
{
public:
    
    using OnValueChangeCallbackType = std::function<void(void)>;
    
    enum Theme
    {
        Default
    };
    
    enum Type
    {
        Horisontal,
        Vertical
    };
    
    ScrollBar(ResourceManager *resource_manager, KeyManager *key_manager,
            const sf::RenderWindow &window,
            Theme theme, Type type,
            unsigned int min_value, unsigned int max_value);
    
    
    
    void setOnValueChangeCallback(OnValueChangeCallbackType callback);
    
    
    
    void setSliderValue(unsigned int slider_value);
    void setRange(unsigned int min_value, unsigned int max_value);
    
    
    
    unsigned int getSliderValue() const;
    unsigned int getRange() const;
    unsigned int getSencetivity() const; // roughly, the smallest scrollbar change
    
    
    
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
    
    unsigned int    m_min_value;
    unsigned int    m_max_value;
    unsigned int    m_slider_value;
    
    OnValueChangeCallbackType m_onValueChange;
};



#endif // H_SCROLL_BAR
