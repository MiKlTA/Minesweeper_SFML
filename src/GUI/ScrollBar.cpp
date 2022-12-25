#include "ScrollBar.h"

#include "../Core/ResourceManager.h"
#include "../Core/KeyManager.h"



#include <cmath>



ScrollBar::ScrollBar(
        ResourceManager *resource_manager, KeyManager *key_manager,
        const sf::RenderWindow &window,
        Theme theme, Type type, unsigned int range)
    : Widget(window),
      
      m_key_manager(key_manager),
      
      m_slider_default(resource_manager, window),
      m_slider_hovered(resource_manager, window),
      m_slider_pressed(resource_manager, window),
      m_horisontal_bar(resource_manager, window),
      m_vertical_bar(resource_manager, window),
      
      m_type(type),
      
      m_range(range)
{
    switch (theme)
    {
    case Theme::White:
        
        m_slider_default.setImage("slider");
        m_slider_hovered.setImage("slider");
        m_slider_pressed.setImage("slider");
        m_horisontal_bar.setImage("bar_horisontal");
        m_vertical_bar.setImage("bar_vertical");
        
        break;
    }
    
    if (m_type == Type::Horisontal)
    {
        setSize(sf::Vector2f(m_horisontal_bar.getSize()));
    }
    else // m_type == Type::Vertical
    {
        setSize(sf::Vector2f(m_vertical_bar.getSize()));
    }
}



void ScrollBar::setOnValueChangeCallback(OnValueChangeCallbackType callback)
{
    m_onValueChange = callback;
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



bool ScrollBar::canBeFocused() const
{
    return true;
}

bool ScrollBar::isPassEvent(const sf::Event &event)
{
    bool isPass = true;
    
    switch (m_type)
    {
    case Type::Horisontal:
        if (event.key.code == m_key_manager->key("right"))
        {
            isPass = m_slider_value == m_range;
        }
        else if (event.key.code == m_key_manager->key("left"))
        {
            isPass = m_slider_value == 0;
        }
        break;
    case Type::Vertical:
        if (event.key.code == m_key_manager->key("down"))
        {
            isPass = m_slider_value == 0;
        }
        else if (event.key.code == m_key_manager->key("up"))
        {
            isPass = m_slider_value == m_range;
        }
        break;
    }
    return isPass;
}



// protected:



void ScrollBar::onEvent_(const sf::Event &event)
{
    switch (getState())
    {
    case State::Default:
        
        if (event.type == sf::Event::MouseMoved &&
                (containsPoint({event.mouseMove.x, event.mouseMove.y})
                 ||
                 isSliderContainsPoint({event.mouseMove.x, event.mouseMove.y}))
                )
        {
            setState(State::Hovered);
        }
        
        break;
    case State::Hovered:
        
        if (event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button == m_key_manager->button("left")
                && isSliderContainsPoint({event.mouseButton.x, event.mouseButton.y}))
        {
            setState(State::Pressed);
        }
        else if (event.type == sf::Event::MouseMoved && 
                 (!containsPoint({event.mouseMove.x, event.mouseMove.y})
                  &&
                  !isSliderContainsPoint({event.mouseMove.x, event.mouseMove.y})
                  ))
        {
            setState(State::Default);
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            addSliderValue(std::round(event.mouseWheelScroll.delta));
            m_onValueChange(m_slider_value);
        }
        
        break;
    case State::Pressed:
        
        if (event.type == sf::Event::MouseButtonReleased
                && event.mouseButton.button == m_key_manager->button("left"))
        {
            if (isSliderContainsPoint({event.mouseButton.x, event.mouseButton.y}))
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
            float delta;
            switch (m_type)
            {
            case Type::Horisontal:
                delta = mapPixelToCoords({event.mouseMove.x, event.mouseMove.y}).x
                        - getPosition().x;
                break;
            case Type::Vertical:
                delta = mapPixelToCoords({event.mouseMove.x, event.mouseMove.y}).y
                        - getPosition().y;
                break;
            }
            m_slider_value = toSliderValue(delta);
            m_onValueChange(m_slider_value);
        }
        
        break;
    case State::Focused:
        
        if (event.type == sf::Event::KeyPressed)
        {
            switch (m_type)
            {
            case Type::Horisontal:
                if (event.key.code == m_key_manager->key("right"))
                {
                    addSliderValue(1);
                    m_onValueChange(m_slider_value);
                }
                else if (event.key.code == m_key_manager->key("left"))
                {
                    addSliderValue(-1);
                    m_onValueChange(m_slider_value);
                }
                break;
            case Type::Vertical:
                if (event.key.code == m_key_manager->key("down"))
                {
                    addSliderValue(-1);
                    m_onValueChange(m_slider_value);
                }
                else if (event.key.code == m_key_manager->key("up"))
                {
                    addSliderValue(1);
                    m_onValueChange(m_slider_value);
                }
                break;
            }
            
        }
        
        break;
    }
}



void ScrollBar::draw_(sf::RenderTarget &target, sf::RenderStates states) const
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



// private:



bool ScrollBar::isSliderContainsPoint(sf::Vector2i pixel_point) const
{
    sf::Vector2f point(mapPixelToCoords(pixel_point));
    
    sf::Vector2f size(m_slider_default.getSize());
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
        x = getSliderValue() * getSize().x / float(getRange())
                - m_slider_default.getSize().x / 2.f;
        y = getSize().y / 2.f
                - m_slider_default.getSize().y / 2.f;
        break;
    case Type::Vertical:
        x = getSize().x / 2.f
                - m_slider_default.getSize().x / 2.f;
        y = (getRange() - getSliderValue()) * getSize().y / float(getRange())
                - m_slider_default.getSize().y / 2.f;
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
        if (slider_position > bar_size) slider_position = bar_size;
        return std::round(m_range * slider_position / bar_size);
        break;
    case Vertical:
        bar_size = getSize().y;
        if (slider_position > bar_size) slider_position = bar_size;
        return std::round(m_range * (1.f - slider_position / bar_size));
        break;
    }
}



void ScrollBar::addSliderValue(int value)
{
    int new_sider_value = m_slider_value;
    new_sider_value += value;
    new_sider_value = std::min(new_sider_value, int(m_range));
    new_sider_value = std::max(new_sider_value, 0);
    m_slider_value = static_cast<unsigned int>(new_sider_value);
}
