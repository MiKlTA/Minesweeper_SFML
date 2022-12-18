#include <iostream>
#include <experimental/filesystem>



#define SFML_STATIC

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"



#include "src/ResourceManager.h"

#include "src/GUI/GUIKeyManager.h"
#include "src/GUI/Button.h"
#include "src/GUI/Image.h"
#include "src/GUI/AnimatedImage.h"
#include "src/GUI/Layout.h"
#include "src/GUI/Text.h"
#include "src/GUI/InputField.h"
#include "src/GUI/ScrollBar.h"



int main(int, char *argv[])
{
    std::string path = std::experimental::filesystem::path(argv[0]).parent_path().string();
    path += '\\';
    ResourceManager::init(path);
    
    GUIKeyManager::attachKey("left", sf::Keyboard::Left);
    GUIKeyManager::attachKey("right", sf::Keyboard::Right);
    GUIKeyManager::attachKey("up", sf::Keyboard::Up);
    GUIKeyManager::attachKey("down", sf::Keyboard::Down);
    GUIKeyManager::attachKey("enter", sf::Keyboard::Enter);
    GUIKeyManager::attachKey("backspace", sf::Keyboard::Backspace);
    GUIKeyManager::attachButton("left", sf::Mouse::Left);
    
    
    
    sf::RenderWindow window(sf::VideoMode(1280, 721), "My window", sf::Style::Default);
    window.setPosition({0, 0});
    window.setSize({1280, 720});
    window.setView(sf::View({640, 360}, {1280, 720}));
    
    
    
    Button b1(window, Button::Theme::Blue, L"Превед", [](){std::cout << "Hello world!" << std::endl;});
    Button b2(window, Button::Theme::Red, L"Медвед", [](){std::cout << "Goodbye world!" << std::endl;});
    Button b3(window, Button::Theme::Blue, L"Кнопка", [](){std::cout << "adsada" << std::endl;});
    Button b4(window, Button::Theme::Red, L"Акпонк", [](){std::cout << "yiyuiyuiu" << std::endl;});
    b2.scale({1.5f, 1.f});
    
    Image i1(window);
//    i1.setImage("duckcarrier");
    i1.setPosition({86.f, 86.f});
    i1.scale({0.3f, 0.3f});
    
    Text t(window);
    t.setString(L"ывауℤ∜∀∫☔♥☆и");
    
    InputField input(window, InputField::Theme::Blue);
    
    ScrollBar sb(window, ScrollBar::Theme::White, ScrollBar::Type::Horisontal, 31);
    
    AnimatedImage ai(window, "player", {48, 48}, 6, 4, 0.2f);
    ai.setRepeatAnimation(false);
    
    
    
    
    Layout::need_draw_border = true;
    
    Layout l(window, Layout::Horizontal);
    l.setPosition({50.f, 50.f});
    
    Layout l1(window, Layout::Horizontal);
    Layout l2(window, Layout::Vertical);
    
    l1.addWidget(&b1);
    l1.addWidget(&b2);
    l1.addWidget(&t);
    l2.addWidget(&b3);
    l2.addWidget(&b4);
    l2.addWidget(&i1);
    l2.addWidget(&input);
    l2.addWidget(&ai);
    
    l.addWidget(&l1);
    l.addWidget(&l2);
    l.addWidget(&sb);
    
    sf::Clock clock;
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
                switch (event.key.code)
                {
                case sf::Keyboard::Tab:
                    l.setState(Layout::State::Focused);
                    break;
                case sf::Keyboard::P:
                    ai.startAnimation();
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
        
        t.setString(std::to_wstring(sb.getSliderValue()));
        window.clear();
        window.draw(l);
        window.display();
    }
    
    
    return 0;
}
