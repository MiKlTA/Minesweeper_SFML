#ifndef H_GAME
#define H_GAME



#include <fstream>
#include <functional>



class Game
{
public:
    
    struct Vector2u
    {
        unsigned int x;
        unsigned int y;
    };
    
    using FieldSize = Vector2u;
    
    struct Tile
    {
        using Position = Vector2u;
        
        enum Type
        {
            Empty,
            Mine,
            Duck
        };
        
        Tile()
            : type(Type::Empty),
              neighbors(0),
              is_open(false),
              have_flag(true)
        {};
        
        Type            type;
        unsigned int    neighbors;
        bool            is_open;
        bool            have_flag;
    };
    
    
    
    Game(std::string game_path);
    ~Game();
    
    
    
    void setTotalMinesNumber(unsigned int mines_number);
    void setTotalDucksNumber(unsigned int ducks_number);
    void setFieldSize(FieldSize field_size);
    
    void createField();
    void generateField();
    void generateField(Tile::Position definitely_empty_tile);
    void destroyField();
    
    void saveGame();
    void loadGame();
    
    void restartGame();
    
    void checkTile(Tile::Position tile_position);
    void checkFlag(Tile::Position flag_position);
    
    
    
    unsigned int getTotalMinesNumber() const;
    unsigned int getTotalDucksNumber() const;
    unsigned int getMinesNumberFound() const;
    unsigned int getDucksNumberFound() const;
    FieldSize getFieldSize() const;
    
    unsigned int getMinTotalMinesNumber() const;
    unsigned int getMinTotalDucksNumber() const;
    unsigned int getMaxTotalMinesNumber() const;
    unsigned int getMaxTotalDucksNumber() const;
    static FieldSize getMinFieldSize();
    static FieldSize getMaxFieldSize();
    
    const Tile & getTile(Tile::Position tile_position) const;
    void processAllTiles(std::function<void(Tile::Position)> handler) const;
    
    bool isDefeated() const;
    
    
    
private:
    
    // fills the container with random numbers from 0 to N - 1
    static void fillRandomNumbers(int *container, unsigned int container_size);
    
    Tile::Position fromLinearToPoint(unsigned int linear_position);
    
    void processTileNeighbors(Tile::Position tile_position,
                              std::function<void(Tile::Position)> handler) const;
    
    // 3x3 area
    bool isPointInArea(Tile::Position area_centre, Tile::Position point) const;
    
    
    
    Tile & tile(Tile::Position tile_position);
    
    void emplaceMine(Tile::Position mine_position);
    void emplaceDuck(Tile::Position duck_position);
    
    
    
    void loseGame();
    
    
    
    std::string     m_game_path;
    
    bool            m_you_lose;
    
    unsigned int    m_mines_total_number;
    unsigned int    m_mines_number_found;
    
    unsigned int    m_ducks_total_number;
    unsigned int    m_ducks_number_found;
    
    FieldSize       m_field_size;
    Tile **m_tiles;
    
};



#endif // H_GAME
