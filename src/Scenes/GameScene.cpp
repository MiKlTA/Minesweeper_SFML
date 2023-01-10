#include "GameScene.h"



GameScene::GameScene(Core *core, Game *game)
    : Scene(core->getSceneManager()),
      
      m_key_manager(core->getKeyManager()),
      
      m_game_state(GameState::Playing),
      m_game(game),
      m_game_widget(core, game),
      
      m_background(core->getResourceManager(), *core->getWindow()),
      
      m_main_layout(core->getKeyManager(), *core->getWindow(),
                    Layout::Type::Horizontal, Layout::Alignment::Left),
      
      m_time(core->getResourceManager(), *core->getWindow(), Text::Alignment::Right),
      m_mines(core->getResourceManager(), *core->getWindow(), Text::Alignment::Right),
      
      m_popup_mini_menu(core, game, &m_game_widget),
      m_win_or_lose(core->getResourceManager(), *core->getWindow(),
                    Text::Alignment::Centre),
      m_popup_win_or_lose(core->getResourceManager(), core->getSoundManager(),
                          core->getKeyManager(), *core->getWindow(),
                          &m_win_or_lose, L"new game")
      
{
    m_game_widget.setSize({core->getViewSize().x, core->getViewSize().y * 9/10.f});
    
    m_background.setImage("mini_menu");
    m_background.setPosition({0.f, core->getViewSize().y * 9/10.f});
    
    m_time.setSize({68.f, 20.f});
    m_time.setCharacterSize(16);
    m_time.setString(L"999");
    m_mines.setSize({68.f, 20.f});
    m_mines.setCharacterSize(16);
    m_mines.setString(L"9999");
    
    m_main_layout.setPadding({134.f, 8.f, 134.f, 8.f});
    m_main_layout.setMargin(248.f);
    m_main_layout.addWidget(&m_mines);
    m_main_layout.addWidget(&m_time);
    m_main_layout.setPosition(m_background.getPosition());
    
    m_popup_mini_menu.setHide(true);
    m_popup_win_or_lose.setHide(true);
    m_popup_win_or_lose.setImSureCallback([this](){
        m_game_state = GameState::Playing;
        m_game->restartGame();
    });
    core->goToCentre(&m_popup_mini_menu);
    core->goToCentre(&m_popup_win_or_lose);
}



void GameScene::onEvent(const sf::Event &event)
{
    m_popup_mini_menu.onEvent(event);
    m_popup_win_or_lose.onEvent(event);
    
    if (event.type == sf::Event::KeyPressed
            && event.key.code == m_key_manager->key("esc"))
    {
        m_popup_mini_menu.setHide(!m_popup_mini_menu.isHidden());
    }
    else if (m_popup_mini_menu.isHidden())
    {
        m_game_widget.onEvent(event);
        if (m_game->isDefeated() && m_game_state != GameState::Lose)
        {
            m_win_or_lose.setString(L"You lose!");
            m_popup_win_or_lose.setHide(false);
            m_game_state = GameState::Lose;
        }
        else if (m_game->isWin() && m_game_state != GameState::Win)
        {
            m_win_or_lose.setString(L"You win!");
            m_popup_win_or_lose.setHide(false);
            m_game_state = GameState::Win;
        }
    }
}

void GameScene::update(float frametime)
{
    // ...
}

void GameScene::onOpen()
{
    m_game_widget.newGame();
}



void GameScene::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_game_widget);
    
    target.draw(m_background);
    
    target.draw(m_main_layout);
    
    target.draw(m_popup_mini_menu);
    target.draw(m_popup_win_or_lose);
}
