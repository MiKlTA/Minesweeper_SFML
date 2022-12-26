#ifndef H_POPUP_YOU_SURE
#define H_POPUP_YOU_SURE



#include "Image.h"
#include "Text.h"
#include "Layout.h"
#include "Button.h"
          
#include "../Core/ResourceManager.h"
#include "../Core/KeyManager.h"



class PopupYouSure : public Widget
{
public:
    
    PopupYouSure(ResourceManager *resource_manager, KeyManager *key_manager,
                 const sf::RenderWindow &window, Text *title);
    ~PopupYouSure();
    
    
    
    void setImSureCallback(Button::CallbackType callback_Im_sure);
    
    
    
    bool canBeFocused() const override;
    bool isPassEvent(const sf::Event &event) override; 
    
    
    
protected:
    
    void onEvent_(const sf::Event &event) override;
    void onPositionChange(sf::Vector2f new_position) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    Layout *m_layout_vertical;
    Layout *m_layout_horisontal;
    
    Image *m_background;
    
    Text *m_title;
    
    Button *m_go_back;
    Button *m_Im_sure;
};



#endif // H_POPUP_YOU_SURE
