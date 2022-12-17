#include "Image.h"

#include "../ResourceManager.h"



Image::Image()
{
    
}



void Image::setImage(std::string image_name)
{
    m_image = sf::Sprite(*ResourceManager::getTexture(image_name));
    setSize(sf::Vector2f(m_image.getTexture()->getSize()));
}

void Image::setRectangle(const sf::IntRect &rectangle)
{
    m_image.setTextureRect(rectangle);
    setSize(sf::Vector2f(rectangle.width, rectangle.height));
}



void Image::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_image, states);
}



bool Image::canBeFocused()
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
