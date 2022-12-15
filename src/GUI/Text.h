#ifndef H_TEXT
#define H_TEXT



#include "Widget.h"



class Text : public Widget
{
public:
    
    Text(std::wstring text = L"");
    
    
    
    void setString(std::wstring text);
    void setCharacterSize(unsigned int size);
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
   sf::Text m_text;
    
};



#endif // H_TEXT
