#include "Widget.h"



Widget::Widget()
    : m_window_size(0, 0),
      
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



bool Widget::containsPoint(sf::Vector2f point) const
{
    return (point.x - m_position.x < m_size.x) && (point.y - m_position.y < m_size.y)
            && point.x > m_position.x && point.y > m_position.y;
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
    if (event.type == sf::Event::Resized)
    {
        if (m_window_size.x == 0 || m_window_size.y == 0)
        {
            m_window_size.x = event.size.width;
            m_window_size.y = event.size.height;
        }
        else
        {
            float k_x = event.size.width / float(m_window_size.x);
            float k_y = event.size.height / float(m_window_size.y);
            
            m_size.x *= k_x;
            m_size.y *= k_y;
            
            m_position.x *= k_x;
            m_position.y *= k_y;
            
            m_window_size.x = event.size.width;
            m_window_size.y = event.size.height;
        }
    }
    
    onEvent_(event);
}



// protected:



const sf::Transform & Widget::getTransform() const
{
    return m_transform;
}


// private:




void Widget::updateTransform()
{
    m_transform = sf::Transform();
    m_transform.translate(m_position);
}
