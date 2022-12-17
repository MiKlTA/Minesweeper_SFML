#ifndef H_IMAGE
#define H_IMAGE



#include "Widget.h"



class Image : public Widget
{
public:
    
    Image();
    
    
    
    void setImage(std::string image_name);
    void setRectangle(const sf::IntRect &rectangle);
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() override;
    
    
    
protected:
    
    void onSizeChange(sf::Vector2f new_size) override;
    
    
    
private:
    
    sf::Sprite m_image;
};



#endif // H_IMAGE
