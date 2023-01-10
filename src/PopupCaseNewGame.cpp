#include "PopupCaseNewGame.h"

#include "PopupGameSettings.h"



PopupCaseNewGame::PopupCaseNewGame(Core *core, Game *game,
        PopupGameSettings *parent, Button::CallbackType apply_callback)
    : Widget(*core->getWindow()),
      
      m_layout_vertical(core->getKeyManager(), *core->getWindow(),
                        Layout::Type::Vertical, Layout::Alignment::Centre),
      m_layout_horisontal(core->getKeyManager(), *core->getWindow(),
                        Layout::Type::Horizontal, Layout::Alignment::Left),
      
      m_background(core->getResourceManager(), *core->getWindow()),
      
      m_title(core->getResourceManager(), *core->getWindow(),
              Text::Alignment::Left, L"Do you want to start a new game or finish this one?"),
      
      m_cancel(core->getResourceManager(), core->getSoundManager(),
               core->getKeyManager(), *core->getWindow(),
               Button::Theme::Default, L"Cancel"),
      m_finish_this_game(core->getResourceManager(), core->getSoundManager(),
                         core->getKeyManager(), *core->getWindow(),
                         Button::Theme::Default, L"Finish this"),
      m_immediately_start(core->getResourceManager(), core->getSoundManager(),
                          core->getKeyManager(), *core->getWindow(),
                          Button::Theme::Default, L"Start new")
{
    m_cancel.setCharacterSize(16);
    m_cancel.scale({0.5f, 0.5f});
    m_cancel.setCallback([this, parent](){
        this->setHide(true);
        parent->setHide(true);
        parent->returnSliderToActualPositions();
    });
    m_finish_this_game.setCharacterSize(16);
    m_finish_this_game.scale({0.5f, 0.5f});
    m_finish_this_game.setCallback([this, parent](){
        this->setHide(true);
        parent->setHide(true);
    });
    m_immediately_start.setCharacterSize(16);
    m_immediately_start.scale({0.5f, 0.5f});
    m_immediately_start.setCallback(apply_callback);
    
    m_layout_horisontal.setMargin(20.f);
    m_layout_horisontal.addWidget(&m_cancel);
    m_layout_horisontal.addWidget(&m_finish_this_game);
    m_layout_horisontal.addWidget(&m_immediately_start);
    
    
    
    m_title.setCharacterSize(16);
    
    m_layout_vertical.setPadding({20.f, 30.f, 20.f, 20.f});
    m_layout_vertical.setMargin(10.f);
    m_layout_vertical.addWidget(&m_title);
    m_layout_vertical.addWidget(&m_layout_horisontal);
    
    
    
    m_background.setImage("window");
    m_background.setSize(m_layout_vertical.getSize());
    
    setSize(m_background.getSize());
    core->goToCentre(this);
}



bool PopupCaseNewGame::isPassEvent(const sf::Event &event)
{
    return false;
}



// protected:



bool PopupCaseNewGame::canBeFocused_() const
{
    return true;
}



void PopupCaseNewGame::onEvent_(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed
            && !containsPoint({event.mouseButton.x, event.mouseButton.y}))
    {
        setHide(true);
    }
    
    m_background.onEvent(event);
    m_layout_vertical.onEvent(event);
}

void PopupCaseNewGame::onPositionChange(sf::Vector2f new_position)
{
    sf::Vector2f delta = new_position - getPosition();
    m_background.move(delta);
    m_layout_vertical.move(delta);
}

void PopupCaseNewGame::onStateChange(State new_state)
{
    m_layout_vertical.setState(new_state);
}



void PopupCaseNewGame::draw_(sf::RenderTarget &target, sf::RenderStates) const
{
    target.draw(m_background);
    target.draw(m_layout_vertical);
}
