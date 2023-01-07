#include "PopupYouSure.h"



PopupYouSure::PopupYouSure(ResourceManager *resource_manager, KeyManager *key_manager,
        const sf::RenderWindow &window, Text *title)
    : Widget(window),
      
      m_layout_vertical(new Layout(key_manager, window,
                        Layout::Type::Vertical, Layout::Alignment::Centre)),
      m_layout_horisontal(new Layout(key_manager, window,
                        Layout::Type::Horizontal, Layout::Alignment::Left)),
      
      m_background(new Image(resource_manager, window)),
      
      m_title(title),
      
      m_go_back(new Button(resource_manager, key_manager, window,
                Button::Theme::Default, L"Back")),
      m_Im_sure(new Button(resource_manager, key_manager, window,
                Button::Theme::Default, L"I'm sure"))
{
    m_layout_vertical->setPadding({20.f, 40.f, 20.f, 20.f});
    m_layout_vertical->setMargin(10.f);
    
    m_layout_horisontal->addWidget(m_go_back);
    m_layout_horisontal->addWidget(m_Im_sure);
    
    m_layout_vertical->addWidget(m_title);
    m_layout_vertical->addWidget(m_layout_horisontal);
    
    m_go_back->setCallback([this](){
        this->setHide(true);
    });
    
    m_background->setImage("popup_you_sure");
    m_background->setSize(m_layout_vertical->getSize());
    
    setSize(m_background->getSize());
}

PopupYouSure::~PopupYouSure()
{
    delete m_layout_vertical;
    delete m_layout_horisontal;
    
    delete m_background;
    
    delete m_title;
    
    delete m_go_back;
    delete m_Im_sure;
}



void PopupYouSure::setImSureCallback(Button::CallbackType callback_Im_sure)
{
    m_Im_sure->setCallback(callback_Im_sure);
}

bool PopupYouSure::isPassEvent(const sf::Event &event)
{
    return false;
}



// protected:



bool PopupYouSure::canBeFocused_() const
{
    return true;
}



void PopupYouSure::onEvent_(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed
            && !containsPoint({event.mouseButton.x, event.mouseButton.y}))
    {
        setHide(true);
    }
    
    m_background->onEvent(event);
    m_layout_vertical->onEvent(event);
}

void PopupYouSure::onPositionChange(sf::Vector2f new_position)
{
    sf::Vector2f delta = new_position - getPosition();
    m_background->move(delta);
    m_layout_vertical->move(delta);
}

void PopupYouSure::onStateChange(State new_state)
{
    m_layout_vertical->setState(new_state);
}



void PopupYouSure::draw_(sf::RenderTarget &target, sf::RenderStates) const
{
    target.draw(*m_background);
    target.draw(*m_layout_vertical);
}
