#include "Game.h"

#include <cmath>
#include <stack>



Game::Game(std::string game_path)
    : m_game_path(game_path),
      
      m_you_lose(false),
      m_field_is_generated(false),
      
      m_mines_total_number(),
      m_mines_number_found(0),
      
      m_ducks_total_number(),
      m_ducks_number_found(0),
      
      m_new_field_size(getMinFieldSize()),
      m_real_field_size(getMinFieldSize()),
      
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
    m_new_field_size = field_size;
    if (m_tiles == nullptr)
    {
        m_real_field_size = m_new_field_size;
    }
}



bool Game::haveCreatedField()
{
    return m_tiles != nullptr;
}

void Game::createField()
{
    if (!haveCreatedField())
    {
        m_tiles = new Tile*[m_real_field_size.y];
        for (unsigned int y = 0; y < m_real_field_size.y; ++y)
        {
            m_tiles[y] = new Tile[m_real_field_size.x];
        }
    }
    
    m_field_is_generated = false;
}

void Game::destroyField()
{
    if (haveCreatedField())
    {
        for (unsigned int y = 0; y < m_real_field_size.y; ++y)
        {
            delete[] m_tiles[y];
        }
        delete[] m_tiles;
        m_tiles = nullptr;
    }
    
    m_real_field_size = m_new_field_size;
}

void Game::recreateField()
{
    destroyField();
    createField();
}



void Game::saveGame()
{
    // ...
}

bool Game::foundSaves()
{
    // ...
    
    return false;
}

void Game::loadGame()
{
    // ...
}



void Game::restartGame()
{
    m_you_lose = false;
    m_field_is_generated = false;
    
    if (m_new_field_size.x != m_real_field_size.x
            || m_new_field_size.y != m_real_field_size.y
            || m_tiles == nullptr)
    {
        recreateField();
    }
    
    processAllTiles([this](Tile::Position tile_position){
        tile(tile_position).type = Tile::Type::Empty;
        tile(tile_position).neighbors = 0;
        tile(tile_position).is_open = false;
        tile(tile_position).have_flag = false;
    });
}



void Game::checkTile(Tile::Position tile_position)
{
    if (!m_field_is_generated)
    {
        generateField(tile_position);
    }
    if (!getTile(tile_position).have_flag)
    {
        std::stack<Tile::Position> requiring_to_open;
        requiring_to_open.push(tile_position);
        
        while (!requiring_to_open.empty() && !m_you_lose)
        {
            Tile::Position opening_tile_position = requiring_to_open.top();
            requiring_to_open.pop();
            Tile &opening_tile = tile(opening_tile_position);
            opening_tile.is_open = true;
            opening_tile.have_flag = false;
            if (opening_tile.type == Tile::Type::Mine
                    || opening_tile.type == Tile::Type::Duck)
            {
                loseGame();
            }
            
            if (opening_tile.neighbors == 0)
            {
                processTileNeighbors(opening_tile_position,
                                     [this, &requiring_to_open](Tile::Position tile_position){
                    if (!tile(tile_position).is_open)
                    {
                        requiring_to_open.push(tile_position);
                    }
                });
            }
            else
            {
                processTileNeighbors(opening_tile_position,
                                     [this, &requiring_to_open](Tile::Position tile_position){
                    if (!tile(tile_position).is_open
                            && tile(tile_position).type == Tile::Type::Empty
                            && tile(tile_position).neighbors == 0)
                    {
                        requiring_to_open.push(tile_position);
                    }
                });
            }
        }
    }
}

void Game::checkFlag(Tile::Position flag_position)
{
    if (!getTile(flag_position).is_open)
    {
        tile(flag_position).have_flag = !tile(flag_position).have_flag;
    }
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
    return m_real_field_size;
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
    const int field_area = m_real_field_size.x * m_real_field_size.y;
    return std::max<int>(field_area - std::round(field_area / 9.f) - getTotalDucksNumber(), 0);
}

