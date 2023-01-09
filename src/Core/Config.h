#ifndef H_CONFIG
#define H_CONFIG



#include <string>

#include "SFML/System/Vector2.hpp"



class Config
{
public:
    
    virtual sf::Vector2u windowSize() {return {640, 360};}
    virtual sf::Vector2f viewSize() {return {640.f, 360.f};}
    virtual sf::Vector2i tileSize() {return {24, 24};}
    virtual sf::Vector2i contentSize() {return {16, 16};}
    virtual std::string windowName() {return "Minesweeper";}
    
    
    
    
};



#endif // H_CONFIG
