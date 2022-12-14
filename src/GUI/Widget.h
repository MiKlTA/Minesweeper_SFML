#ifndef H_WIDGET
#define H_WIDGET



#include "SFML/Graphics.hpp"



class Widget : public sf::Drawable
{
public:
    
    enum State
    {
        Default,
        Hovered,
        Focused,
        Pressed
    };
    
    
    
    Widget();
    
    
    
    void setPosition(sf::Vector2f position);
    void scalePosition(sf::Vector2f scale);
    
    void setState(State state);
    
    void setSize(sf::Vector2f size);
    void scale(sf::Vector2f scale);
    
    
    
    bool containsPoint(sf::Vector2f point) const;
    
    sf::Vector2f getPosition() const;
    
    State getState() const;
    
    sf::Vector2f getSize() const;
    
    
    
    void onEvent(const sf::Event &event);
    
    
    
protected:
    
    const sf::Transform & getTransform() const;
    
    virtual void onEvent_(const sf::Event &event) {};
    virtual void onPositionChange(sf::Vector2f new_position) {};
    virtual void onSizeChange(sf::Vector2f new_size) {};
    
    
    
private:
    
    void updateTransform();
    
    
    
    sf::Vector2u m_window_size;
    
    
    
    State m_state;
    
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    
    sf::Transform m_transform;
};



#endif // H_WIDGET
