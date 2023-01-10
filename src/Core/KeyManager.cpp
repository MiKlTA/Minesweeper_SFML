#include "KeyManager.h"




KeyManager::KeyManager()
{
    attachKey("left", sf::Keyboard::Left);
    attachKey("right", sf::Keyboard::Right);
    attachKey("up", sf::Keyboard::Up);
    attachKey("down", sf::Keyboard::Down);
    attachKey("enter", sf::Keyboard::Enter);
    attachKey("backspace", sf::Keyboard::Backspace);
    attachKey("shift", sf::Keyboard::RShift);
    attachKey("esc", sf::Keyboard::Escape);
    attachButton("left", sf::Mouse::Left);
    attachButton("right", sf::Mouse::Right);
}



void KeyManager::attachKey(std::string name, Key key)
{
    auto iter = m_attached_keys.find(name);
    if (iter != m_attached_keys.end())
    {
        m_attached_keys.erase(iter);
    }
    m_attached_keys.insert({name, key});
}

void KeyManager::attachButton(std::string name, Button button)
{
    auto iter = m_attached_buttons.find(name);
    if (iter != m_attached_buttons.end())
    {
        m_attached_buttons.erase(iter);
    }
    m_attached_buttons.insert({name, button});
}



KeyManager::Key KeyManager::key(std::string name) const
{
    auto iter = m_attached_keys.find(name);
    if (iter != m_attached_keys.end())
    {
        return (*iter).second;
    }
    return static_cast<KeyManager::Key>(-1);
}

KeyManager::Button KeyManager::button(std::string name) const
{
    auto iter = m_attached_buttons.find(name);
    if (iter != m_attached_buttons.end())
    {
        return (*iter).second;
    }
    return static_cast<KeyManager::Button>(-1);
}
