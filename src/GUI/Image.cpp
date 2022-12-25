#include "Image.h"

#include "../Core/ResourceManager.h"



Image::Image(ResourceManager *resource_manager, const sf::RenderWindow &window)
    : Widget(window),
      
      m_resource_manager(resource_manager)
{
    
}



void Image::setImage(std::string image_name)
{
    m_image = sf::Sprite(*m_resource_manager->getTexture(image_name));
    setSize(sf::Vector2f(m_image.getTexture()->getSize()));
}

void Image::setRectangle(const sf::IntRect &rectangle)
{
    m_image.setTextureRect(rectangle);
    setSize(sf::Vector2f(rectangle.width, rectangle.height));
}



bool Image::canBeFocused() const
{
    return false;
}



// protected:



void Image::onSizeChange(sf::Vector2f new_size)
{
    if (getSize().x != 0 && getSize().y != 0)
    {
        m_image.scale(new_size.x / getSize().x, new_size.y / getSize().y);
    }
}



void Image::draw_(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_image, states);
}
