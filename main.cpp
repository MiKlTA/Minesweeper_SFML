#include <iostream>
#include <experimental/filesystem>



#define SFML_STATIC

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"



#include "src/Core/Game.h"



template <typename VecType>
void printVector(const VecType &vector)
{
    std::cout << vector.x << ' ' << vector.y << std::endl;
}



int main(int, char *argv[])
{
    Config *config = new Config;
    
    Core *core = new Core;
    
    std::string path = std::experimental::filesystem::path(argv[0]).parent_path().string();
    path += '\\';
    ResourceManager *resource_manager = new ResourceManager(path);
    
    Game game(config, core, resource_manager);
    game.run();
    
    return 0;
}
