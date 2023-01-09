#include "GameWidget.h"



GameWidget::GameWidget(Core *core, Game *game)
    : Widget(*core->getWindow()),
      
      m_game(game),
      m_resource_manager(core->getResourceManager()),
      m_key_manager(core->getKeyManager()),
      m_config(core->getConfig()),
      
      m_padding(0.f, 0.f),
      m_real_size(),
      m_scale(1.f),
      
      m_focus_position({0, 0}),
      m_pressed_position({0, 0})
{
   
}



void GameWidget::restartGame()
{
    
}

void GameWidget::newGame()
{
    m_game->destroyField();
    m_game->createField();
    recomputeRealSizeAndLocation();
    
    m_game->generateField(); // !!!
}



bool GameWidget::isPassEvent(const sf::Event &event)
{
    bool is_pass = true;
    
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == m_key_manager->key("left"))
        {
            is_pass = false;
        }
        else if (event.key.code == m_key_manager->key("up"))
        {
            is_pass = false;
        }
        else if (event.key.code == m_key_manager->key("right"))
        {
            is_pass = false;
        }
        else if (event.key.code == m_key_manager->key("down"))
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
    switch (event.type)
    {
    case sf::Event::MouseMoved:
    {
        bool have_focused_tile;
        Game::Tile::Position tile_position;
        tile_position = getTilePosition({event.mouseMove.x, event.mouseMove.y}, have_focused_tile);
        
        if (have_focused_tile && getState() != State::Pressed)
        {
            setState(State::Hovered);
            m_focus_position = tile_position;
        }
        
        break;
    }
    case sf::Event::MouseButtonPressed:
        
        if (event.mouseButton.button == m_key_manager->button("left")
                && getState() == State::Hovered)
        {
            setState(State::Pressed);
            m_pressed_position = m_focus_position;
        }
        
        break;
    case sf::Event::MouseButtonReleased:
        
        if (event.mouseButton.button == m_key_manager->button("left"))
        {
            bool have_focused_tile;
            getTilePosition({event.mouseButton.x, event.mouseButton.y}, have_focused_tile);
            if (have_focused_tile)
            {
                setState(State::Hovered);
            }
            else
            {
                setState(State::Default);
            }
            
            if (m_focus_position.x == m_pressed_position.x
                    && m_focus_position.y == m_pressed_position.y)
            {
                m_game->checkTile(m_focus_position);
            }
        }
        
        break;
    default: break;
    }
}



void GameWidget::draw_(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite tile_brush(*m_resource_manager->getTexture("tiles"));
    sf::Sprite content_brush(*m_resource_manager->getTexture("content"));
    
    m_game->processAllTiles([&](Game::Tile::Position tile_position){
        const Game::Tile &tile = m_game->getTile(tile_position);
        
        sf::Transform transform;
        transform.translate(m_padding);
        transform.scale(m_scale, m_scale);
        transform.translate(tile_position.x * m_config->tileSize().x,
                            tile_position.y * m_config->tileSize().y);
        
        if (tile.is_open)
        {
            tile_brush.setTextureRect(getOpenedTileTexRect());
        }
        else if (m_focus_position.x == tile_position.x
                 && m_focus_position.y == tile_position.y)
        {
            if (getState() == State::Hovered || getState() == State::Focused)
            {
                tile_brush.setTextureRect(getHoveredTileTexRect());
            }
            else if (getState() == State::Pressed)
            {
                tile_brush.setTextureRect(getOpenedTileTexRect());
            }
        }
        else
        {
            tile_brush.setTextureRect(getClosedTileTexRect());
        }
        
        target.draw(tile_brush, transform);
        
        if (tile.is_open)
        {
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
                transform.translate((m_config->tileSize().x - m_config->contentSize().x) / 2.f,
                                    (m_config->tileSize().y - m_config->contentSize().y) / 2.f);
                
                target.draw(content_brush, transform);
            }
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

sf::IntRect GameWidget::getHoveredTileTexRect() const
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



void GameWidget::recomputeRealSizeAndLocation()
{
    m_scale = 1.f;
    m_real_size = sf::Vector2f(
                m_game->getFieldSize().x * m_config->tileSize().x,
                m_game->getFieldSize().y * m_config->tileSize().y);
    
    if (m_real_size.x > getSize().x)
    {
        m_scale = getSize().x / m_real_size.x;
    }
    if (m_real_size.y > getSize().y)
    {
        m_scale = getSize().y / m_real_size.y;
    }
    m_real_size *= m_scale;
    
    m_padding.x = (getSize().x - m_real_size.x) / 2.f;
    m_padding.y = (getSize().y - m_real_size.y) / 2.f;
}

Game::Tile::Position GameWidget::getTilePosition(sf::Vector2i pixel_point, bool &tile_exist)
{
    sf::Vector2f point = Widget::mapPixelToCoords(pixel_point) - m_padding;
    tile_exist = point.x > 0.f && point.y > 0.f
            && point.x < m_real_size.x && point.y < m_real_size.y;
    
    if (tile_exist)
    {
        return {
            static_cast<unsigned int>(point.x / (m_config->tileSize().x * m_scale)),
            static_cast<unsigned int>(point.y / (m_config->tileSize().y * m_scale))
        };
    }
    else
    {
        return {LONG_MAX, LONG_MAX};
    }
}
