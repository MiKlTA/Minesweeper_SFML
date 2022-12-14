#include "ResourceManager.h"



std::string ResourceManager::m_path;
std::map<std::string, sf::Texture*> ResourceManager::m_textures;



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
        texture->loadFromFile(m_path + name + ".png");
        iter = m_textures.emplace(name, texture).first;
    }
    return (*iter).second;
}
