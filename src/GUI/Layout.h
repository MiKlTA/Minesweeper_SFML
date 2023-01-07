#ifndef H_LAYOUT
#define H_LAYOUT



#include <list>

#include "Widget.h"



class KeyManager;

class Layout : public Widget
{
public:
    
    enum Type
    {
        Horizontal,
        Vertical
    };
    
    enum Alignment
    {
        Left,
        Centre,
        Right
    };
    
    struct PaddingType
    {
        float left;
        float top;
        float right;
        float bottom;
    };
    
    
    
    Layout(KeyManager *key_manager, const sf::RenderWindow &window,
           Type type, Alignment alignment);
    
    void setPadding(PaddingType padding);
    void setMargin(float margin);
    
    PaddingType getPadding() const;
    float getMargin() const;
    
    
    
    void addWidget(Widget *widget);
    
    
    
    bool isPassEvent(const sf::Event &event) override; 
    
    
    
    static bool need_draw_border;
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    void onEvent_(const sf::Event &event) override;
    void onSizeChange(sf::Vector2f new_size) override;
    void onPositionChange(sf::Vector2f new_position) override;
    void onStateChange(State new_state) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    using ListIterator = std::list<Widget *>::iterator;
    
    PaddingType padding() const; // Spacing inside widgets
    float margin() const; // Spacing between widgets
    
    
    
    
    void addLayoutSizeBy(Widget *widget);
    void recalcWidgetsPositions();
    
    
    
    ListIterator getNextFocusableWidget(ListIterator iter);
    ListIterator getPrevFocusableWidget(ListIterator iter);
    ListIterator getNextFocusableWidgetFromBegin();
    void setFocusOnNextWidget();
    void setFocusOnPrevWidget();
    
    bool haveTargetsForFocus();
    
    
    
    KeyManager *m_key_manager;
    
    
    
    sf::Transform m_transform;
    
    sf::RectangleShape  m_border;
    
    std::list<Widget *> m_contains;
    ListIterator        m_focused_widget;
    bool                m_can_be_focused;
    
    Type            m_type;
    Alignment       m_alignment;
    PaddingType     m_padding;
    float           m_margin;
};



#endif // H_LAYOUT
