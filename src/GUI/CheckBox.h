#ifndef H_CHECK_BOX
#define H_CHECK_BOX



#include "Widget.h"

#include "Image.h"



class CheckBox : public Widget
{
public:
    
    
    
    CheckBox(const sf::RenderWindow &window);
    
    
    
    bool isChecked() const;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() const override;
    
    
    
protected:
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override;
    void onSizeChange(sf::Vector2f new_size) override;
    
    
    
private:
    
    enum PressEvents
    {
        Mouse,
        Key
    };
    
    void locateCheckmark(sf::Vector2f box_position);
    
    
    
    Image           m_box;
    Image           m_checkmark;
    
    bool            m_is_checked;
    
    PressEvents     m_press_event;
};



#endif // H_CHECK_BOX
