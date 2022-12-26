#ifndef H_GAME_SCENE
#define H_GAME_SCENE



#include "../Core/SceneManager.h"
#include "../Core/Game.h"



class GameScene : public Scene
{
public:
    
    GameScene(SceneManager *scene_manager, Game *game);
    
    
    
    void onEvent(const sf::Event &event) override;
    
    void update(float frametime) override;
    
    void onOpen() override;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    
    
};




#endif // H_GAME_SCENE
