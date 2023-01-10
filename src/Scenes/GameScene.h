#ifndef H_GAME_SCENE
#define H_GAME_SCENE



#include "../Core/SceneManager.h"
#include "../Core/Core.h"

#include "../GUI/Layout.h"
#include "../GUI/Image.h"
#include "../GUI/TextCell.h"
#include "../GUI/PopupYouSure.h"

#include "../GameWidget.h"
#include "../PopupMiniMenu.h"



class GameScene : public Scene
{
public:
    
    GameScene(Core *core, Game *game);
    
    
    
    void onEvent(const sf::Event &event) override;
    
    void update(float frametime) override;
    
    void onOpen() override;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    enum GameState
    {
        Playing,
        Lose,
        Win
    };
    
    
    
    KeyManager *m_key_manager;
    
    GameState       m_game_state;
    Game        *m_game;
    GameWidget  m_game_widget;
    
    Image m_background;
    
    Layout m_main_layout;
    
    TextCell m_time;
    TextCell m_mines;
    
    PopupMiniMenu m_popup_mini_menu;
    Text          m_win_or_lose;
    PopupYouSure  m_popup_win_or_lose;
};




#endif // H_GAME_SCENE
