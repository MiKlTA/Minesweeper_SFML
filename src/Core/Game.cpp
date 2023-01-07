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



void Game::startGame()
{
    
}



void Game::checkTile(Tile::Position)
{
    
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
    return 1;
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
    return FieldSize{2, 2};
}

Game::FieldSize Game::getMaxFieldSize()
{
    return FieldSize{100, 100};
}



const Game::Tile & Game::getTile(Tile::Position tile_position) const
{
    return m_tiles[tile_position.y][tile_position.x];
}



bool Game::isDefeated() const
{
    return m_you_lose;
}
