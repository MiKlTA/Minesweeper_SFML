#include "InputField.h"

#include "../ResourceManager.h"
#include "GUIKeyManager.h"



InputField::InputField(const sf::RenderWindow &window, Theme theme, Text::Alignment alignment)
    : Widget(window),
      
      m_text(window, alignment),
      
      m_only_numbers(false),
      
      m_theme(theme),
      m_alignment(alignment),
      
      m_field_default(window),
      m_field_active(window)
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



void InputField::draw(sf::RenderTarget &target, sf::RenderStates states) const
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



bool InputField::canBeFocused() const
{
    return true;
}



// private:



void InputField::onEvent_(const sf::Event &event)
{
    switch (getState())
    {
    case State::Default:
    case State::Hovered:
        if (event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button == GUIKeyManager::button("left")
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
                if (event.key.code == GUIKeyManager::key("backspace"))
                {
                    m_text.pop_back();
                    recalcTextPosition(getPosition());
                }
            }
        else if (event.type == sf::Event::TextEntered
                 && !sf::Keyboard::isKeyPressed(GUIKeyManager::key("backspace")))
        {
            wchar_t symbol = static_cast<wchar_t>(event.text.unicode);
            
            if ((!m_only_numbers || (symbol >= L'0' && symbol <= L'9'))
                    && m_text.getString().size() < m_max_text_length
                    && canPushSymbol(symbol))
            {
                m_text.append(symbol);
                recalcTextPosition(getPosition());
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
    recalcTextPosition(new_position);
}



// private:



void InputField::recalcTextPosition(sf::Vector2f new_field_position)
{
    sf::Vector2f position(new_field_position);
    switch (m_alignment)
    {
    case Text::Alignment::Left:
        position.x += m_text_padding;
        position.y += getSize().y / 2.f - m_text.getSize().y;
        break;
    case Text::Alignment::Right:
        position.x += getSize().x - m_text_padding;
        position.y += getSize().y / 2.f - m_text.getSize().y;
        break;
    case Text::Alignment::Centre:
        position.x += getSize().x / 2.f;
        position.y += getSize().y / 2.f - m_text.getSize().y;
        break;
    }
    
    m_text.setPosition(position);
}



bool InputField::canPushSymbol(wchar_t symbol)
{
    bool canPush;
    m_text.append(symbol);
    
    canPush = m_text.getSize().x + 2.f * m_text_padding < getSize().x;
    
    m_text.pop_back();
    
    return canPush;
}
