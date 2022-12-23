#ifndef H_ANIMATED_IMAGE
#define H_ANIMATED_IMAGE



#include "Widget.h"



class ResourceManager;

class AnimatedImage : public Widget
{
public:
    
    AnimatedImage(ResourceManager *resource_manager,
                  const sf::RenderWindow &window, std::string animation_name,
                  sf::Vector2u frame_size, unsigned int frames_count, unsigned int row,
                  float delay_sec);
    
    
    
    void startAnimation();
    bool isAnimatedNow() const;
    void breakAnimation();
    
    void setRepeatAnimation(bool need_repeat);
    void setRowAnimation(unsigned int row);
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() const override;
    
    
    
protected:
    
    void onSizeChange(sf::Vector2f new_size) override;
    
    
    
private:
    
    void resetAnimation();
    
    sf::Vector2u    calcFramePosition() const;
    sf::IntRect     calcTextureRect() const;
    
    
    
    const sf::Texture *m_spritesheet;
    
    sf::Vector2u    m_frame_size;
    unsigned int    m_frames_count;
    unsigned int    m_row;
    
    sf::Clock       m_clock;
    float           m_delay;
    
    bool            m_is_animated_now;
    bool            m_need_repeat_animation;
};



#endif // H_ANIMATED_IMAGE
