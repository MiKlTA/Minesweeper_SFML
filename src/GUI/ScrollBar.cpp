#include "ScrollBar.h"

#include "../ResourceManager.h"
#include "GUIKeyManager.h"



#include <cmath>



ScrollBar::ScrollBar(Theme theme, Type type, unsigned int range)
    : m_type(type),
      
      m_range(range),
      m_slider_value(1)
{
    switch (theme)
    {
    case Theme::White:
        
        m_slider_default = sf::Sprite(*ResourceManager::getTexture("slider"));
        m_slider_hovered = sf::Sprite(*ResourceManager::getTexture("slider"));
        m_slider_pressed = sf::Sprite(*ResourceManager::getTexture("slider"));
        m_horisontal_bar = sf::Sprite(*ResourceManager::getTexture("bar_horisontal"));
        m_vertical_bar = sf::Sprite(*ResourceManager::getTexture("bar_vertical"));
        
        break;
    }
    
    if (m_type == Type::Horisontal)
    {
        setSize(sf::Vector2f(m_horisontal_bar.getTexture()->getSize()));
    }
    else // m_type == Type::Vertical
    {
        setSize(sf::Vector2f(m_vertical_bar.getTexture()->getSize()));
    }
}



void ScrollBar::setRange(unsigned int range)
{
    m_range = range;
}



unsigned int ScrollBar::getSliderValue() const
{
    return m_slider_value;
}

unsigned int ScrollBar::getRange() const
{
    return m_range;
}



void ScrollBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if (m_type == Type::Horisontal)
    {
        target.draw(m_horisontal_bar, states);
    }
    else // m_type == Type::Vertical
    {
        target.draw(m_vertical_bar, states);
    }
    
    states.transform.translate(getSliderRelativePosition());
    
    switch (getState())
    {
    case State::Default:
        target.draw(m_slider_default, states);
        break;
    case State::Hovered:
    case State::Focused:
        target.draw(m_slider_hovered, states);
        break;
    case State::Pressed:
        target.draw(m_slider_pressed, states);
        break;
    }
}



bool ScrollBar::canBeFocused()
{
    return true;
}



// protected:



void ScrollBar::onEvent_(const sf::Event &event)
{
    switch (getState())
    {
    case State::Default:
        
        if (event.type == sf::Event::MouseMoved &&
                (containsPoint(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))
                 ||
                 isSliderContainsPoint(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                )
        {
            setState(State::Hovered);
        }
        
        break;
    case State::Hovered:
        
        if (event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button == GUIKeyManager::button("left")
                && isSliderContainsPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
        {
            setState(State::Pressed);
        }
        else if (event.type == sf::Event::MouseMoved && 
                 (!containsPoint(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))
                  &&
                  !isSliderContainsPoint(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))
                  ))
        {
            setState(State::Default);
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            int new_sider_value = m_slider_value;
            new_sider_value += std::round(event.mouseWheelScroll.delta);
            new_sider_value = std::min(new_sider_value, int(m_range));
            new_sider_value = std::max(new_sider_value, 0);
            m_slider_value = static_cast<unsigned int>(new_sider_value);
        }
        
        break;
    case State::Pressed:
        
        if (event.type == sf::Event::MouseButtonReleased
                && event.mouseButton.button == GUIKeyManager::button("left"))
        {
            if (isSliderContainsPoint(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
            {
                setState(State::Hovered);
            }
            else
            {
                setState(State::Default);
            }
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            m_slider_value = toSliderValue(event.mouseMove.x - getPosition().x);
        }
        
        break;
    case State::Focused:
        
        
        
        break;
    }
}

void ScrollBar::onSizeChange(sf::Vector2f new_size)
{
    
}

void ScrollBar::onPositionChange(sf::Vector2f new_position)
{
    
}

void ScrollBar::onStateChange(State new_state)
{
    
}



// private:



bool ScrollBar::isSliderContainsPoint(sf::Vector2f point) const
{
    sf::Vector2f size(m_slider_default.getTexture()->getSize());
    size = size * 2.f;
    const sf::Vector2f position = getSliderRelativePosition() + getPosition();
    return (point.x > position.x && point.x < position.x + size.x)
            &&
           (point.y > position.y && point.y < position.y + size.y);
}

sf::Vector2f ScrollBar::getSliderRelativePosition() const
{
    float x;
    float y;
    
    switch (m_type)
    {
    case Type::Horisontal:
        x = getSliderValue() * getSliderDelta()
                - m_slider_default.getTextureRect().width / 2.f;
        y = getSize().y / 2.f
                - m_slider_default.getTexture()->getSize().y / 2.f;
        break;
    case Type::Vertical:
        x = getSize().x / 2.f
                - m_slider_default.getTexture()->getSize().x / 2.f;
        y = getSliderValue() * getSliderDelta()
                - m_slider_default.getTextureRect().height / 2.f;
        break;
    }
    
    return sf::Vector2f(x, y);
}

unsigned int ScrollBar::toSliderValue(float slider_position) const
{
    if (slider_position < 0.f) slider_position = 0.f;
    float bar_size;
    switch (m_type)
    {
    case Horisontal:
        bar_size = getSize().x;
        break;
    case Vertical:
        bar_size = getSize().y;
        break;
    }
    if (slider_position > bar_size) slider_position = bar_size;
    return std::round(m_range * slider_position / bar_size);
}

// ?????

float ScrollBar::getSliderDelta() const
{
    return getSize().x / float(getRange());
}