#ifndef H_GAME
#define H_GAME



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
        
        Type            type;
        unsigned int    neighbors;
    };
    
    
    
    Game();
    
    
    
    void setTotalMinesNumber(unsigned int mines_number);
    void setTotalDucksNumber(unsigned int ducks_number);
    void setFieldSize(FieldSize field_size);
    
    void createField();
    void generateField();
    void destroyField();
    
    void startGame(); // or restart
    
    void checkTile(Tile::Position);
    
    
    
    unsigned int getTotalMinesNumber() const;
    unsigned int getTotalDucksNumber() const;
    unsigned int getMinesNumberFound() const;
    unsigned int getDucksNumberFound() const;
    FieldSize getFieldSize() const;
    
    const Tile & getTile(Tile::Position) const;
    
    bool isDefeated() const;
    
    
    
private:
    
    bool            m_you_lose;
    
    FieldSize       m_field_size;
    
    unsigned int    m_mines_total_number;
    unsigned int    m_mines_number_found;
    
    unsigned int    m_ducks_total_number;
    unsigned int    m_ducks_number_found;
    
    Tile **m_tiles;
    
};



#endif // H_GAME
