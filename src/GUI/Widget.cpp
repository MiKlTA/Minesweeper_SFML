#include "Widget.h"



Widget::Widget(const sf::RenderWindow &window)
    : m_window(window),
      
      m_state(Default)
{
    
}

void Widget::setPosition(sf::Vector2f position)
{
    onPositionChange(position);
    
    m_position = position;
    
    updateTransform();
}

void Widget::scalePosition(sf::Vector2f scale)
{
    setPosition({getPosition().x * scale.x, getPosition().y * scale.y});
}

void Widget::move(sf::Vector2f delta)
{
    setPosition(getPosition() + delta);
}



void Widget::setState(State state)
{
    onStateChange(state);
    
    m_state = state;
}

void Widget::setSize(sf::Vector2f size)
{
    onSizeChange(size);
    
    m_size = size;
}

void Widget::scale(sf::Vector2f scale)
{
    setSize({getSize().x * scale.x, getSize().y * scale.y});
}



bool Widget::containsPoint(sf::Vector2i pixel_point) const
{
    sf::Vector2f world_point = mapPixelToCoords(pixel_point);
    return (world_point.x - m_position.x < m_size.x) && (world_point.y - m_position.y < m_size.y)
            && world_point.x > m_position.x && world_point.y > m_position.y;
}

sf::Vector2f Widget::getPosition() const
{
    return m_position;
}

Widget::State Widget::getState() const
{
    return m_state;
}

sf::Vector2f Widget::getSize() const
{
    return m_size;
}

void Widget::onEvent(const sf::Event &event)
{
    // ...
    
    onEvent_(event);
}



bool Widget::readyToPassFocus()
{
    return true;
}



// protected:



const sf::Transform & Widget::getTransform() const
{
    return m_transform;
}

sf::Vector2f Widget::mapPixelToCoords(sf::Vector2i point) const
{
    return m_window.mapPixelToCoords(point);
}

sf::Vector2i Widget::mapCoordsToPixel(sf::Vector2f point) const
{
    return m_window.mapCoordsToPixel(point);
}



// private:




void Widget::updateTransform()
{
    m_transform = sf::Transform();
    m_transform.translate(m_position);
}
