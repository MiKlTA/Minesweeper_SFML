#include "PopupGameSettings.h"



PopupGameSettings::PopupGameSettings(Core *core, Game *game)
    : Widget(*core->getWindow()),
      
      m_main_layout(core->getKeyManager(), *core->getWindow(),
                    Layout::Type::Vertical, Layout::Alignment::Centre),
      m_scrollbars_layout(core->getKeyManager(), *core->getWindow(),
                          Layout::Type::Vertical, Layout::Alignment::Left),
      m_labels_layout(core->getKeyManager(), *core->getWindow(),
                      Layout::Type::Vertical, Layout::Alignment::Right),
      m_main_horisontal_layout(core->getKeyManager(), *core->getWindow(),
                               Layout::Type::Horizontal, Layout::Alignment::Left),
      m_buttons_layout(core->getKeyManager(), *core->getWindow(),
                       Layout::Type::Horizontal, Layout::Alignment::Centre),
      
      m_background(core->getResourceManager(), *core->getWindow()),
      
      
      
      m_field_width(core->getResourceManager(), core->getKeyManager(),
                    *core->getWindow(), ScrollBar::Theme::Default,
                    ScrollBar::Type::Horisontal, game->getMaxFieldSize().x),
      m_field_height(core->getResourceManager(), core->getKeyManager(),
                     *core->getWindow(), ScrollBar::Theme::Default,
                     ScrollBar::Type::Horisontal, game->getMaxFieldSize().y),
      m_mines_count(core->getResourceManager(), core->getKeyManager(),
                    *core->getWindow(), ScrollBar::Theme::Default,
                    ScrollBar::Type::Horisontal, game->getMaxTotalMinesNumber()),
      m_ducks_count(core->getResourceManager(), core->getKeyManager(),
                    *core->getWindow(), ScrollBar::Theme::Default,
                    ScrollBar::Type::Horisontal, game->getMaxTotalDucksNumber()),
      
      m_field_width_label(core->getResourceManager(), *core->getWindow(),
                          Text::Alignment::Right,
                          std::to_wstring(game->getFieldSize().x)),
      m_field_height_label(core->getResourceManager(), *core->getWindow(),
                           Text::Alignment::Right,
                           std::to_wstring(game->getFieldSize().y)),
      m_mines_count_label(core->getResourceManager(), *core->getWindow(),
                          Text::Alignment::Right,
                          std::to_wstring(game->getTotalMinesNumber())),
      m_ducks_count_label(core->getResourceManager(), *core->getWindow(),
                          Text::Alignment::Right,
                          std::to_wstring(game->getTotalDucksNumber())),
      
      
      m_go_back(core->getResourceManager(), core->getKeyManager(), *core->getWindow(),
                Button::Theme::Default, L"Back"),
      m_start(core->getResourceManager(), core->getKeyManager(), *core->getWindow(),
                Button::Theme::Default, L"Start!")
{
    Layout::need_draw_border = true;
    
    m_buttons_layout.addWidget(&m_go_back);
    m_buttons_layout.addWidget(&m_start);
    
    m_scrollbars_layout.addWidget(&m_field_width);
    m_scrollbars_layout.addWidget(&m_field_height);
    m_scrollbars_layout.addWidget(&m_mines_count);
    m_scrollbars_layout.addWidget(&m_ducks_count);
    
    m_labels_layout.addWidget(&m_field_width_label);
    m_labels_layout.addWidget(&m_field_height_label);
    m_labels_layout.addWidget(&m_mines_count_label);
    m_labels_layout.addWidget(&m_ducks_count_label);
    
    m_main_horisontal_layout.addWidget(&m_scrollbars_layout);
    m_main_horisontal_layout.addWidget(&m_labels_layout);
    
    m_main_layout.addWidget(&m_main_horisontal_layout);
    m_main_layout.addWidget(&m_buttons_layout);
    
    m_go_back.setCallback([this](){
        this->setHide(!this->isHidden());
    });
    
    
    
    m_background.setImage("popup_game_settings");
    m_background.setSize(m_main_layout.getSize());
    
    setSize(m_background.getSize());
    
    core->goToCentre(this);
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
    m_main_layout.onEvent(event);
}

void PopupGameSettings::onPositionChange(sf::Vector2f new_position)
{
    sf::Vector2f delta = new_position - getPosition();
    m_background.move(delta);
    m_main_layout.move(delta);
}

void PopupGameSettings::onStateChange(State new_state)
{
    m_main_layout.setState(new_state);
}



void PopupGameSettings::draw_(sf::RenderTarget &target, sf::RenderStates) const
{
    
    target.draw(m_background);
    target.draw(m_main_layout);
}
