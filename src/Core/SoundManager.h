#ifndef H_SOUND_MANAGER
#define H_SOUND_MANAGER



#include <map>
#include <string>

#include "SFML/Audio.hpp"



class SoundManager
{
public:
    
    SoundManager(std::string path);
    ~SoundManager();
    
    
    const sf::SoundBuffer * getSoundBuffer(std::string name);
    
    
    
private:
    
    std::string m_path;
    
    std::map<std::string, sf::SoundBuffer*> m_sound_buffers;
};



#endif // H_SOUND_MANAGER
