#include "Image.h"

#include "../ResourceManager.h"



Image::Image(std::string image_name)
    : m_image(*ResourceManager::getTexture(image_name))
{
    
}

Image::Image(std::string image_name, sf::IntRect rectangle)
    : m_image(*ResourceManager::getTexture(image_name), rectangle)
{
    
}



void Image::setRectangle(const sf::IntRect &rectangle)
{
    m_image.setTextureRect(rectangle);
}



void Image::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_image, states);
}
