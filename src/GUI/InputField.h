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
    
    InputField(Theme theme, Text::Alignment alignment = Text::Alignment::Left);
    
    
    
    void onlyNumbers(bool isOnlyNumbers);
    
    
    
    std::wstring getText() const;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() override;
    
    
    
protected:
    
    void onEvent_(const sf::Event &event) override;
    void onSizeChange(sf::Vector2f new_size) override;
    void onPositionChange(sf::Vector2f new_position) override;
    
    
    
private:
    
    void recalcTextPosition(sf::Vector2f new_field_position);
    
    bool canPushSymbol(wchar_t symbol);
    
    
    
    Text m_text;
    
    bool m_only_numbers;
    unsigned int m_max_text_length;
    
    Theme           m_theme;
    Text::Alignment m_alignment;
    sf::Sprite      m_default_sprite;
    sf::Sprite      m_active_sprite;
    sf::Vector2f    m_text_padding;
    sf::Vector2f    m_text_shift;
};




#endif // H_INPUT_FIELD