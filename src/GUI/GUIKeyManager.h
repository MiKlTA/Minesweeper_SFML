#ifndef H_GUI_KEY_MANAGER
#define H_GUI_KEY_MANAGER



#include <map>
#include <string>

#include "SFML/Window.hpp"



class GUIKeyManager
{
public:
    
    using Key       = sf::Keyboard::Key;
    using Button    = sf::Mouse::Button;
    
    using KeysContainer = std::map<std::string, Key>;
    using ButtonsContainer = std::map<std::string, Button>;
    
    
    
    static void attachKey(std::string name, Key key);
    static void attachButton(std::string name, Button button);
    
    
    
    static Key key(std::string name);
    static Button button(std::string name);
    
    
    
private:
    
    static KeysContainer    m_attached_keys;
    static ButtonsContainer m_attached_buttons;
};



#endif // H_GUI_KEY_MANAGER
