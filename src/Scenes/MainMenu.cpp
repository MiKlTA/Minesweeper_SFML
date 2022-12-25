#include "MainMenu.h"



MainMenu::MainMenu(Core *core, Game *game)
    : Scene(core),
      
      m_layout(new Layout(game->getKeyManager(), *game->getWindow(),
                          Layout::Type::Vertical)),
      
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
                               Button::Theme::Default, L"Exit")),
      
      
      m_go_back(new Button(game->getResourceManager(), game->getKeyManager(),
                        *game->getWindow(),
                               Button::Theme::Default, L"Back")),
      m_start_game(new Button(game->getResourceManager(), game->getKeyManager(),
                        *game->getWindow(),
                               Button::Theme::Default, L"Start!")),
      
      m_game_settings(new PopupGameSettings(game))
{
    configureButton(m_continue_game);
    configureButton(m_new_game);
    configureButton(m_settings);
    configureButton(m_exit);
    configureButton(m_go_back);
    configureButton(m_start_game);
    
    m_exit->setCallback([game](){
        game->quit();
    });
    
    m_layout->setMargin(16.f);
    
    m_layout->addWidget(m_continue_game);
    m_layout->addWidget(m_new_game);
    m_layout->addWidget(m_settings);
    m_layout->addWidget(m_exit);
    
    game->goToCentre(m_layout);
    
    m_game_settings->setHide(false);
}



void MainMenu::onEvent(const sf::Event &event)
{
    m_game_settings->onEvent(event);
    if (m_game_settings->isHidden())
    {
        m_layout->onEvent(event);
        
    }
}

void MainMenu::update(float frametime)
{
    
}

void MainMenu::onOpen()
{
    
}



void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*m_layout);
    target.draw(*m_game_settings);
}



// private:



void MainMenu::configureButton(Button *button)
{
    button->scale({0.8f, 0.8f});
    button->setCharacterSize(32);
}
