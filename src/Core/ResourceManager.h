#ifndef H_RESOURCE_MANAGER
#define H_RESOURCE_MANAGER



#include <map>
#include <string>

#include "SFML/Graphics.hpp"



class ResourceManager
{
public:
    
    ResourceManager(std::string path);
    ~ResourceManager();
    
    
    const sf::Texture * getTexture(std::string name);
    
    const sf::Font * getFont(std::string name);
    
    
    
private:
    
    std::string m_path;
    
    std::map<std::string, sf::Texture*> m_textures;
    std::map<std::string, sf::Font*>    m_fonts;
};



#endif // H_RESOURCE_MANAGER
