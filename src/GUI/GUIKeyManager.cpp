#include "GUIKeyManager.h"



GUIKeyManager::KeysContainer      GUIKeyManager::m_attached_keys
= GUIKeyManager::KeysContainer();

GUIKeyManager::ButtonsContainer   GUIKeyManager::m_attached_buttons
= GUIKeyManager::ButtonsContainer();



void GUIKeyManager::attachKey(std::string name, Key key)
{
    auto iter = m_attached_keys.find(name);
    if (iter != m_attached_keys.end())
    {
        m_attached_keys.erase(iter);
    }
    m_attached_keys.insert({name, key});
}

void GUIKeyManager::attachButton(std::string name, Button button)
{
    auto iter = m_attached_buttons.find(name);
    if (iter != m_attached_buttons.end())
    {
        m_attached_buttons.erase(iter);
    }
    m_attached_buttons.insert({name, button});
}



GUIKeyManager::Key GUIKeyManager::key(std::string name)
{
    auto iter = m_attached_keys.find(name);
    if (iter != m_attached_keys.end())
    {
        return (*iter).second;
    }
    return static_cast<GUIKeyManager::Key>(-1);
}

GUIKeyManager::Button GUIKeyManager::button(std::string name)
{
    auto iter = m_attached_buttons.find(name);
    if (iter != m_attached_buttons.end())
    {
        return (*iter).second;
    }
    return static_cast<GUIKeyManager::Button>(-1);
}
