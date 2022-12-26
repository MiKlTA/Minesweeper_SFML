#ifndef H_SCENE_MANAGER
#define H_SCENE_MANAGER



#include <list>
#include <map>

#include "Scene.h"



class SceneManager
{
public:
    
    SceneManager();
    
    
    
    void setScenesBufferSize(unsigned int buffer_size);
    
    
    
    void addScene(std::string scene_name, Scene *scene);
    
    Scene * getCurrentScene();
    
    void setScene(std::string scene_name);
    Scene * goBack();
    
    
    
private:
    
    using SceneContainer = std::map<std::string, Scene *>;
    using ScenesBufferType = std::list<Scene *>;
    
    Scene * findScene(std::string scene_name);
    
    
    
    SceneContainer  m_scenes;
    Scene          *m_current_scene;
    
    ScenesBufferType    m_scenes_buffer;
    unsigned int        m_scenes_buffer_size;
};



#endif // H_SCENE_MANAGER
