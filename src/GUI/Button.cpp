#include "Button.h"

#include "../Core/ResourceManager.h"
#include "../Core/SoundManager.h"
#include "../Core/KeyManager.h"



Button::Button(ResourceManager *resource_manager, SoundManager *sound_manager,
               KeyManager *key_manager,
               const sf::RenderWindow &window,
               Theme theme, std::wstring text)
    : Widget(window),
      
      m_key_manager(key_manager),
      
      m_text(resource_manager, window, Text::Alignment::Centre, text),
      
      m_callback([](){}),
      
      m_button_default(resource_manager, window),
      m_button_hovered(resource_manager, window),
      m_button_pressed(resource_manager, window),
      
      m_hover_sound(*sound_manager->getSoundBuffer("click2")),
      m_press_sound(*sound_manager->getSoundBuffer("click1"))
{
    switch (theme)
    {
    case Theme::Default:
        m_button_default.setImage("button_default");
        m_button_hovered.setImage("button_hovered");
        m_button_pressed.setImage("button_pressed");
        break;
    }
    m_text_padding = {0.f, -2.f};
    
    m_sagging = float(m_button_default.getSize().y) - m_button_pressed.getSize().y;
    
    
    
    setSize(sf::Vector2f(m_button_default.getSize()));
    
    m_text.setColor(sf::Color(150, 40, 10));
    locateText(getState(), getSize(), getPosition());
}



void Button::setCharacterSize(unsigned int character_size)
{
    m_text.setCharacterSize(character_size);
    locateText(getState(), getSize(), getPosition());
}

void Button::setCallback(CallbackType callback)
{
    m_callback = callback;
}



// protected:



bool Button::canBeFocused_() const
{
    return true;
}



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
    locateText(getState(), getSize(), new_position);
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
        
        locateText(getState(), new_size, getPosition());
    }
}

void Button::onStateChange(State new_state)
{
    locateText(new_state, getSize(), getPosition());
    
    if (getState() == State::Default
            && (new_state == State::Hovered || new_state == State::Focused))
    {
        m_hover_sound.play();
    }
    else if ((getState() == State::Hovered || getState() == State::Focused)
             && new_state == State::Pressed)
    {
        m_press_sound.play();
    }
}



void Button::draw_(sf::RenderTarget &target, sf::RenderStates states) const
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



// private:



void Button::locateText(State new_state, sf::Vector2f new_size, sf::Vector2f new_position)
{
    sf::Vector2f text_position(new_position + m_text_padding);
    text_position.x += new_size.x / 2.f;
    text_position.y += new_size.y / 2.f - m_text.getSize().y / 2.f;
    
    if (new_state == State::Pressed)
    {
        text_position.y += m_sagging;
    }
    
    m_text.setPosition(text_position);
}
