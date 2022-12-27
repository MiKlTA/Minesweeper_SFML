#ifndef H_MAIN_MENU
#define H_MAIN_MENU



#include "../PopupGameSettings.h"

#include "../Core/Core.h"

#include "../GUI/Layout.h"
#include "../GUI/Button.h"
#include "../GUI/Image.h"
#include "../GUI/PopupYouSure.h"



class MainMenu : public Scene
{
public:
    
    MainMenu(Core *core, SceneManager *scene_manager, Game *game);
    
    
    
    void onEvent(const sf::Event &event) override;
    
    void update(float frametime) override;
    
    void onOpen() override;
    
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    
private:
    
    static void configureButton(Button *button);
    
    
    
    KeyManager *m_key_manager;
    
    
    
    Layout *m_layout;
    
    Image *m_background;
    
    Button *m_continue_core;
    Button *m_new_core;
    Button *m_settings;
    Button *m_exit;
    
    
    
    PopupYouSure *m_popup_im_sure;
    PopupGameSettings *m_popup_core_settings;
    
};



#endif // H_MAIN_MENU
