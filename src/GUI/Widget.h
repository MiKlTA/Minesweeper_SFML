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
    
    
    
    Widget(const sf::RenderWindow &window);
    
    
    
    void setPosition(sf::Vector2f position);
    void scalePosition(sf::Vector2f scale);
    void move(sf::Vector2f delta);
    
    void setState(State state);
    
    void setSize(sf::Vector2f size);
    void scale(sf::Vector2f scale);
    
    
    
    bool containsPoint(sf::Vector2i pixel_point) const;
    
    sf::Vector2f getPosition() const;
    
    State getState() const;
    
    sf::Vector2f getSize() const;
    
    
    
    void onEvent(const sf::Event &event);
    
    
    
    virtual bool canBeFocused() const = 0;
    virtual bool isPassEvent(const sf::Event &event);
    
    
    
protected:
    
    const sf::Transform & getTransform() const;
    
    sf::Vector2f mapPixelToCoords(sf::Vector2i point) const;
    sf::Vector2i mapCoordsToPixel(sf::Vector2f point) const;
    
    virtual void onEvent_(const sf::Event &event) {};
    virtual void onPositionChange(sf::Vector2f new_position) {};
    virtual void onSizeChange(sf::Vector2f new_size) {};
    virtual void onStateChange(State new_state) {};
    
    
    
private:
    
    void updateTransform();
    
    
    
    const sf::RenderWindow &m_window;
    
    State m_state;
    
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    
    sf::Transform m_transform;
};



#endif // H_WIDGET
