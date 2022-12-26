#include "AnimatedImage.h"

#include "../Core/ResourceManager.h"




AnimatedImage::AnimatedImage(
        ResourceManager *resource_manager,
        const sf::RenderWindow &window, std::string animation_name,
        sf::Vector2u frame_size, unsigned int frames_count, unsigned int row,
        float delay_sec)
    : Widget(window),
      
      m_spritesheet(resource_manager->getTexture(animation_name)),
      
      m_frame_size(frame_size),
      m_frames_count(frames_count),
      m_row(row),
      
      m_delay(delay_sec),
      
      m_is_animated_now(false),
      m_need_repeat_animation(true)
{
    setSize(sf::Vector2f(frame_size));
}



void AnimatedImage::startAnimation()
{
    resetAnimation();
    m_is_animated_now = true;
}

bool AnimatedImage::isAnimatedNow() const
{
    return m_is_animated_now;
}

void AnimatedImage::breakAnimation()
{
    m_is_animated_now = false;
    resetAnimation();
}

void AnimatedImage::setRepeatAnimation(bool need_repeat)
{
    m_need_repeat_animation = need_repeat;
}



// protected:



bool AnimatedImage::canBeFocused_() const
{
    return false;
}



void AnimatedImage::onSizeChange(sf::Vector2f new_size)
{
    // TODO: ...
}



void AnimatedImage::draw_(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::IntRect rectangle = calcTextureRect();
    sf::Sprite frame(*m_spritesheet, rectangle);
    
    states.transform *= getTransform();
    target.draw(frame, states);
}



// private:



void AnimatedImage::resetAnimation()
{
    m_clock.restart();
}



sf::Vector2u AnimatedImage::calcFramePosition() const
{
    unsigned int frame_number;
    if (m_is_animated_now)
    {
        frame_number = static_cast<unsigned int>(
                    m_clock.getElapsedTime().asSeconds() / m_delay);
        if (m_need_repeat_animation)
        {
            frame_number %= m_frames_count;
        }
        else if (frame_number >= m_frames_count)
        {
            frame_number = 0;
        }
    }
    else
    {
        frame_number = 0;
    }
    
    sf::Vector2u frame_pos;
    frame_pos.y = m_row;
    frame_pos.x = frame_number;
    
    return frame_pos;
}



sf::IntRect AnimatedImage::calcTextureRect() const
{
    sf::Vector2u frame_position = calcFramePosition();
    
    int left = m_frame_size.x * frame_position.x;
    int top = m_frame_size.y * frame_position.y;
    int width = m_frame_size.x;
    int height = m_frame_size.y;
    return sf::IntRect(left, top, width, height);
}
