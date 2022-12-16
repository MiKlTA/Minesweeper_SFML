#include "InputField.h"

#include "../ResourceManager.h"
#include "GUIKeyManager.h"



InputField::InputField(Theme theme, Text::Alignment alignment)
    : m_text(alignment),
      
      m_only_numbers(false),
      
      m_theme(theme),
      m_alignment(alignment)
{
    switch (theme)
    {
    case Theme::Blue:
        m_default_sprite = sf::Sprite(*ResourceManager::getTexture("blue_input_field_default"));
        m_active_sprite = sf::Sprite(*ResourceManager::getTexture("blue_input_field_active"));
        m_text.setColor(sf::Color::Cyan);
        m_text_padding = {16.f, 16.f};
        
        m_max_text_length = 256;
        break;
    }
    
    setSize(sf::Vector2f(m_default_sprite.getTexture()->getSize()));
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
        target.draw(m_default_sprite, states);
        break;
    case State::Focused:
    case State::Pressed:
        target.draw(m_active_sprite, states);
        break;
    }
    
    target.draw(m_text);
}



bool InputField::canBeFocused()
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
                && containsPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))
                )
        {
            setState(State::Pressed);
        }
        break;
    case State::Pressed:
        
        if (event.type == sf::Event::MouseButtonPressed
                && !containsPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
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
    
    if (getSize().x != 0 && getSize().y != 0)
    {
        sf::Vector2f k = {new_size.x / getSize().x, new_size.y / getSize().y};
        
        m_default_sprite.scale(k);
        m_active_sprite.scale(k);
        
        m_text_padding.x *= k.x;
        m_text_padding.y *= k.y;
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
        position += m_text_padding;
        break;
    case Text::Alignment::Right:
        position.y += m_text_padding.y;
        position.x += getSize().x - m_text_padding.x;
        break;
    case Text::Alignment::Centre:
        position.y += m_text_padding.y;
        position.x += getSize().x / 2.f;
        break;
    }
    
    m_text.setPosition(position);
}



bool InputField::canPushSymbol(wchar_t symbol)
{
    bool canPush;
    m_text.append(symbol);
    
    canPush = m_text.getSize().x + 2.f * m_text_padding.x < getSize().x;
    
    m_text.pop_back();
    
    return canPush;
}
