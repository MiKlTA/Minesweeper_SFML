#include "ResourceManager.h"



ResourceManager::ResourceManager(std::string path)
    : m_path(path)
{
    
}

ResourceManager::~ResourceManager()
{
    for (auto texture : m_textures)
    {
        delete texture.second;
    }
    
    for (auto font : m_fonts)
    {
        delete font.second;
    }
}



const sf::Texture * ResourceManager::getTexture(std::string name)
{
    auto iter = m_textures.find(name);
    if (iter == m_textures.end())
    {
        sf::Texture *texture = new sf::Texture;
        texture->loadFromFile(m_path + "resources\\sprites\\" + name + ".png");
        iter = m_textures.emplace(name, texture).first;
    }
    (*iter).second->setSmooth(false);
    return (*iter).second;
}

const sf::Font * ResourceManager::getFont(std::string name)
{
    auto iter = m_fonts.find(name);
    if (iter == m_fonts.end())
    {
        sf::Font *font = new sf::Font;
        font->loadFromFile(m_path + "resources\\fonts\\" + name + ".ttf");
        iter = m_fonts.emplace(name, font).first;
    }
    return (*iter).second;
}
