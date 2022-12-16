#ifndef H_INPUT_FIELD
#define H_INPUT_FIELD



#include "Widget.h"
#include "Text.h"



class InputField : public Widget
{
public:
    
    enum Theme
    {
        Blue
    };
    
    InputField(Theme theme);
    
    
    
    std::wstring getText() const;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() override;
    
    
    
protected:
    
    void onEvent_(const sf::Event &event) override;
    void onSizeChange(sf::Vector2f new_size) override;
    void onPositionChange(sf::Vector2f new_position) override;
    void onStateChange(State new_state) override;
    
    
    
private:
    
    Text m_text;
    
    Theme m_theme;
    sf::Sprite m_default_sprite;
    sf::Sprite m_active_sprite;
    sf::Vector2f m_text_padding;
};




#endif // H_INPUT_FIELD
