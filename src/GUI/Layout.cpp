#include "Layout.h"

#include "../Core/KeyManager.h"



bool Layout::need_draw_border = false;



Layout::Layout(KeyManager *key_manager, const sf::RenderWindow &window, Type type)
    : Widget(window),
      
      m_key_manager(key_manager),
      
      m_focused_widget(m_contains.end()),
      
      m_type(type),
      m_padding(20.f, 20.f),
      m_margin(50.f)
{
    m_border.setFillColor(sf::Color::Transparent);
    m_border.setOutlineColor(sf::Color::Red);
    m_border.setOutlineThickness(2.f);
}



void Layout::setPadding(sf::Vector2f padding)
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



bool Layout::canBeFocused() const
{
    return true;
}

bool Layout::isPassEvent(const sf::Event &event)
{
    bool isPass = true;
    if (!m_contains.empty())
    {
        if (m_type == Type::Horizontal)
        {
            if (event.key.code == m_key_manager->key("right"))
            {
                isPass = m_focused_widget == getPrevFocusableWidget(m_contains.end());
            }
            else if (event.key.code == m_key_manager->key("left"))
            {
                isPass = m_focused_widget == m_contains.begin();
                if (!(*m_contains.begin())->canBeFocused())
                {
                    isPass |= m_focused_widget == getNextFocusableWidget(m_contains.begin());
                }
            }
        }
        else // m_type == Type::Vertical
        {
            if (event.key.code == m_key_manager->key("down"))
            {
                isPass = m_focused_widget == getPrevFocusableWidget(m_contains.end());
            }
            else if (event.key.code == m_key_manager->key("up"))
            {
                isPass = m_focused_widget == m_contains.begin();
                if (!(*m_contains.begin())->canBeFocused())
                {
                    isPass |= m_focused_widget == getNextFocusableWidget(m_contains.begin());
                }
            }
        }
    }
    if (m_focused_widget != m_contains.end())
    {
        isPass &= (*m_focused_widget)->isPassEvent(event);
    }
    return isPass;
}



// protected:



void Layout::onEvent_(const sf::Event &event)
{
    bool canIPassEvent = true;
    bool focused_widget_ready = true;
    if (m_focused_widget != m_contains.end())
    {
        focused_widget_ready = (*m_focused_widget)->isPassEvent(event);
    }
    if (getState() == State::Focused)
    {
        if (event.type == sf::Event::KeyPressed && focused_widget_ready)
        {
            if (m_type == Type::Horizontal)
            {
                if (event.key.code == m_key_manager->key("right"))
                {
                    setFocusOnNextWidget();
                    canIPassEvent = false;
                }
                else if (event.key.code == m_key_manager->key("left"))
                {
                    setFocusOnPrevWidget();
                    canIPassEvent = false;
                }
            }
            else // m_type == Type::Vertical
            {
                if (event.key.code == m_key_manager->key("down"))
                {
                    setFocusOnNextWidget();
                    canIPassEvent = false;
                }
                else if (event.key.code == m_key_manager->key("up"))
                {
                    setFocusOnPrevWidget();
                    canIPassEvent = false;
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            setState(State::Default);
        }
    }
    
    if (canIPassEvent)
    {
        for (auto widget_iter = m_contains.begin(); widget_iter != m_contains.end(); ++widget_iter)
        {
            (*widget_iter)->onEvent(event);
        }
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

void Layout::onStateChange(State new_state)
{
    if (new_state == State::Focused)
    {
        m_border.setOutlineColor(sf::Color::Green);
        
        if (m_focused_widget == m_contains.end())
        {
            m_focused_widget = getNextFocusableWidgetFromBegin();
        }
        (*m_focused_widget)->setState(State::Focused);
    }
    else
    {
        m_border.setOutlineColor(sf::Color::Red);
        
        if (m_focused_widget != m_contains.end())
        {
            (*m_focused_widget)->setState(State::Default);
        }
    }
}



void Layout::draw_(sf::RenderTarget &target, sf::RenderStates states) const
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



// private:



sf::Vector2f Layout::padding() const
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
        setSize(2.f*padding());
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
        new_height = std::max(getSize().y, widget->getSize().y + 2.f*padding().y);
    }
    else // m_type == Type::Vertical
    {
        new_width = std::max(getSize().x, widget->getSize().x + 2.f*padding().x);
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
        widget->move(getPosition() + padding());
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



Layout::ListIterator Layout::getNextFocusableWidget(ListIterator iter)
{
    iter = std::next(iter);
    while (iter != m_contains.end() && !(*iter)->canBeFocused())
    {
        iter = std::next(iter);
    }
    
    return iter;
}

Layout::ListIterator Layout::getPrevFocusableWidget(ListIterator iter)
{
    iter = std::prev(iter);
    while (iter != m_contains.begin() && !(*iter)->canBeFocused())
    {
        iter = std::prev(iter);
    }
    
    return iter;
}

Layout::ListIterator Layout::getNextFocusableWidgetFromBegin()
{
    if ((*m_contains.begin())->canBeFocused())
    {
        return m_contains.begin();
    }
    else
    {
        return getNextFocusableWidget(m_contains.begin());
    }
}

void Layout::setFocusOnNextWidget()
{
    (*m_focused_widget)->setState(State::Default);
    
    m_focused_widget = getNextFocusableWidget(m_focused_widget);
    
    if (m_focused_widget == m_contains.end())
    {
        m_focused_widget = getNextFocusableWidgetFromBegin();
    }
    (*m_focused_widget)->setState(State::Focused);
}

void Layout::setFocusOnPrevWidget()
{
    (*m_focused_widget)->setState(State::Default);
    
    if (m_focused_widget == m_contains.begin())
    {
        m_focused_widget = getPrevFocusableWidget(m_contains.end());
    }
    else
    {
        m_focused_widget = getPrevFocusableWidget(m_focused_widget);
    }
    
    (*m_focused_widget)->setState(State::Focused);
}

bool Layout::haveTargetsForFocus()
{
    for (Widget *widget : m_contains)
    {
        if (widget->canBeFocused())
            return true;
    }
    return false;

}
