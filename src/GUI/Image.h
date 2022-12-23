#ifndef H_IMAGE
#define H_IMAGE



#include "Widget.h"



class ResourceManager;

class Image : public Widget
{
public:
    
    Image(ResourceManager *resource_manager, const sf::RenderWindow &window);
    
    
    
    void setImage(std::string image_name);
    void setRectangle(const sf::IntRect &rectangle);
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() const override;
    
    
    
protected:
    
    void onSizeChange(sf::Vector2f new_size) override;
    
    
    
private:
    
    ResourceManager *m_resource_manager;
    
    
    
    sf::Sprite m_image;
};



#endif // H_IMAGE
