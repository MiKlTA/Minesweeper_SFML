#include "GameWidget.h"



GameWidget::GameWidget(Core *core, Game *game)
    : Widget(*core->getWindow()),
      
      m_game(game),
      m_resource_manager(core->getResourceManager()),
      m_key_manager(core->getKeyManager()),
      m_config(core->getConfig()),
      
      m_padding(0.f, 0.f),
      
      m_focus_position(0, 0)
{
   
}



void GameWidget::refresh()
{
    m_game->createField();
    m_game->generateField();
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



void GameWidget::draw_(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite tile_brush(*m_resource_manager->getTexture("tiles"));
    sf::Sprite content_brush(*m_resource_manager->getTexture("content"));
    
    m_game->processAllTiles([&](Game::Tile::Position tile_position){
        const Game::Tile &tile = m_game->getTile(tile_position);
        bool need_draw = false;
        
        
        if (tile.type == Game::Tile::Empty && tile.neighbors > 0)
        {
            content_brush.setTextureRect(getNumberTexRect(tile.neighbors));
            need_draw = true;
        }
        else if (tile.type == Game::Tile::Mine)
        {
            content_brush.setTextureRect(getMineTexRect());
            need_draw = true;
        }
        else if (tile.type == Game::Tile::Duck)
        {
            content_brush.setTextureRect(getDuckTexRect());
            need_draw = true;
        }
        
        
        
        if (need_draw)
        {
            sf::Transform transform;
            transform.translate(m_padding);
            transform.translate(tile_position.x * 16.f, tile_position.y * 16.f);
            
            target.draw(content_brush, transform);
        }
    });
}



// private:



sf::IntRect GameWidget::getNumberTexRect(int number) const
{
    return {
        (2 + number) * m_config->contentSize().x, 0,
        m_config->contentSize().x, m_config->contentSize().y
    };
}

sf::IntRect GameWidget::getMineTexRect() const
{
    return {
        0, 0,
        m_config->contentSize().x, m_config->contentSize().y
    };
}

sf::IntRect GameWidget::getDuckTexRect() const
{
    return {
        m_config->contentSize().x, 0,
        m_config->contentSize().x, m_config->contentSize().y
    };
}

sf::IntRect GameWidget::getFlagTexRect() const
{
    return {
        2 * m_config->contentSize().x, 0,
        m_config->contentSize().x, m_config->contentSize().y
    };
}



sf::IntRect GameWidget::getClosedTileTexRect() const
{
    return {
        0, 0,
        m_config->tileSize().x, m_config->tileSize().y
    };
}

sf::IntRect GameWidget::getHoveredTIleTexRect() const
{
    return {
        m_config->tileSize().x, 0,
        m_config->tileSize().x, m_config->tileSize().y
    };
}

sf::IntRect GameWidget::getOpenedTileTexRect() const
{
    return {
        2 * m_config->tileSize().x, 0,
        m_config->tileSize().x, m_config->tileSize().y
    };
}
