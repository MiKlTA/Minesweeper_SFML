#include "Button.h"

#include "../Core/ResourceManager.h"
#include "../Core/KeyManager.h"



Button::Button(KeyManager *key_manager, ResourceManager *resource_manager,
               const sf::RenderWindow &window,
               Theme theme, std::wstring text, CallbackType callback)
    : Widget(window),
      
      m_key_manager(key_manager),
      
      m_text(resource_manager, window, Text::Alignment::Centre, text),
      m_callback(callback),
      
      m_button_default(resource_manager, window),
      m_button_hovered(resource_manager, window),
      m_button_pressed(resource_manager, window)
{
    switch (theme)
    {
    case Theme::Blue:
        m_button_default.setImage("blue_button_default");
        m_button_hovered.setImage("blue_button_hovered");
        m_button_pressed.setImage("blue_button_pressed");
        break;
    case Theme::Red:
        m_button_default.setImage("red_button_default");
        m_button_hovered.setImage("red_button_hovered");
        m_button_pressed.setImage("red_button_pressed");
        break;
    }
    m_text_padding = {0.f, 8.f};
    
    m_sagging = float(m_button_default.getSize().y) - m_button_pressed.getSize().y;
    
    
    
    setSize(sf::Vector2f(m_button_default.getSize()));
    
    m_text.setColor(sf::Color(150, 40, 10));
}



void Button::setCharacterSize(unsigned int character_size)
{
    m_text.setCharacterSize(character_size);
    locateText(getState(), getPosition());
}



void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    switch (getState())
    {
    case Widget::Default:
        target.draw(m_button_default, states);
        break;
    case Widget::Hovered:
    case Widget::Focused:
        target.draw(m_button_hovered, states);
        break;
    case Widget::Pressed:
        states.transform.translate(0, m_sagging);
        target.draw(m_button_pressed, states);
        break;
    }
    
    target.draw(m_text);
}



bool Button::canBeFocused() const
{
    return true;
}



// protected:



void Button::onEvent_(const sf::Event &event)
{
    switch (getState())
    {
    case State::Default:
        
        if (containsPoint({event.mouseMove.x, event.mouseMove.y}))
        {
           setState(State::Hovered); 
        }
        
        break;
    case State::Focused:
        
        if (event.type == sf::Event::KeyPressed
                && event.key.code == m_key_manager->key("enter"))
        {
            setState(State::Pressed);
            m_press_event_type = PressEvents::Key;
        }
        
        break;
    case State::Hovered:
        
        if (event.type == sf::Event::MouseMoved
                && !containsPoint({event.mouseMove.x, event.mouseMove.y}))
        {
           setState(State::Default); 
        }
        else if (event.type == sf::Event::MouseButtonPressed
                 && event.mouseButton.button == m_key_manager->button("left"))
        {
            setState(State::Pressed);
            m_press_event_type = PressEvents::Mouse;
        }
        
        break;
    case State::Pressed:
        
        if (event.type == sf::Event::MouseButtonReleased
                && event.mouseButton.button == m_key_manager->button("left")
                && m_press_event_type == PressEvents::Mouse)
        {
            if (containsPoint({event.mouseMove.x, event.mouseMove.y}))
            {
                setState(State::Default);
            }
            else
            {
                setState(State::Hovered);
            }
            m_callback();
        }
        else if (event.type == sf::Event::KeyReleased
                 && event.key.code == m_key_manager->key("enter")
                 && m_press_event_type == PressEvents::Key)
        {
            setState(State::Focused);
            m_callback();
        }
        
        break;
    }
}

void Button::onPositionChange(sf::Vector2f new_position)
{
    locateText(getState(), new_position);
}

void Button::onSizeChange(sf::Vector2f new_size)
{
    if (getSize().x != 0 && getSize().y != 0)
    {
        m_button_default.setSize(new_size);
        m_button_hovered.setSize(new_size);
        sf::Vector2f new_size_pressed(new_size);
        new_size_pressed.y -= m_sagging * new_size.y / getSize().y;
        m_button_pressed.setSize(new_size_pressed);
        
        sf::Vector2f k = {new_size.x / getSize().x, new_size.y / getSize().y};
        
        m_sagging *= k.y;
        m_text_padding.x *= k.x;
        m_text_padding.y *= k.y;
        
        m_text.scale(k);
    }
    
    locateText(getState(), getPosition());
}

void Button::onStateChange(State new_state)
{
    locateText(new_state, getPosition());
}



// private:



void Button::locateText(State new_state, sf::Vector2f position)
{
    sf::Vector2f text_position(position + m_text_padding);
    text_position.x += getSize().x / 2.f;
    
    if (new_state == State::Pressed)
    {
        text_position.y += m_sagging;
    }
    
    m_text.setPosition(text_position);
}
