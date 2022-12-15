#include "Button.h"

#include "GUIKeyManager.h"

#include "../ResourceManager.h"



Button::Button(Theme theme, std::wstring text, CallbackType callback)
    : m_text(Text::Alignment::Centre, text),
      m_callback(callback)
{
    switch (theme)
    {
    case Theme::Blue:
        m_default_sprite = sf::Sprite(*ResourceManager::getTexture("blue_button_default"));
        m_hovered_sprite = sf::Sprite(*ResourceManager::getTexture("blue_button_hovered"));
        m_pressed_sprite = sf::Sprite(*ResourceManager::getTexture("blue_button_pressed"));
        break;
    case Theme::Red:
        m_default_sprite = sf::Sprite(*ResourceManager::getTexture("red_button_default"));
        m_hovered_sprite = sf::Sprite(*ResourceManager::getTexture("red_button_hovered"));
        m_pressed_sprite = sf::Sprite(*ResourceManager::getTexture("red_button_pressed"));
        break;
    }
    m_text_padding = {0.f, 16.f};
    
    m_sadding = float(m_default_sprite.getTexture()->getSize().y)
            - m_pressed_sprite.getTexture()->getSize().y;
    
    m_pressed_sprite.setOrigin(0.f, -m_sadding);
    
    
    
    setSize(sf::Vector2f(m_default_sprite.getTexture()->getSize()));
    
    m_text.setColor(sf::Color(150, 40, 10));
}



void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    switch (getState())
    {
    case Widget::Default:
        target.draw(m_default_sprite, states);
        break;
    case Widget::Hovered:
    case Widget::Focused:
        target.draw(m_hovered_sprite, states);
        break;
    case Widget::Pressed:
        target.draw(m_pressed_sprite, states);
        break;
    }
    
    target.draw(m_text);
}



bool Button::canBeFocused()
{
    return true;
}



// protected:



void Button::onEvent_(const sf::Event &event)
{
    switch (getState())
    {
    case State::Default:
        
        if (containsPoint(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
        {
           setState(State::Hovered); 
        }
        
        break;
    case State::Focused:
        
        if (event.type == sf::Event::KeyPressed
                && event.key.code == GUIKeyManager::key("enter"))
        {
            press();
        }
        
        break;
    case State::Hovered:
        
        if (!containsPoint(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
        {
           setState(State::Default); 
        }
        else if (event.type == sf::Event::KeyPressed
                 && event.key.code == GUIKeyManager::key("enter"))
        {
            press();
        }
        
        break;
    case State::Pressed:
        
        if (event.type == sf::Event::MouseButtonReleased
                    && event.mouseButton.button == sf::Mouse::Left)
        {
            setState(State::Default);
        }
        else if (event.type == sf::Event::KeyReleased
                 && event.key.code == GUIKeyManager::key("enter"))
        {
            setState(State::Focused);
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
        sf::Vector2f k = {new_size.x / getSize().x, new_size.y / getSize().y};
        
        m_default_sprite.scale(k);
        m_hovered_sprite.scale(k);
        m_pressed_sprite.scale(k);
        
        m_sadding *= k.y;
        m_text_padding.x *= k.x;
        m_text_padding.y *= k.y;
    }
}

void Button::onStateChange(State new_state)
{
    locateText(new_state, getPosition());
}



// private:



void Button::press()
{
    setState(State::Pressed);
    m_callback();
}



void Button::locateText(State new_state, sf::Vector2f position)
{
    sf::Vector2f text_position(position + m_text_padding);
    text_position.x += getSize().x / 2.f;
    
    if (new_state == State::Pressed)
    {
        text_position.y += m_sadding;
    }
    
    m_text.setPosition(text_position);
}
