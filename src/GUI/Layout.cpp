#include "Layout.h"



bool Layout::need_draw_border = false;



Layout::Layout(Type type)
    : m_type(type),
      m_padding(30.f),
      m_margin(50.f)
{
    m_border.setFillColor(sf::Color::Transparent);
    m_border.setOutlineColor(sf::Color::Red);
    m_border.setOutlineThickness(1.f);
}



void Layout::setPadding(float padding)
{
    
}

void Layout::setMargin(float margin)
{
    
}

void Layout::recomputeSize()
{
    
    
    updateBorder();
}



void Layout::addWidget(Widget *widget)
{
    
}



void Layout::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (need_draw_border)
    {
        target.draw(m_border, states);
    }
}



// protected:



void Layout::onEvent_(const sf::Event &event)
{
    
}

void Layout::onSizeChange(sf::Vector2f new_size)
{
    m_border.setSize(new_size);
}

void Layout::onPositionChange(sf::Vector2f new_position)
{
    m_border.setPosition(new_position);
}



// private:



float Layout::padding() const
{
    return m_padding;
}

float Layout::margin() const
{
    return m_margin;
}



void Layout::setFocus()
{
    setState(Widget::Focused);
}

void Layout::unfocus()
{
    setState(Widget::Default);
}

void Layout::updateBorder()
{
    m_border.setPosition(getPosition());
    m_border.setSize(getSize());
}
