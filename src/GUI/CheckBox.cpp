#include "CheckBox.h"

#include "../Core/ResourceManager.h"
#include "../Core/KeyManager.h"



CheckBox::CheckBox(ResourceManager *resource_manager, KeyManager *key_manager,
                   const sf::RenderWindow &window)
    : Widget(window),
      
      m_key_manager(key_manager),
      
      m_box(resource_manager, window),
      m_checkmark(resource_manager, window),
      
      m_is_checked(false)
{
    m_box.setImage("box");
    m_checkmark.setImage("checkmark");
    
    setSize(m_box.getSize());
}



bool CheckBox::isChecked() const
{
    return m_is_checked;
}




void CheckBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_box, states);
    
    if (m_is_checked)
    {
        target.draw(m_checkmark);
    }
}



bool CheckBox::canBeFocused() const
{
    return true;
}



// protected:



void CheckBox::onEvent_(const sf::Event &event)
{
    switch (getState())
    {
    case State::Default:
        
        if (event.type == sf::Event::MouseMoved
                && containsPoint({event.mouseMove.x, event.mouseMove.y}))
        {
            setState(State::Hovered);
        }
        
        break;
    case State::Hovered:
        
        if (event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button == m_key_manager->button("left"))
        {
            setState(State::Pressed);
            m_press_event = PressEvents::Mouse;
        }
        else if (event.type == sf::Event::MouseMoved
                 && !containsPoint({event.mouseMove.x, event.mouseMove.y}))
         {
             setState(State::Default);
        }
        
        break;
    case State::Focused:
        
        if (event.type == sf::Event::KeyPressed
                && event.key.code == m_key_manager->key("enter"))
        {
            setState(State::Pressed);
            m_press_event = PressEvents::Key;
        }
        
        break;
    case State::Pressed:
        
        if (event.type == sf::Event::MouseButtonReleased
                && event.mouseButton.button == m_key_manager->button("left")
                && m_press_event == PressEvents::Mouse)
        {
            if (containsPoint({event.mouseButton.x, event.mouseButton.y}))
            {
                setState(State::Default);
            }
            else
            {
                setState(State::Hovered);
            }
            m_is_checked = !m_is_checked;
        }
        else if (event.type == sf::Event::KeyReleased
                 && event.key.code == m_key_manager->key("enter")
                 && m_press_event == PressEvents::Key)
        {
            setState(State::Focused);
            m_is_checked = !m_is_checked;
        }
        
        break;
    }
}

void CheckBox::onPositionChange(sf::Vector2f new_position)
{
    locateCheckmark(new_position);
}

void CheckBox::onSizeChange(sf::Vector2f new_size)
{
    if (getSize().x != 0 && getSize().y != 0)
    {
        sf::Vector2f k(new_size.x / getSize().x, new_size.y / getSize().y);
        
        m_box.scale(k);
        m_checkmark.scale(k);
    }
    locateCheckmark(getPosition());
}



// private:



void CheckBox::locateCheckmark(sf::Vector2f box_position)
{
    sf::Vector2f position(box_position);
    position += getSize() / 2.f;
    position -= m_checkmark.getSize() / 2.f;
    m_checkmark.setPosition(position);
}
