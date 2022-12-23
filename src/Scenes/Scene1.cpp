#include "Scene1.h"

#include "../GUI/Image.h"



Scene1::Scene1(Core *core,
                   ResourceManager *resource_manager, KeyManager *key_manager,
                   sf::RenderWindow *window)
    : Scene(core),
      
      m_image(resource_manager, *window),
      
      m_button(resource_manager, key_manager, *window,
               Button::Theme::Red, L"BAACK!!!",
               [core](){
               core->setScene("MainMenu");
               })
{
    m_image.setImage("tile");
    m_image.scale({0.5f, 0.5f});
    m_image.setPosition({200.f, 100.f});
    
    
}



void Scene1::onEvent(const sf::Event &event)
{
    m_button.onEvent(event);
}

void Scene1::update(float frametime)
{
    
}

void Scene1::onOpen()
{
    
}



void Scene1::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_image);
    target.draw(m_button);
}
