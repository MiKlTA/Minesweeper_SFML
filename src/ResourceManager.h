#ifndef H_RESOURCE_MANAGER
#define H_RESOURCE_MANAGER



#include <map>
#include <string>

#include "SFML/Graphics.hpp"



class ResourceManager
{
public:
    
    static void init(std::string path);
    
    
    
    static const sf::Texture * getTexture(std::string name);
    
    static const sf::Font * getFont(std::string name);
    
    
    
private:
    
    static std::string m_path;
    
    static std::map<std::string, sf::Texture*> m_textures;
    static std::map<std::string, sf::Font*>    m_fonts;
};



#endif // H_RESOURCE_MANAGER
