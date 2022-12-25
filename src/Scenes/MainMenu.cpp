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
      
      m_popup_im_sure(new PopupYouSure(game->getResourceManager(), game->getKeyManager(),
                                       *game->getWindow(), L"Are you sure?")),
      m_popup_game_settings(new PopupGameSettings(game))
{
    configureButton(m_continue_game);
    m_continue_game->setHide(true);
    configureButton(m_new_game);
    configureButton(m_settings);
    configureButton(m_exit);
    
    m_continue_game->setCallback([game](){
        game->quit();
    });
    m_new_game->setCallback([this](){
        m_popup_im_sure->setHide(false);
    });
    m_settings->setCallback([game](){
        game->quit();
    });
    m_exit->setCallback([game](){
        game->quit();
    });
    
    m_layout->setMargin(16.f);
    
    m_layout->addWidget(m_continue_game);
    m_layout->addWidget(m_new_game);
    m_layout->addWidget(m_settings);
    m_layout->addWidget(m_exit);
    
    game->goToCentre(m_layout);
    
    game->goToCentre(m_popup_im_sure);
    
    m_popup_game_settings->setHide(true);
    m_popup_im_sure->setHide(false);
}



void MainMenu::onEvent(const sf::Event &event)
{
    if (!m_popup_game_settings->isHidden())
    {
        m_popup_game_settings->onEvent(event);
    }
    else if (!m_popup_im_sure->isHidden())
    {
        m_popup_im_sure->onEvent(event);
    }
    else
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
    target.draw(*m_popup_im_sure);
    target.draw(*m_popup_game_settings);
}



// private:



void MainMenu::configureButton(Button *button)
{
    button->scale({0.8f, 0.8f});
    button->setCharacterSize(32);
}
