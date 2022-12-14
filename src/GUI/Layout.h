#ifndef H_LAYOUT
#define H_LAYOUT



#include <list>

#include "Widget.h"



class Layout : public Widget
{
public:
    
    enum Type
    {
        Horizontal,
        Vertical
    };
    
    
    
    Layout(Type type);
    
    void setPadding(float padding);
    void setMargin(float margin);
    
    
    
    void addWidget(Widget *widget);
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    static bool need_draw_border;
    
    
    
protected:
    
    void onEvent_(const sf::Event &event) override;
    void onSizeChange(sf::Vector2f new_size) override;
    void onPositionChange(sf::Vector2f new_position) override;
    
    
    
private:
    
    using ListIterator = std::list<Widget *>::iterator;
    
    float padding() const; // Spacing inside widgets
    float margin() const; // Spacing between widgets
    
    
    
    void addLayoutSizeBy(Widget *widget);
    void calcPositionWidget(Widget *widget);
    
    
    
    void setFocus();
    void unfocus();
    
    
    
    sf::Transform m_transform;
    
    sf::RectangleShape m_border;
    
    ListIterator        m_focused;
    std::list<Widget *> m_contains;
    
    Type        m_type;
    float       m_padding;
    float       m_margin;
};



#endif // H_LAYOUT
