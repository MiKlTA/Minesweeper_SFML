#ifndef H_PROGRESS_BAR
#define H_PROGRESS_BAR



#include "Widget.h"

#include "Image.h"



class ProgressBar : public Widget
{
public:
    
    enum Type
    {
        Horisontal,
        Vertical
    };
    
    enum Mode
    {
        
    };
    
    
    
    ProgressBar(ResourceManager *resource_manager,
            const sf::RenderWindow &window, Type type,
            unsigned int elements_count, float elements_interval);
    
    
    
    void setProgressValue(float value);
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() const override;
    
    
    
protected:
    
    void onSizeChange(sf::Vector2f new_size) override;
    void onPositionChange(sf::Vector2f new_position) override;
    
    
    
private:
    
    void recalcProgressElementSize(sf::Vector2f widget_size);
    unsigned int progress() const;
    
    
    
    
    Image       m_bar;
    sf::Sprite  m_progress_element;
    
    Type        m_type;
    float       m_padding;
    
    float           m_progress;
    unsigned int    m_elements_count;
    float           m_elements_interval;
};



#endif // H_PROGRESS_BAR
