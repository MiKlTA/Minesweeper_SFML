#include "ResourceManager.h"



std::string ResourceManager::m_path;
std::map<std::string, sf::Texture*> ResourceManager::m_textures;
std::map<std::string, sf::Font*> ResourceManager::m_fonts;



void ResourceManager::init(std::string path)
{
    m_path = path;
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