unsigned int Game::getMaxTotalDucksNumber() const
{
    const int field_area = m_real_field_size.x * m_real_field_size.y;
    return std::max<int>(field_area - std::round(field_area / 9.f) - getTotalMinesNumber(), 0);
}

Game::FieldSize Game::getMinFieldSize()
{
    return FieldSize{4, 2};
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

bool Game::isWin() const
{
    // ...
    
    return false;
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
                                std::function<void(Tile::Position)> handler) const
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

bool Game::isPointInArea(Tile::Position area_centre, Tile::Position point) const
{
    if (area_centre.x == point.x && area_centre.y == point.y)
    {
        return true;
    }
    
    bool is_point_in_area = false;
    processTileNeighbors(area_centre,
                         [&is_point_in_area, point](Tile::Position tile_position){
        is_point_in_area |= tile_position.x == point.x && tile_position.y == point.y;
    });
    
    return is_point_in_area;
}



Game::Tile & Game::tile(Tile::Position tile_position)
{
    return m_tiles[tile_position.y][tile_position.x];
}

void Game::emplaceMine(Tile::Position mine_position)
{
    tile(mine_position).type = Tile::Type::Mine;
    processTileNeighbors(mine_position, [this](Tile::Position neighbor_position){
        this->tile(neighbor_position).neighbors++;
    });
}

void Game::emplaceDuck(Tile::Position duck_position)
{
    tile(duck_position).type = Tile::Type::Duck;
    processTileNeighbors(duck_position, [this](Tile::Position neighbor_position){
        unsigned int &neighbors = this->tile(neighbor_position).neighbors;
        if (neighbors > 1)
        {
            neighbors--;
        }
        else if (neighbors == 0)
        {
            neighbors = 1;
        }
    });
}



void Game::generateField()
{
    int mines_number = getTotalMinesNumber();
    int ducks_number = getTotalDucksNumber();
    int tiles_number = getFieldSize().x * getFieldSize().y;
    
    int *random_tiles = new int[tiles_number];
    fillRandomNumbers(random_tiles, tiles_number);
    
    
    for (int i = 0; i < mines_number; ++i)
    {
        emplaceMine(fromLinearToPoint(random_tiles[i]));
    }
    
    for (int i = mines_number; i < mines_number + ducks_number; ++i)
    {
        emplaceDuck(fromLinearToPoint(random_tiles[i]));
    }
    
    
    
    m_field_is_generated = true;
}

void Game::generateField(Tile::Position definitely_empty_tile)
{
    int mines_number = getTotalMinesNumber();
    int ducks_number = getTotalDucksNumber();
    int tiles_number = getFieldSize().x * getFieldSize().y;
    int available_tiles_number = tiles_number - mines_number - ducks_number;
    
    if (available_tiles_number > 16)
    {
        int *random_tiles = new int[tiles_number];
        fillRandomNumbers(random_tiles, tiles_number);
        
        
        int random_tile_index = 0;
        for (int i = 0; i < mines_number; ++i)
        {
            Tile::Position random_tile_position;
            do
            {
                ++random_tile_index;
                random_tile_position = fromLinearToPoint(random_tiles[random_tile_index]);
            }
            while (isPointInArea(definitely_empty_tile, random_tile_position));
            emplaceMine(random_tile_position);
        }
        
        for (int i = mines_number; i < mines_number + ducks_number; ++i)
        {
            Tile::Position random_tile_position;
            do
            {
                ++random_tile_index;
                random_tile_position = fromLinearToPoint(random_tiles[random_tile_index]);
            }
            while (isPointInArea(definitely_empty_tile, random_tile_position));
            emplaceDuck(fromLinearToPoint(random_tiles[random_tile_index]));
        }
    }
    else
    {
        generateField();
    }
    
    
    
    m_field_is_generated = true;
}



void Game::loseGame()
{
    m_you_lose = true;
    
    processAllTiles([this](Tile::Position tile_position){
        tile(tile_position).is_open = true;
    });
}
