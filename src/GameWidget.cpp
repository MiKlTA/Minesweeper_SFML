#include "GameWidget.h"



GameWidget::GameWidget(Core *core, Game *game)
    : Widget(*core->getWindow()),
      
      m_game(game),
      m_key_manager(core->getKeyManager()),
      
      m_padding(0.f, 0.f),
      
      m_focus_position(0, 0)
{
   
}



void GameWidget::refresh()
{
    // ...
}



bool GameWidget::isPassEvent(const sf::Event &event)
{
    bool is_pass = true;
    
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == m_key_manager->key("left")
                && m_focus_position.x != 0)
        {
            is_pass = false;
        }
        else if (event.key.code == m_key_manager->key("up")
                 && m_focus_position.y != 0)
        {
            is_pass = false;
        }
        else if (event.key.code == m_key_manager->key("right")
                 && m_focus_position.x != m_game->getFieldSize().x - 1)
        {
            is_pass = false;
        }
        else if (event.key.code == m_key_manager->key("down")
                 && m_focus_position.y != m_game->getFieldSize().y - 1)
        {
            is_pass = false;
        }
    }
    
    return is_pass;
}



// protected:



bool GameWidget::canBeFocused_() const
{
    return true;
}



void GameWidget::onEvent_(const sf::Event &event)
{
    // ...
}



void GameWidget::draw_(sf::RenderTarget &target, sf::RenderStates) const
{
    // ...
}



// private:


