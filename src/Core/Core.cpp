#include "Core.h"



Core::Core()
    : m_scenes_buffer_size(256)
{
    
}



void Core::setScenesBufferSize(unsigned int buffer_size)
{
    m_scenes_buffer_size = buffer_size;
}



void Core::addScene(std::string scene_name, Scene *scene)
{
    m_scenes.insert({scene_name, scene});
}

Scene * Core::getCurrentScene()
{
    return m_current_scene;
}

void Core::setScene(std::string scene_name)
{
    Scene *scene = findScene(scene_name);
    if (scene != nullptr)
    {
        m_current_scene = scene;
        m_scenes_buffer.push_back(scene);
        if (m_scenes_buffer.size() > m_scenes_buffer_size)
        {
            m_scenes_buffer.pop_front();
        }
    }
}

Scene * Core::goBack()
{
    if (m_scenes_buffer.size() <= 1)
    {
        return nullptr;
    }
    else
    {
        m_scenes_buffer.pop_back();
        m_current_scene = m_scenes_buffer.back();
        return m_current_scene;
    }
}



// private:



Scene * Core::findScene(std::string scene_name)
{
    SceneContainer::iterator iter = m_scenes.find(scene_name);
    if (iter == m_scenes.end())
    {
        return nullptr;
    }
    else
    {
        return (*iter).second;
    }
}
