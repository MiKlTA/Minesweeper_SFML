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
    m_padding = padding;
}

void Layout::setMargin(float margin)
{
    m_margin = margin;
}



void Layout::addWidget(Widget *widget)
{
    calcPositionWidget(widget);
    
    addLayoutSizeBy(widget);
    
    m_contains.push_back(widget);
}



void Layout::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= m_transform;
    for (auto widget_iter = m_contains.begin(); widget_iter != m_contains.end(); ++widget_iter)
    {
        target.draw(**widget_iter, states);
    }
    
    if (need_draw_border)
    {
        target.draw(m_border, states);
    }
}



// protected:



void Layout::onEvent_(const sf::Event &event)
{
    
    for (auto widget_iter = m_contains.begin(); widget_iter != m_contains.end(); ++widget_iter)
    {
        (*widget_iter)->onEvent(event);
    }
}

void Layout::onSizeChange(sf::Vector2f new_size)
{
    m_border.setSize(new_size);
}

void Layout::onPositionChange(sf::Vector2f new_position)
{
    m_border.setPosition(new_position);
    
    for (auto widget_iter = m_contains.begin(); widget_iter != m_contains.end(); ++widget_iter)
    {
        Widget *widget = *widget_iter;
        widget->move(new_position - getPosition());
    }
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



void Layout::addLayoutSizeBy(Widget *widget)
{
    if (m_contains.empty())
    {
        setSize({2.f*padding(), 2.f*padding()});
    }
    
    float new_width;
    float new_height;
    
    if (m_type == Type::Horizontal)
    {
        new_width = getSize().x + widget->getSize().x;
        if (!m_contains.empty())
        {
            new_width += margin();
        }
        new_height = std::max(getSize().y, widget->getSize().y + 2.f*padding());
    }
    else // m_type == Type::Vertical
    {
        new_width = std::max(getSize().x, widget->getSize().x + 2.f*padding());
        new_height = getSize().y + widget->getSize().y;
        if (!m_contains.empty())
        {
            new_height += margin();
        }
    }
    
    setSize({new_width, new_height});
}

void Layout::calcPositionWidget(Widget *widget)
{
    if (m_contains.empty())
    {
        widget->move(getPosition() + sf::Vector2f(padding(), padding()));
    }
    else
    {
        Widget *prev_widget = *std::prev(m_contains.end());
        sf::Vector2f shift;
        if (m_type == Type::Horizontal)
        {
            shift = sf::Vector2f(prev_widget->getSize().x + margin(), 0.f);
        }
        else // m_type == Type::Vertical
        {
            shift = sf::Vector2f(0.f, prev_widget->getSize().y + margin());
        }
        widget->setPosition(prev_widget->getPosition() + shift);
    }
}



void Layout::setFocus()
{
    setState(Widget::Focused);
    m_border.setOutlineColor(sf::Color::Green);
}

void Layout::unfocus()
{
    setState(Widget::Default);
    m_border.setOutlineColor(sf::Color::Red);
}
