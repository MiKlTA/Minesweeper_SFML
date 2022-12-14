#include "MainMenu.h"



MainMenu::MainMenu(Core *core, Game *game)
    : Scene(core->getSceneManager()),
      
      m_key_manager(core->getKeyManager()),
      
      m_layout(core->getKeyManager(), *core->getWindow(),
                          Layout::Type::Vertical, Layout::Alignment::Centre),
      
      m_background(core->getResourceManager(), *core->getWindow()),
      
      m_continue_game(core->getResourceManager(), core->getSoundManager(),
                                 core->getKeyManager(), *core->getWindow(),
                                 Button::Theme::Default, L"Continue"),
      m_new_game(core->getResourceManager(), core->getSoundManager(),
                            core->getKeyManager(), *core->getWindow(),
                               Button::Theme::Default, L"New game"),
      m_settings(core->getResourceManager(), core->getSoundManager(),
                            core->getKeyManager(),
                            *core->getWindow(),
                               Button::Theme::Default, L"Settings"),
      m_exit(core->getResourceManager(), core->getSoundManager(),
                        core->getKeyManager(), *core->getWindow(),
                               Button::Theme::Default, L"Exit")
{
    Text *im_sure_text = new Text(core->getResourceManager(), *core->getWindow(),
                                  Text::Alignment::Left,
                                  L"Do you want to start a new game?");
    im_sure_text->setCharacterSize(32);
    m_popup_im_sure = new PopupYouSure(core->getResourceManager(), core->getSoundManager(),
                                       core->getKeyManager(), *core->getWindow(),
                                       im_sure_text, L"I'm sure");
    
    configureButton(&m_continue_game);
    m_continue_game.setHide(true);
    configureButton(&m_new_game);
    configureButton(&m_settings);
    configureButton(&m_exit);
    
    m_continue_game.setCallback([core](){
        core->getSceneManager()->setScene("GameScene");
    });
    m_new_game.setCallback([this, game](){
        if (game->foundSaves())
        {
            m_popup_im_sure->setHide(false);
        }
        else
        {
            m_popup_game_settings->setHide(false);
        }
    });
    m_settings.setCallback([core](){
        core->getSceneManager()->setScene("Settings");
    });
    m_exit.setCallback([core](){
        core->quit();
    });
    
    m_layout.setMargin(16.f);
    
    m_layout.addWidget(&m_continue_game);
    m_layout.addWidget(&m_new_game);
    m_layout.addWidget(&m_settings);
    m_layout.addWidget(&m_exit);
    
    core->goToCentre(&m_layout);
    
    core->goToCentre(m_popup_im_sure);
    
    m_popup_im_sure->setHide(true);
    m_popup_im_sure->setImSureCallback([this](){
        m_popup_im_sure->setHide(true);
        m_popup_game_settings->setHide(false);
    });
    
    m_popup_game_settings = new PopupGameSettings(core, game, [core](){
        core->getSceneManager()->setScene("GameScene");
    });
    m_popup_game_settings->setHide(true);
}

MainMenu::~MainMenu()
{
    delete m_popup_im_sure;
    delete m_popup_game_settings;
}



void MainMenu::onEvent(const sf::Event &event)
{
    Widget *active_widget;
    
    if (!m_popup_game_settings->isHidden())
    {
        active_widget = m_popup_game_settings;
    }
    else if (!m_popup_im_sure->isHidden())
    {
        active_widget = m_popup_im_sure;
    }
    else
    {
        active_widget = &m_layout;
    }
    
    if (event.type == sf::Event::KeyPressed)
    {
        active_widget->setState(Widget::State::Focused);
    }
    active_widget->onEvent(event);
}

void MainMenu::update(float frametime)
{
    
}

void MainMenu::onOpen()
{
    
}



void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_layout);
    target.draw(*m_popup_im_sure);
    target.draw(*m_popup_game_settings);
}



// private:



void MainMenu::configureButton(Button *button)
{
    button->scale({0.8f, 0.8f});
    button->setCharacterSize(32);
}
