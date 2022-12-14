#ifndef H_IMAGE
#define H_IMAGE



#include "Widget.h"



class Image : public Widget
{
public:
    
    Image(std::string image_name);
    
    Image(std::string image_name, sf::IntRect rectangle);
    
    
    
    void setRectangle(const sf::IntRect &rectangle);
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    sf::Sprite m_image;
};



#endif // H_IMAGE
