#ifndef H_GAME_SCENE
#define H_GAME_SCENE



#include "../Core/Core.h"
#include "../Core/Game.h"



class GameScene : public Scene
{
public:
    
    GameScene(Core *core, Game *game);
    
    
    
    void onEvent(const sf::Event &event) override;
    
    void update(float frametime) override;
    
    void onOpen() override;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    
    
};




#endif // H_GAME_SCENE
