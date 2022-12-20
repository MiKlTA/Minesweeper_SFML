#include "ProgressBar.h"

#include "../ResourceManager.h"

#include <cmath>



ProgressBar::ProgressBar(
        const sf::RenderWindow &window, Type type,
        unsigned int elements_count, float elements_interval)
    : Widget(window),
      
      m_bar(window),
      
      m_type(type),
      
      m_elements_count(elements_count),
      m_elements_interval(elements_interval)
{
    m_bar.setImage("bar");
    
    m_progress_element.setTexture(*ResourceManager::getTexture("progress_element"));
    
    m_padding = 16.f;
    
    setSize(m_bar.getSize());
}



void ProgressBar::setProgressValue(float value)
{
    m_progress = value;
}



void ProgressBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    const sf::Vector2f element_size(m_progress_element.getGlobalBounds().width,
                                    m_progress_element.getGlobalBounds().height);
    
    target.draw(m_bar);
    
    states.transform.translate(getPosition());
    switch (m_type)
    {
    case Type::Horisontal:
        states.transform.translate({m_padding, getSize().y / 2.f - element_size.y / 2.f});
        
        for (unsigned int i = 0; i < progress(); ++i)
        {
            target.draw(m_progress_element, states);
            states.transform.translate({m_elements_interval + element_size.x, 0.f});
        }
        break;
    case Type::Vertical:
        
        for (unsigned int i = 0; i < progress(); ++i)
        {
            target.draw(m_progress_element);
        }
        break;
    }
}



bool ProgressBar::canBeFocused() const
{
    return false;
}



// protected:



void ProgressBar::onSizeChange(sf::Vector2f new_size)
{
    recalcProgressElementSize(new_size);
}

void ProgressBar::onPositionChange(sf::Vector2f new_position)
{
    m_bar.setPosition(new_position);
}



// private:



void ProgressBar::recalcProgressElementSize(sf::Vector2f widget_size)
{
    const sf::Vector2f element_size(m_progress_element.getTexture()->getSize());
    sf::Vector2f scale;
    
    switch (m_type)
    {
    case Type::Horisontal:
        scale.x = (widget_size.x - 2.f * m_padding - (m_elements_count - 1) * m_elements_interval)
                / float(m_elements_count);
        scale.x /= element_size.x;
        scale.y = 1.f;
        break;
    case Type::Vertical:
        scale.x = 1.f;
        scale.y = (widget_size.y - 2.f * m_padding - (m_elements_count - 1) * m_elements_interval)
                / float(m_elements_count);
        scale.y /= element_size.y;
        break;
    }
    
    m_progress_element.scale(scale);
}

unsigned int ProgressBar::progress() const
{
    return std::round(m_elements_count * m_progress);
}
