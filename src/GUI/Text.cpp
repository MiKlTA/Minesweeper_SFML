#include "Text.h"

#include "../Core/ResourceManager.h"



Text::Text(
        ResourceManager *resource_manager,
        const sf::RenderWindow &window,
        Alignment alignment, std::wstring text)
    : Widget(window),
      
      m_alignment(alignment)
{
    m_text = sf::Text(text, *resource_manager->getFont("font"));
    
    setCharacterSize(32);
}



void Text::setString(std::wstring text)
{
    m_text.setString(text);
    
    computeSize();
    computeTextPosition(getPosition());
}

void Text::setCharacterSize(unsigned int size)
{
    m_text.setCharacterSize(size);
    const_cast<sf::Texture&>(m_text.getFont()->getTexture(size)).setSmooth(false);
    computeSize();
}

void Text::setColor(const sf::Color &color)
{
    m_text.setFillColor(color);
}



void Text::append(wchar_t symbol)
{
    setString(getString() + symbol);
}

void Text::pop_back()
{
    std::wstring string = getString();
    if (!string.empty())
    {
        string.pop_back();
        setString(string);
    }
}



std::wstring Text::getString() const
{
    return m_text.getString().toWideString();
}




void Text::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}



bool Text::canBeFocused() const
{
    return false;
}



// private:



void Text::onPositionChange(sf::Vector2f new_position)
{
    computeTextPosition(new_position);
}



void Text::computeTextPosition(sf::Vector2f new_position)
{
    computeSize();
    
    sf::Vector2f position(new_position);
    position.y -= getSize().y / 2.f;
    
    switch (m_alignment)
    {
    case Alignment::Right:
        position.x -= getSize().x;
        break;
    case Alignment::Centre:
        position.x -= getSize().x / 2.f;
        break;
    case Alignment::Left:
        break;
    }
    
    m_text.setPosition(position);
}

void Text::computeSize()
{
    sf::Vector2f size(m_text.getLocalBounds().width, m_text.getCharacterSize() / 2);
    
    setSize(size);
}
