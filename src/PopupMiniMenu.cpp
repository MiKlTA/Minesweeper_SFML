#include "PopupMiniMenu.h"

#include "Scenes/GameScene.h"



PopupMiniMenu::PopupMiniMenu(Core *core, Game *game, GameWidget *game_widget)
    : Widget(*core->getWindow()),
      
      m_layout_vertical(core->getKeyManager(), *core->getWindow(),
                        Layout::Type::Vertical, Layout::Alignment::Centre),
      
      m_background(core->getResourceManager(), *core->getWindow()),
      
      m_back(core->getResourceManager(), core->getSoundManager(),
             core->getKeyManager(), *core->getWindow(),
             Button::Theme::Default, L"Back"),
      m_go_settings(core->getResourceManager(), core->getSoundManager(),
                    core->getKeyManager(), *core->getWindow(),
                    Button::Theme::Default, L"Settings"),
      m_quit_and_save(core->getResourceManager(), core->getSoundManager(),
                      core->getKeyManager(), *core->getWindow(),
                      Button::Theme::Default, L"Quit and save")
{
    m_back.setCallback([this](){
        this->setHide(true);
    });
    m_go_settings.setCallback([this](){
        m_popup_game_settings->setHide(false);
    });
    m_quit_and_save.setCallback([this](){
        this->setHide(true);
    });
    
    m_layout_vertical.setPadding({20.f, 20.f, 20.f, 20.f});
    m_layout_vertical.setMargin(10.f);
    m_layout_vertical.addWidget(&m_back);
    m_layout_vertical.addWidget(&m_go_settings);
    m_layout_vertical.addWidget(&m_quit_and_save);
    
    m_background.setImage("window");
    m_background.setSize(m_layout_vertical.getSize());
    
    
    
    m_popup_game_settings = new PopupGameSettings(core, game, [game_widget, this](){
        game_widget->newGame();
        m_popup_game_settings->setHide(true);
        this->setHide(true);
    });
    m_popup_game_settings->setHide(true);
    
    setSize(m_background.getSize());
}



bool PopupMiniMenu::isPassEvent(const sf::Event &event)
{
    return false;
}



// protected:



bool PopupMiniMenu::canBeFocused_() const
{
    return true;
}



void PopupMiniMenu::onEvent_(const sf::Event &event)
{
    m_background.onEvent(event);
    m_layout_vertical.onEvent(event);
    
    m_popup_game_settings->onEvent(event);
}

void PopupMiniMenu::onPositionChange(sf::Vector2f new_position)
{
    sf::Vector2f delta = new_position - getPosition();
    m_background.move(delta);
    m_layout_vertical.move(delta);
}

void PopupMiniMenu::onStateChange(State new_state)
{
    m_layout_vertical.setState(new_state);
}



void PopupMiniMenu::draw_(sf::RenderTarget &target, sf::RenderStates) const
{
    target.draw(m_background);
    target.draw(m_layout_vertical);
    
    target.draw(*m_popup_game_settings);
}
