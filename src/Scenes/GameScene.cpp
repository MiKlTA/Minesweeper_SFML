#include "GameScene.h"



GameScene::GameScene(Core *core, SceneManager *scene_manager, Game *game)
    : Scene(scene_manager),
      
      m_game_widget(core, game),
      
      m_background(core->getResourceManager(), *core->getWindow()),
      
      m_main_layout(core->getKeyManager(), *core->getWindow(),
                    Layout::Type::Horizontal, Layout::Alignment::Left),
      
      m_time(core->getResourceManager(), *core->getWindow(), Text::Alignment::Right),
      m_mines(core->getResourceManager(), *core->getWindow(), Text::Alignment::Right)
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
}



void GameScene::onEvent(const sf::Event &event)
{
    m_game_widget.onEvent(event);
}

void GameScene::update(float frametime)
{
    
}

void GameScene::onOpen()
{
    m_game_widget.refresh();
}



void GameScene::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_game_widget);
    
    target.draw(m_background);
    
    target.draw(m_main_layout);
}
