#ifndef H_GAME_SCENE
#define H_GAME_SCENE



#include "../Core/SceneManager.h"
#include "../Core/Core.h"

#include "../GUI/Layout.h"
#include "../GUI/Image.h"
#include "../GUI/TextCell.h"

#include "../GameWidget.h"



class GameScene : public Scene
{
public:
    
    GameScene(Core *core, Game *game);
    
    
    
    void onEvent(const sf::Event &event) override;
    
    void update(float frametime) override;
    
    void onOpen() override;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    GameWidget m_game_widget;
    
    Image m_background;
    
    Layout m_main_layout;
    
    TextCell m_time;
    TextCell m_mines;
};




#endif // H_GAME_SCENE
