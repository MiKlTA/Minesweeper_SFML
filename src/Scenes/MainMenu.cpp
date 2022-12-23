#include "MainMenu.h"



MainMenu::MainMenu(Core *core, Game *game)
    : Scene(core),
      
      m_background(new Image(game->getResourceManager(), *game->getWindow())),
      
      m_continue_game(new Button(game->getResourceManager(), game->getKeyManager(),
                                 *game->getWindow(),
                                 Button::Theme::Default, L"Continue")),
      m_new_game(new Button(game->getResourceManager(), game->getKeyManager(),
                            *game->getWindow(),
                               Button::Theme::Default, L"New game")),
      m_settings(new Button(game->getResourceManager(), game->getKeyManager(),
                            *game->getWindow(),
                               Button::Theme::Default, L"Settings")),
      m_exit(new Button(game->getResourceManager(), game->getKeyManager(),
                        *game->getWindow(),
                               Button::Theme::Default, L"Exit"))
{
    m_exit->setCallback([game](){
        game->quit();
    });
    m_exit->setPosition(game->getViewSize() / 2.f - m_exit->getSize() / 2.f);
    
}



void MainMenu::onEvent(const sf::Event &event)
{
    m_exit->onEvent(event);
}

void MainMenu::update(float frametime)
{
    
}

void MainMenu::onOpen()
{
    
}



void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*m_exit);
}
