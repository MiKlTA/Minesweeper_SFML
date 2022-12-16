#ifndef H_TEXT
#define H_TEXT



#include "Widget.h"



class Text : public Widget
{
public:
    
    enum Alignment
    {
        Left,
        Centre,
        Right
    };
    
    Text(Alignment alignment = Left, std::wstring text = L"");
    
    
    
    void setString(std::wstring text);
    void setCharacterSize(unsigned int size);
    void setColor(const sf::Color &color);
    
    void append(wchar_t symbol);
    void pop_back();
    
    std::wstring getString() const;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
    bool canBeFocused() override;
    
    
        
private:
    
    void onPositionChange(sf::Vector2f new_position) override;
    
    
    
    void computeTextPosition(sf::Vector2f new_position);
    void computeSize();
    
    
    
   sf::Text m_text;
   
   Alignment    m_alignment;
   float        m_spacing;
    
};



#endif // H_TEXT
