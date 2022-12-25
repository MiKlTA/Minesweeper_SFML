#include "PopupYouSure.h"



PopupYouSure::PopupYouSure(ResourceManager *resource_manager, KeyManager *key_manager,
        const sf::RenderWindow &window, std::wstring title)
    : Widget(window),
      
      m_layout_vertical(key_manager, window,
                        Layout::Type::Vertical),
      m_layout_horisontal(key_manager, window,
                        Layout::Type::Horizontal),
      
      m_background(resource_manager, window),
      
      m_title(resource_manager, window,
             Text::Alignment::Left, L"Are you sure?"),
      
      m_go_back(resource_manager, key_manager, window,
                Button::Theme::Default, L"Back"),
      m_Im_sure(resource_manager, key_manager, window,
                Button::Theme::Default, L"I'm sure")
{
    m_layout_horisontal.addWidget(&m_go_back);
    m_layout_horisontal.addWidget(&m_Im_sure);
    
    m_layout_vertical.addWidget(&m_title);
    m_layout_vertical.addWidget(&m_layout_horisontal);
    
    m_go_back.setCallback([this](){
        this->setHide(true);
    });
    
    m_background.setImage("popup_you_sure");
    m_background.setSize(m_layout_vertical.getSize());
    
    setSize(m_background.getSize());
}



void PopupYouSure::setImSureCallback(Button::CallbackType callback_Im_sure)
{
    m_Im_sure.setCallback(callback_Im_sure);
}



bool PopupYouSure::canBeFocused() const
{
    return true;
}

bool PopupYouSure::isPassEvent(const sf::Event &event)
{
    return false;
}



// protected:



void PopupYouSure::onEvent_(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed
            && !containsPoint({event.mouseButton.x, event.mouseButton.y}))
    {
        setHide(true);
    }
    
    m_background.onEvent(event);
    m_layout_vertical.onEvent(event);
}

void PopupYouSure::onPositionChange(sf::Vector2f new_position)
{
    sf::Vector2f delta = new_position - getPosition();
    m_background.move(delta);
    m_layout_vertical.move(delta);
}



void PopupYouSure::draw_(sf::RenderTarget &target, sf::RenderStates) const
{
    target.draw(m_background);
    target.draw(m_layout_vertical);
}
