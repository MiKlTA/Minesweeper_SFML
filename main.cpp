#include <iostream>
#include <experimental/filesystem>



#define SFML_STATIC

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"



#include "src/Core/Core.h"
#include "src/GUI/Layout.h"



template <typename VecType>
void printVector(const VecType &vector)
{
    std::cout << vector.x << ' ' << vector.y << std::endl;
}



int main(int, char *argv[])
{
    std::srand(124);
    
    Config *config = new Config;
    
    SceneManager *scene_manager = new SceneManager;
    
    std::string path = std::experimental::filesystem::path(argv[0]).parent_path().string();
    ResourceManager *resource_manager = new ResourceManager(path + "\\");
    SoundManager *sound_manager = new SoundManager(path + "\\");
    KeyManager *key_manager = new KeyManager;
    
    Game *game = new Game(path);
    
    // Layout::need_draw_border = true;
    Core core(config, scene_manager, resource_manager, sound_manager, key_manager, game);
    core.run();
    
    return 0;
}
