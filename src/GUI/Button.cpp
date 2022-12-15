#include "Button.h"

#include "../ResourceManager.h"



Button::Button(Theme theme, std::wstring text, CallbackType callback)
    : m_text(text),
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
    m_text_padding = {16.f, 0.f};
    
    
    m_sadding = float(m_default_sprite.getTexture()->getSize().y)
            - m_pressed_sprite.getTexture()->getSize().y;
    
    m_pressed_sprite.setOrigin(0.f, -m_sadding);
    
    setSize(sf::Vector2f(m_default_sprite.getTexture()->getSize()));
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



// protected:



void Button::onEvent_(const sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::MouseMoved:
    {
        if (containsPoint(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
        {
            if (getState() == State::Default)
            {
                setState(State::Hovered);
            }
        }
        else
        {
            if (getState() == State::Hovered)
            {
                setState(State::Default);
            }
        }
        break;
    }
    case sf::Event::MouseButtonPressed:
        if (getState() == State::Hovered)
        {
            setState(State::Pressed);
        }
        break;
    case sf::Event::MouseButtonReleased:
        if (getState() == State::Pressed)
        {
            if (containsPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                setState(State::Hovered);
            }
            else
            {
                setState(State::Default);
            }
            
            m_callback();
        }
        break;
    default:
        break;
    }
}

void Button::onSizeChange(sf::Vector2f new_size)
{
    if (getSize().x != 0 && getSize().y != 0)
    {
        sf::Vector2f k = {new_size.x / getSize().x, new_size.y / getSize().y};
        
        m_default_sprite.scale(k);
        m_hovered_sprite.scale(k);
        m_pressed_sprite.scale(k);
    }
}

void Button::onStateChange(State new_state)
{
    locateText(new_state);
}



// private:



void Button::locateText(State new_state)
{
    sf::Vector2f text_position(getPosition() + m_text_padding);
    
    if (new_state == State::Pressed)
    {
        text_position.y += m_sadding;
    }
    
    m_text.setPosition(text_position);
}
