#include "InputField.h"

#include "../Core/ResourceManager.h"
#include "../Core/KeyManager.h"



InputField::InputField(
        ResourceManager *resource_manager, KeyManager *key_manager,
        const sf::RenderWindow &window,
        Theme theme, Text::Alignment alignment)
    : Widget(window),
      
      m_key_manager(key_manager),
      
      m_text(resource_manager, window, alignment),
      
      m_only_numbers(false),
      
      m_theme(theme),
      m_alignment(alignment),
      
      m_field_default(resource_manager, window),
      m_field_active(resource_manager, window)
{
    switch (theme)
    {
    case Theme::Blue:
        m_field_default.setImage("blue_input_field_default");
        m_field_active.setImage("blue_input_field_active");
        m_text.setColor(sf::Color::Cyan);
        m_text_padding = 16.f;
        
        m_max_text_length = 256;
        break;
    }
    
    setSize(sf::Vector2f(m_field_default.getSize()));
}



void InputField::onlyNumbers(bool isOnlyNumbers)
{
    m_only_numbers = isOnlyNumbers;
}



std::wstring InputField::getText() const
{
    return m_text.getString();
}



// private:



bool InputField::canBeFocused_() const
{
    return true;
}



void InputField::onEvent_(const sf::Event &event)
{
    switch (getState())
    {
    case State::Default:
    case State::Hovered:
        if (event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button == m_key_manager->button("left")
                && containsPoint({event.mouseButton.x, event.mouseButton.y})
                )
        {
            setState(State::Pressed);
        }
        break;
    case State::Pressed:
        
        if (event.type == sf::Event::MouseButtonPressed
                && !containsPoint({event.mouseButton.x, event.mouseButton.y}))
        {
            setState(State::Default);
        }
        
        // continue!
    case State::Focused:
        
        if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == m_key_manager->key("backspace"))
                {
                    m_text.pop_back();
                }
            }
        else if (event.type == sf::Event::TextEntered
                 && !sf::Keyboard::isKeyPressed(m_key_manager->key("backspace")))
        {
            wchar_t symbol = static_cast<wchar_t>(event.text.unicode);
            
            if ((!m_only_numbers || (symbol >= L'0' && symbol <= L'9'))
                    && m_text.canPushSymbol(symbol))
            {
                m_text.append(symbol);
            }
        }
        
        break;
    }
}

void InputField::onSizeChange(sf::Vector2f new_size)
{
    m_text.setSize(new_size);
    
    m_field_default.setSize(new_size);
    m_field_active.setSize(new_size);
    
    if (getSize().x != 0 && getSize().y != 0)
    {
        sf::Vector2f k = {new_size.x / getSize().x, new_size.y / getSize().y};
        
        m_text_padding *= k.x;
    }
}

void InputField::onPositionChange(sf::Vector2f new_position)
{
    m_text.setPosition(new_position);
}



void InputField::draw_(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    
    switch (getState())
    {
    case State::Default:
    case State::Hovered:
        target.draw(m_field_default, states);
        break;
    case State::Focused:
    case State::Pressed:
        target.draw(m_field_active, states);
        break;
    }
    
    target.draw(m_text);
}
