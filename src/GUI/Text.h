#ifndef H_TEXT
#define H_TEXT



#include "Widget.h"



class ResourceManager;

class Text : public Widget
{
public:
    
    enum Alignment
    {
        Left,
        Centre,
        Right
    };
    
    Text(ResourceManager *resource_manager,
         const sf::RenderWindow &window,
         Alignment alignment = Left, std::wstring text = L"");
    
    
    
    void setString(std::wstring text);
    void setCharacterSize(unsigned int size);
    void setColor(const sf::Color &color);
    
    void append(wchar_t symbol);
    void pop_back();
    
    std::wstring getString() const;
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    void onPositionChange(sf::Vector2f new_position) override;
    
    
    
    void computeTextPosition(sf::Vector2f new_position);
    void computeSize();
    
    
    
   sf::Text m_text;
   
   Alignment    m_alignment;
    
};



#endif // H_TEXT
