#include <iostream>
#include <experimental/filesystem>



#define SFML_STATIC

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"



#include "src/ResourceManager.h"
#include "src/GUI/Button.h"
#include "src/GUI/Image.h"
#include "src/GUI/Layout.h"



int main(int, char *argv[])
{
    std::string path = std::experimental::filesystem::path(argv[0]).parent_path().string();
    path += '\\';
    ResourceManager::init(path);
    
    Button b1(Button::Theme::Red, "abc", [](){std::cout << "Hello world!" << std::endl;});
    Button b2(Button::Theme::Red, "awert", [](){std::cout << "Goodbye world!" << std::endl;});
    
    Image i1("duckcarrier");
    i1.setPosition({100.f, 100.f});
    i1.scale({0.5f, 0.5f});
    
    Layout::need_draw_border = true;
    Layout l(Layout::Horizontal);
    l.setPosition({50.f, 50.f});
    l.setSize({300.f, 200.f});
    
    l.addWidget(&b1);
    l.addWidget(&b2);
    // l.recomputeSize();
    
    
    sf::RenderWindow window(sf::VideoMode(1280, 721), "My window", sf::Style::Close);
    window.setPosition({0, 0});
    window.setSize({1280, 720});
    window.setView(sf::View({640, 360}, {1280, 720}));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            l.onEvent(event);
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::P)
                {
                    l.setPosition({100.f, 100.f});
                }
            default:
                break;
            }
        }
        
        window.clear();
        window.draw(i1);
        // window.draw(b1);
        window.draw(l);
        window.display();
    }
    
    return 0;
}
