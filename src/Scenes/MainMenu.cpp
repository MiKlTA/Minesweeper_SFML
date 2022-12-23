#include "MainMenu.h"

#include "../GUI/Image.h"



MainMenu::MainMenu(Core *core, ResourceManager *resource_manager, sf::RenderWindow *window)
    : Scene(core),
      
      m_image(resource_manager, *window)
{
    m_image.setImage("tile");
    m_image.scale({0.5f, 0.5f});
}



void MainMenu::onEvent(const sf::Event &event)
{
    
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
}
