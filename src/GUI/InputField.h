#ifndef H_INPUT_FIELD
#define H_INPUT_FIELD



#include "Widget.h"

#include "Image.h"
#include "TextCell.h"



class KeyManager;

class InputField : public Widget
{
public:
    
    enum Theme
    {
        Blue
    };
    
    InputField(ResourceManager *resource_manager, KeyManager *key_manager,
               const sf::RenderWindow &window,
               Theme theme, Text::Alignment alignment = Text::Alignment::Left);
    
    
    
    void onlyNumbers(bool isOnlyNumbers);
    
    
    
    std::wstring getText() const;
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    void onEvent_(const sf::Event &event) override;
    void onSizeChange(sf::Vector2f new_size) override;
    void onPositionChange(sf::Vector2f new_position) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    KeyManager *m_key_manager;
    
    
    
    TextCell m_text;
    
    bool m_only_numbers;
    unsigned int m_max_text_length;
    
    Theme           m_theme;
    Text::Alignment m_alignment;
    Image           m_field_default;
    Image           m_field_active;
    float    m_text_padding;
    sf::Vector2f    m_text_shift;
};




#endif // H_INPUT_FIELD
