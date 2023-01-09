#include "Game.h"

#include <cmath>



Game::Game(std::string game_path)
    : m_game_path(game_path),
      
      m_you_lose(true),
      
      m_mines_total_number(),
      m_mines_number_found(0),
      
      m_ducks_total_number(),
      m_ducks_number_found(0),
      
      m_field_size(getMinFieldSize()),
      
      m_tiles(nullptr)
{
    
}

Game::~Game()
{
    destroyField();
}



void Game::setTotalMinesNumber(unsigned int mines_number)
{
    m_mines_total_number = mines_number;
    m_mines_number_found = std::min(m_mines_number_found, m_mines_total_number);
}

void Game::setTotalDucksNumber(unsigned int ducks_number)
{
    m_ducks_total_number = ducks_number;
    m_ducks_number_found = std::min(m_ducks_number_found, m_ducks_total_number);
}

void Game::setFieldSize(FieldSize field_size)
{
    if (m_tiles == nullptr)
    {
        m_field_size = field_size;
    }
}



void Game::createField()
{
    if (m_tiles == nullptr)
    {
        m_tiles = new Tile*[m_field_size.y];
        for (unsigned int y = 0; y < m_field_size.x; ++y)
        {
            m_tiles[y] = new Tile[m_field_size.x];
        }
    }
}

void Game::generateField()
{
    int tiles_number = getFieldSize().x * getFieldSize().y;
    int *random_tiles = new int[tiles_number];
    fillRandomNumbers(random_tiles, tiles_number);
    
    int mines_number = getTotalMinesNumber();
    int ducks_number = getTotalDucksNumber();
    
    for (int i = 0; i < mines_number; ++i)
    {
        Tile::Position tile_position(fromLinearToPoint(random_tiles[i]));
        
        tile(tile_position).type = Tile::Type::Mine;
        processTileNeighbors(tile_position, [this](Tile::Position neighbor_position){
            this->tile(neighbor_position).neighbors++;
        });
    }
    
    for (int i = mines_number; i < mines_number + ducks_number; ++i)
    {
        Tile::Position tile_position(fromLinearToPoint(random_tiles[i]));
        
        tile(tile_position).type = Tile::Type::Duck;
        processTileNeighbors(tile_position, [this](Tile::Position neighbor_position){
            unsigned int &neighbors = this->tile(neighbor_position).neighbors;
            if (neighbors > 0)
            {
                neighbors--;
            }
        });
    }
}

void Game::generateField(Tile::Position definitely_empty_tile)
{
    // ...
}

void Game::destroyField()
{
    if (m_tiles != nullptr)
    {
        for (unsigned int y = 0; y < m_field_size.x; ++y)
        {
            delete[] m_tiles[y];
        }
        delete[] m_tiles;
        m_tiles = nullptr;
    }
}



void Game::saveGame()
{
    // ...
}

void Game::loadGame()
{
    // ...
}



void Game::startGame()
{
    // ...
}



void Game::checkTile(Tile::Position tile_position)
{
    // ... 
}



unsigned int Game::getTotalMinesNumber() const
{
    return m_mines_total_number;
}

unsigned int Game::getTotalDucksNumber() const
{
    return m_ducks_total_number;
}

unsigned int Game::getMinesNumberFound() const
{
    return m_mines_number_found;
}

unsigned int Game::getDucksNumberFound() const
{
    return m_ducks_number_found;
}

Game::FieldSize Game::getFieldSize() const
{
    return m_field_size;
}



unsigned int Game::getMinTotalMinesNumber() const
{
    return 50;
}

unsigned int Game::getMinTotalDucksNumber() const
{
    return 0;
}

unsigned int Game::getMaxTotalMinesNumber() const
{
    const int field_area = m_field_size.x * m_field_size.y;
    return std::max<int>(field_area - std::round(field_area / 9.f) - getTotalDucksNumber(), 0);
}

unsigned int Game::getMaxTotalDucksNumber() const
{
    const int field_area = m_field_size.x * m_field_size.y;
    return std::max<int>(field_area - std::round(field_area / 9.f) - getTotalMinesNumber(), 0);
}

Game::FieldSize Game::getMinFieldSize()
{
    return FieldSize{30, 30};
}

Game::FieldSize Game::getMaxFieldSize()
{
    return FieldSize{100, 100};
}



const Game::Tile & Game::getTile(Tile::Position tile_position) const
{
    return m_tiles[tile_position.y][tile_position.x];
}

void Game::processAllTiles(std::function<void(Tile::Position)> handler) const
{
    for (unsigned int y = 0; y < getFieldSize().y; ++y)
    {
        for (unsigned int x = 0; x < getFieldSize().x; ++x)
        {
            handler(Tile::Position({x, y}));
        }
    }
}



bool Game::isDefeated() const
{
    return m_you_lose;
}



// private:



void Game::fillRandomNumbers(int *container, unsigned int container_size)
{
    for (unsigned int i = 0; i < container_size; ++i)
    {
        container[i] = i;
    }
    
    for (unsigned int i = 0; i < container_size; ++i)
    {
        int random_index = rand() % (container_size - i) + i;
        std::swap(container[i], container[random_index]);
    }
}

Game::Tile::Position Game::fromLinearToPoint(unsigned int linear_position)
{
    return {
        linear_position % getFieldSize().x,
        linear_position / getFieldSize().x
    };
}


void Game::processTileNeighbors(Tile::Position tile_position,
                                std::function<void(Tile::Position)> handler)
{
    bool on_left_border = tile_position.x == 0;
    bool on_right_border = tile_position.x == getFieldSize().x - 1;
    bool on_top_border = tile_position.y == 0;
    bool on_bottom_border = tile_position.y == getFieldSize().y - 1;
    
    // 1 8 7
    // 2 - 6
    // 3 4 5
    
    if (!on_left_border)
    {
        if (!on_top_border)
        {
            handler({tile_position.x - 1, tile_position.y - 1}); // 1
        }
        handler({tile_position.x - 1, tile_position.y}); // 2
        if (!on_bottom_border)
        {
            handler({tile_position.x - 1, tile_position.y + 1}); // 3
        }
    }
    
    if (!on_bottom_border)
    {
        handler({tile_position.x, tile_position.y + 1}); // 4
    }
    
    if (!on_right_border)
    {
        if (!on_bottom_border)
        {
            handler({tile_position.x + 1, tile_position.y + 1}); // 5
        }
        handler({tile_position.x + 1, tile_position.y}); // 6
        if (!on_top_border)
        {
            handler({tile_position.x + 1, tile_position.y - 1}); // 7
        }
    }
    
    if (!on_top_border)
    {
        handler({tile_position.x, tile_position.y - 1}); // 8
    }
}

Game::Tile & Game::tile(Tile::Position tile_position)
{
    return m_tiles[tile_position.y][tile_position.x];
}
