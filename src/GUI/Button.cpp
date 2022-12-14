#include "Button.h"

#include "../ResourceManager.h"



Button::Button(Theme theme, std::string text, CallbackType callback)
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
    
    m_hovered_sprite.setOrigin(0.f, m_hovered_sprite.getTexture()->getSize().y
                               - float(m_default_sprite.getTexture()->getSize().y));
    m_pressed_sprite.setOrigin(0.f, m_pressed_sprite.getTexture()->getSize().y
                               - float(m_default_sprite.getTexture()->getSize().y));
    
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
            if (getState() == Button::Default)
            {
                setState(Button::Hovered);
            }
        }
        else
        {
            if (getState() == Button::Hovered)
            {
                setState(Button::Default);
            }
        }
        break;
    }
    case sf::Event::MouseButtonPressed:
        if (getState() == Button::Hovered)
        {
            setState(Button::Pressed);
        }
        break;
    case sf::Event::MouseButtonReleased:
        if (getState() == Button::Pressed)
        {
            if (containsPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                setState(Button::Hovered);
            }
            else
            {
                setState(Button::Default);
            }
            
            m_callback();
        }
        break;
    default:
        break;
    }
}



// private:
