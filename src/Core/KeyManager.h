#ifndef H_GUI_KEY_MANAGER
#define H_GUI_KEY_MANAGER



#include <map>
#include <string>

#include "SFML/Window.hpp"



class KeyManager
{
public:
    
    using Key       = sf::Keyboard::Key;
    using Button    = sf::Mouse::Button;
    
    using KeysContainer = std::map<std::string, Key>;
    using ButtonsContainer = std::map<std::string, Button>;
    
    
    
    KeyManager();
    
    
    
    void attachKey(std::string name, Key key);
    void attachButton(std::string name, Button button);
    
    
    
    Key key(std::string name) const;
    Button button(std::string name) const;
    
    
    
private:
    
    KeysContainer    m_attached_keys;
    ButtonsContainer m_attached_buttons;
};



#endif // H_GUI_KEY_MANAGER
