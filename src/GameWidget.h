#ifndef H_GAME_WIDGET
#define H_GAME_WIDGET



#include "Core/Core.h"

#include "GUI/PopupYouSure.h"



class GameWidget : public Widget
{
public:
    
    GameWidget(Core *core, Game *game);
    
    
    
    void refresh();
    
    
    
    bool isPassEvent(const sf::Event &event) override;
    
    
    
protected:
    
    bool canBeFocused_() const override;
    
    
    
    void onEvent_(const sf::Event &event) override;
    
    
    
    void draw_(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    sf::IntRect getNumberTexRect(int number) const;
    sf::IntRect getMineTexRect() const;
    sf::IntRect getDuckTexRect() const;
    sf::IntRect getFlagTexRect() const;
    
    sf::IntRect getClosedTileTexRect() const;
    sf::IntRect getHoveredTIleTexRect() const;
    sf::IntRect getOpenedTileTexRect() const;
    
    
    
    Game            *m_game;
    ResourceManager *m_resource_manager;
    KeyManager      *m_key_manager;
    Config          *m_config;
    
    sf::Vector2f m_padding;
    sf::Vector2f m_real_size;
    
    sf::Vector2u m_focus_position;
};



#endif // H_GAME_WIDGET
