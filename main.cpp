#include <iostream>
#include <experimental/filesystem>



#define SFML_STATIC

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"



#include "src/ResourceManager.h"
#include "src/GUI/Button.h"
#include "src/GUI/Image.h"
#include "src/GUI/Layout.h"
#include "src/GUI/Text.h"



int main(int, char *argv[])
{
    std::string path = std::experimental::filesystem::path(argv[0]).parent_path().string();
    path += '\\';
    ResourceManager::init(path);
    
    Button b1(Button::Theme::Red, L"Превед", [](){std::cout << "Hello world!" << std::endl;});
    Button b2(Button::Theme::Red, L"Медвед", [](){std::cout << "Goodbye world!" << std::endl;});
    b2.scale({1.5f, 1.f});
    
    Image i1("duckcarrier");
    i1.setPosition({86.f, 86.f});
    i1.scale({0.3f, 0.3f});
    
    Layout::need_draw_border = true;
    Layout l(Layout::Horizontal);
    l.setPosition({50.f, 50.f});
    
    l.addWidget(&b1);
    l.addWidget(&b2);
    l.addWidget(&i1);
    
    
    
    Text t;
    t.setString(L"ывауℤ∜∀∫☔♥☆и");
    l.addWidget(&t);
    
    
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
                    
                }
            default:
                break;
            }
        }
        
        window.clear();
        window.draw(l);
        window.draw(t);
        // window.draw(i1);
        window.display();
    }
    
    
    return 0;
}
