#include "PopupGameSettings.h"



PopupGameSettings::PopupGameSettings(Game *game)
    : Widget(*game->getWindow()),
      
      m_layout(game->getKeyManager(), *game->getWindow(),
               Layout::Type::Vertical, Layout::Alignment::Left),
      
      m_background(game->getResourceManager(), *game->getWindow()),
      
      m_go_back(game->getResourceManager(), game->getKeyManager(), *game->getWindow(),
                Button::Theme::Default, L"Back"),
      m_start(game->getResourceManager(), game->getKeyManager(), *game->getWindow(),
                Button::Theme::Default, L"Start!")
{
    m_layout.addWidget(&m_go_back);
    m_layout.addWidget(&m_start);
    
    m_go_back.setCallback([this](){
        this->setHide(!this->isHidden());
    });
    
    
    
    m_background.setImage("popup_game_settings");
    m_background.setSize(m_layout.getSize());
    
    setSize(m_background.getSize());
    
    game->goToCentre(this);
}

bool PopupGameSettings::isPassEvent(const sf::Event &event)
{
    return false;
}



// protected:



bool PopupGameSettings::canBeFocused_() const
{
    return true;
}



void PopupGameSettings::onEvent_(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed
            && !containsPoint({event.mouseButton.x, event.mouseButton.y}))
    {
        setHide(true);
    }
    
    m_background.onEvent(event);
    m_layout.onEvent(event);
}

void PopupGameSettings::onPositionChange(sf::Vector2f new_position)
{
    sf::Vector2f delta = new_position - getPosition();
    m_background.move(delta);
    m_layout.move(delta);
}

void PopupGameSettings::onStateChange(State new_state)
{
    m_layout.setState(new_state);
}



void PopupGameSettings::draw_(sf::RenderTarget &target, sf::RenderStates) const
{
    target.draw(m_background);
    target.draw(m_layout);
}
