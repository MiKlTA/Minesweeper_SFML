#ifndef H_TEXT_CELL
#define H_TEXT_CELL



#include "Widget.h"

#include "Text.h"



class TextCell : public Widget
{
public:
    
    TextCell(ResourceManager *resource_manager, const sf::RenderWindow &window,
            Text::Alignment alignment = Text::Alignment::Left, std::wstring text = L"");
    
    
    
    void setString(std::wstring string);
    void setColor(sf::Color color);
    void append(wchar_t symbol);
    void pop_back();
    
    
    
    void setTextPadding(float text_padding);
    void setTextShift(sf::Vector2f text_shift);
    
    void setMaxTextLength(unsigned int max_text_length);
    
    
    
    std::wstring getString() const;
    
    bool canPushSymbol(wchar_t symbol);
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    void onSizeChange(sf::Vector2f new_size) override;
    void onPositionChange(sf::Vector2f new_position) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    void recalcTextPosition(sf::Vector2f new_field_position);
    
    
    
    Text m_text;
    
    bool m_only_numbers;
    unsigned int m_max_text_length;
    
    Text::Alignment m_alignment;
    float    m_text_padding;
    sf::Vector2f    m_text_shift;
};




#endif // H_INPUT_FIELD
