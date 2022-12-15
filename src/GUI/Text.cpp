#include "Text.h"

#include "../ResourceManager.h"



Text::Text(std::wstring text)
{
    m_text = sf::Text(text, *ResourceManager::getFont("font"));
    
    m_text.setCharacterSize(32);
}



void Text::setString(std::wstring text)
{
    m_text.setString(text);
}

void Text::setCharacterSize(unsigned int size)
{
    m_text.setCharacterSize(size);
}




void Text::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_text, states);
}
