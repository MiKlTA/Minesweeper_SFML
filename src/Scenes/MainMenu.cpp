#include "MainMenu.h"

#include "../GUI/Image.h"



MainMenu::MainMenu(Core *core,
                   ResourceManager *resource_manager, KeyManager *key_manager,
                   sf::RenderWindow *window)
    : Scene(core),
      
      m_image(resource_manager, *window),
      
      m_button(resource_manager, key_manager, *window,
               Button::Theme::Red, L"GOOO!!!",
               [core](){
               core->setScene("Scene1");
               })
{
    m_image.setImage("tile");
    m_image.scale({0.5f, 0.5f});
    
    m_button.setPosition({200.f, 200.f});
}



void MainMenu::onEvent(const sf::Event &event)
{
    m_button.onEvent(event);
}

void MainMenu::update(float frametime)
{
    
}

void MainMenu::onOpen()
{
    
}



void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_image);
    target.draw(m_button);
}
