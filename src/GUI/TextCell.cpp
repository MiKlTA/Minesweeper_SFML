#include "TextCell.h"

#include "../Core/ResourceManager.h"



TextCell::TextCell(ResourceManager *resource_manager, const sf::RenderWindow &window,
                   Text::Alignment alignment, std::wstring text)
    : Widget(window),
      
      m_text(resource_manager, window, alignment, text),
      
      m_only_numbers(false),
      m_max_text_length(42000),
      
      m_alignment(alignment),
      m_text_padding(),
      m_text_shift()
{
    
}



void TextCell::setString(std::wstring string)
{
    m_text.setString(string);
    
    recalcTextPosition(getPosition());
}

void TextCell::setColor(sf::Color color)
{
    m_text.setColor(color);
}

void TextCell::setCharacterSize(unsigned int size)
{
    m_text.setCharacterSize(size);
}

void TextCell::append(wchar_t symbol)
{
    m_text.append(symbol);
    
    recalcTextPosition(getPosition());
}

void TextCell::pop_back()
{
    m_text.pop_back();
    
    recalcTextPosition(getPosition());
}



void TextCell::setTextPadding(float text_padding)
{
    m_text_padding = text_padding;
}

void TextCell::setTextShift(sf::Vector2f text_shift)
{
    m_text_shift = text_shift;
}



void TextCell::setMaxTextLength(unsigned int max_text_length)
{
    m_max_text_length = max_text_length;
}



std::wstring TextCell::getString() const
{
    return m_text.getString();
}



bool TextCell::canPushSymbol(wchar_t symbol)
{
    bool canPush;
    m_text.append(symbol);
    
    canPush = m_text.getSize().x + 2.f * m_text_padding < getSize().x;
    
    m_text.pop_back();
    
    return canPush && m_text.getString().size() + 1 <= m_max_text_length;
}



// private:



bool TextCell::canBeFocused_() const
{
    return false;
}



void TextCell::onSizeChange(sf::Vector2f new_size)
{
    m_text.setSize(new_size);
    
    if (getSize().x != 0 && getSize().y != 0)
    {
        sf::Vector2f k = {new_size.x / getSize().x, new_size.y / getSize().y};
        
        m_text_padding *= k.x;
    }
}

void TextCell::onPositionChange(sf::Vector2f new_position)
{
    recalcTextPosition(new_position);
}



void TextCell::draw_(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_text);
}



// private:



void TextCell::recalcTextPosition(sf::Vector2f new_field_position)
{
    sf::Vector2f position(new_field_position);
    switch (m_alignment)
    {
    case Text::Alignment::Left:
        position.x += m_text_padding;
        position.y += getSize().y / 2.f - m_text.getSize().y / 2.f;
        break;
    case Text::Alignment::Right:
        position.x += getSize().x - m_text_padding;
        position.y += getSize().y / 2.f - m_text.getSize().y / 2.f;
        break;
    case Text::Alignment::Centre:
        position.x += getSize().x / 2.f;
        position.y += getSize().y / 2.f - m_text.getSize().y / 2.f;
        break;
    }
    
    m_text.setPosition(position);
}
