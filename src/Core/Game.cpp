#include "Game.h"



Game::Game(std::string game_path)
{
    
}



void Game::setTotalMinesNumber(unsigned int mines_number)
{
    
}

void Game::setTotalDucksNumber(unsigned int ducks_number)
{
    
}

void Game::setFieldSize(FieldSize field_size)
{
    
}



void Game::createField()
{
    
}

void Game::generateField()
{
    
}

void Game::destroyField()
{
    
}



void Game::startGame()
{
    
}



void Game::checkTile(Tile::Position)
{
    
}



unsigned int Game::getTotalMinesNumber() const
{
    
}

unsigned int Game::getTotalDucksNumber() const
{
    
}

unsigned int Game::getMinesNumberFound() const
{
    
}

unsigned int Game::getDucksNumberFound() const
{
    
}

Game::FieldSize Game::getFieldSize() const
{
    
}



unsigned int Game::getMinTotalMinesNumber() const
{
    
}

unsigned int Game::getMinTotalDucksNumber() const
{
    return 0;
}

unsigned int Game::getMaxTotalMinesNumber() const
{
    
}

unsigned int Game::getMaxTotalDucksNumber() const
{
    
}

Game::FieldSize Game::getMinFieldSize()
{
    return FieldSize{1, 1};
}

Game::FieldSize Game::getMaxFieldSize()
{
    return FieldSize{100, 100};
}



const Game::Tile & Game::getTile(Tile::Position) const
{
    
}



bool Game::isDefeated() const
{
    
}
