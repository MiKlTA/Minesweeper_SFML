#include <iostream>
#include <experimental/filesystem>



#define SFML_STATIC

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"



#include "src/ResourceManager.h"

#include "src/GUI/GUIKeyManager.h"
#include "src/GUI/Button.h"
#include "src/GUI/Image.h"
#include "src/GUI/AnimatedImage.h"
#include "src/GUI/Layout.h"
#include "src/GUI/Text.h"
#include "src/GUI/InputField.h"
#include "src/GUI/ScrollBar.h"
#include "src/GUI/CheckBox.h"
#include "src/GUI/ProgressBar.h"



template <typename VecType>
void printVector(const VecType &vector)
{
    std::cout << vector.x << ' ' << vector.y << std::endl;
}



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
    
    
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My window", sf::Style::Default);
    window.setPosition({0, 0});
    window.setView(sf::View({320, 180}, {640, 360}));
    
    
    
    Button b1(window, Button::Theme::Blue, L"Превед", [](){std::cout << "Hello world!" << std::endl;});
    Button b2(window, Button::Theme::Red, L"Медвед", [](){std::cout << "Goodbye world!" << std::endl;});
    Button b3(window, Button::Theme::Blue, L"Кнопка", [](){std::cout << "adsada" << std::endl;});
    Button b4(window, Button::Theme::Red, L"Акпонк", [](){std::cout << "yiyuiyuiu" << std::endl;});
    b1.scale({0.5f, 0.5f});
    b1.setCharacterSize(16);
    b2.scale({1.0f, 1.0f});
    b3.scale({1.0f, 1.0f});
    b4.scale({0.5f, 0.5f});
    b4.setCharacterSize(16);
    
    Image i1(window);
    i1.setImage("duckcarrier");
    i1.setPosition({86.f, 86.f});
    i1.scale({0.3f, 0.3f});
    
    AnimatedImage ai(window, "player", {48, 48}, 6, 4, 0.2f);
    ai.setRepeatAnimation(false);
    
    Text t(window);
    t.setString(L"ыℤ∜∀∫");
    
    InputField input(window, InputField::Theme::Blue);
    
    ProgressBar pb(window, ProgressBar::Type::Horisontal, 10, 2.f);
    pb.setProgressValue(0.69f);
    
    ScrollBar sb(window, ScrollBar::Theme::White, ScrollBar::Type::Vertical, 31);
    sb.setOnValueChangeCallback([&pb](unsigned int value){
        pb.setProgressValue(value / float(31));
    });
    
    CheckBox cb(window);
    
    
    
    
    Layout::need_draw_border = true;
    
    Layout l(window, Layout::Vertical);
    l.setMargin(10.f);
    l.setPadding({5.f, 5.f});
    l.setPosition({10.f, 10.f});
    
    Layout l1(window, Layout::Horizontal);
    Layout l2(window, Layout::Vertical);
    Layout l3(window, Layout::Horizontal);
    Layout l4(window, Layout::Vertical);
    l1.setMargin(10.f);
    l1.setPadding({5.f, 5.f});
    l2.setMargin(10.f);
    l2.setPadding({5.f, 5.f});
    
    l1.addWidget(&b1);
    l1.addWidget(&b2);
    l1.addWidget(&t);
    l1.addWidget(&pb);
    l2.addWidget(&b3);
    l2.addWidget(&b4);
    l2.addWidget(&input);
    l2.addWidget(&ai);
    
    l4.addWidget(&sb);
    l4.addWidget(&cb);
    
    l3.addWidget(&l2);
    l3.addWidget(&i1);
    l3.addWidget(&l4);
    
    l.addWidget(&l1);
    l.addWidget(&l3);
    
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
                case sf::Keyboard::C:
                    window.close();
                    break;
                default:
                    break;
                }
            case sf::Event::MouseMoved:
                
                // printVector(window.mapPixelToCoords(event.mouseMove.x, event.mouseMove.y));
                
                break;
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
