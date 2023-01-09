#include "SoundManager.h"



SoundManager::SoundManager(std::string path)
    : m_path(path)
{
    
}

SoundManager::~SoundManager()
{
    for (auto texture : m_sound_buffers)
    {
        delete texture.second;
    }
}



const sf::SoundBuffer * SoundManager::getSoundBuffer(std::string name)
{
    auto iter = m_sound_buffers.find(name);
    if (iter == m_sound_buffers.end())
    {
        sf::SoundBuffer *texture = new sf::SoundBuffer;
        texture->loadFromFile(m_path + "resources\\sounds\\" + name + ".ogg");
        iter = m_sound_buffers.emplace(name, texture).first;
    }
    return (*iter).second;
}
