#include "PopupGameSettings.h"



PopupGameSettings::PopupGameSettings(Core *core, Game *game, Button::CallbackType apply_callback)
    : Widget(*core->getWindow()),
      
      m_game(game),
      
      m_main_layout(core->getKeyManager(), *core->getWindow(),
                    Layout::Type::Vertical, Layout::Alignment::Left),
      
      m_scrollbars_layout(core->getKeyManager(), *core->getWindow(),
                          Layout::Type::Vertical, Layout::Alignment::Left),
      m_labels_layout(core->getKeyManager(), *core->getWindow(),
                      Layout::Type::Vertical, Layout::Alignment::Right),
      m_icons_layout(core->getKeyManager(), *core->getWindow(),
                     Layout::Type::Vertical, Layout::Alignment::Right),
      
      m_main_horisontal_layout(core->getKeyManager(), *core->getWindow(),
                               Layout::Type::Horizontal, Layout::Alignment::Left),
      m_buttons_layout(core->getKeyManager(), *core->getWindow(),
                       Layout::Type::Horizontal, Layout::Alignment::Centre),
      
      m_background(core->getResourceManager(), *core->getWindow()),
      
      
      
      m_field_width(core->getResourceManager(), core->getKeyManager(),
                    *core->getWindow(), ScrollBar::Theme::Default,
                    ScrollBar::Type::Horisontal,
                    game->getMinFieldSize().x, game->getMaxFieldSize().x),
      m_field_height(core->getResourceManager(), core->getKeyManager(),
                     *core->getWindow(), ScrollBar::Theme::Default,
                     ScrollBar::Type::Horisontal,
                     game->getMinFieldSize().y, game->getMaxFieldSize().y),
      m_mines_count(core->getResourceManager(), core->getKeyManager(),
                    *core->getWindow(), ScrollBar::Theme::Default,
                    ScrollBar::Type::Horisontal,
                    game->getTotalMinesNumber(), game->getMaxTotalMinesNumber()),
      m_ducks_count(core->getResourceManager(), core->getKeyManager(),
                    *core->getWindow(), ScrollBar::Theme::Default,
                    ScrollBar::Type::Horisontal,
                    game->getMinTotalDucksNumber(), game->getMaxTotalDucksNumber()),
      
      m_field_width_label(core->getResourceManager(), *core->getWindow(),
                          Text::Alignment::Right,
                          std::to_wstring(game->getFieldSize().x)),
      m_field_height_label(core->getResourceManager(), *core->getWindow(),
                           Text::Alignment::Right,
                           std::to_wstring(game->getFieldSize().y)),
      m_mines_count_label(core->getResourceManager(), *core->getWindow(),
                          Text::Alignment::Right,
                          std::to_wstring(game->getTotalMinesNumber())),
      m_ducks_count_label(core->getResourceManager(), *core->getWindow(),
                          Text::Alignment::Right,
                          std::to_wstring(game->getTotalDucksNumber())),
      
      m_width_image(core->getResourceManager(), *core->getWindow()),
      m_height_image(core->getResourceManager(), *core->getWindow()),
      m_mine_image(core->getResourceManager(), *core->getWindow()),
      m_duck_image(core->getResourceManager(), *core->getWindow()),
      
      m_go_back(core->getResourceManager(), core->getSoundManager(),
                core->getKeyManager(), *core->getWindow(),
                Button::Theme::Default, L"Back"),
      m_start(core->getResourceManager(), core->getSoundManager(),
              core->getKeyManager(), *core->getWindow(),
                Button::Theme::Default, L"Apply"),
      
      
      
      m_popup_case_new_game(core, game, this, apply_callback)
{
    m_go_back.setCallback([this](){
        this->setHide(!this->isHidden());
    });
    m_start.setCallback([game, this, apply_callback]()
    {
        if (game->haveCreatedField())
        {
            m_popup_case_new_game.setHide(false);
        }
        else
        {
            apply_callback();
        }
    });
    
    m_buttons_layout.setPadding({35.f, 0.f, 35.f, 30.f});
    m_buttons_layout.setMargin(30.f);
    m_buttons_layout.addWidget(&m_go_back);
    m_buttons_layout.addWidget(&m_start);
    
    
    
    m_width_image.setImage("width");
    m_width_image.scale({2.f, 2.f});
    m_height_image.setImage("height");
    m_height_image.scale({2.f, 2.f});
    m_mine_image.setImage("content");
    m_mine_image.setRectangle({0, 0,
                               core->getConfig()->contentSize().x,
                               core->getConfig()->contentSize().y
                              });
    m_mine_image.scale({2.f, 2.f});
    m_duck_image.setImage("content");
    m_duck_image.setRectangle({core->getConfig()->contentSize().x, 0,
                               core->getConfig()->contentSize().x,
                               core->getConfig()->contentSize().y
                              });
    m_duck_image.scale({2.f, 2.f});
    
    float icons_layout_margin = 16.f;
    m_icons_layout.setMargin(icons_layout_margin);
    m_icons_layout.addWidget(&m_width_image);
    m_icons_layout.addWidget(&m_height_image);
    m_icons_layout.addWidget(&m_mine_image);
    m_icons_layout.addWidget(&m_duck_image);
    
    
    
    m_field_width_label.setSize({50.f, 16.f});
    m_field_height_label.setSize({50.f, 16.f});
    m_mines_count_label.setSize({50.f, 16.f});
    m_ducks_count_label.setSize({50.f, 16.f});
    
    alignLayoutRelativeTo(&m_icons_layout, &m_labels_layout,
                          m_width_image.getSize().y, m_field_width_label.getSize().y);
    m_labels_layout.addWidget(&m_field_width_label);
    m_labels_layout.addWidget(&m_field_height_label);
    m_labels_layout.addWidget(&m_mines_count_label);
    m_labels_layout.addWidget(&m_ducks_count_label);
    
    
    
    m_field_width.setOnValueChangeCallback([this](){
        m_mines_count.setRange(m_game->getMinTotalMinesNumber(),
                               m_game->getMaxTotalMinesNumber());
        m_ducks_count.setRange(m_game->getMinTotalDucksNumber(),
                               m_game->getMaxTotalDucksNumber());
        
        updateGame();
        updateLabels();
    });
    m_field_width.setSliderValue(game->getFieldSize().x);
    m_field_height.setOnValueChangeCallback([this](){
        m_mines_count.setRange(m_game->getMinTotalMinesNumber(),
                               m_game->getMaxTotalMinesNumber());
        m_ducks_count.setRange(m_game->getMinTotalDucksNumber(),
                               m_game->getMaxTotalDucksNumber());
        
        updateGame();
        updateLabels();
    });
    m_field_height.setSliderValue(game->getFieldSize().y);
    m_mines_count.setOnValueChangeCallback([this](){
        m_ducks_count.setRange(m_game->getMinTotalDucksNumber(),
                               m_game->getMaxTotalDucksNumber());
        
        updateGame();
        updateLabels();
    });
    m_mines_count.setSliderValue(game->getTotalMinesNumber());
    m_ducks_count.setOnValueChangeCallback([this](){
        m_mines_count.setRange(m_game->getMinTotalMinesNumber(),
                               m_game->getMaxTotalMinesNumber());
        
        updateGame();
        updateLabels();
    });
    m_ducks_count.setSliderValue(game->getTotalDucksNumber());
    
    alignLayoutRelativeTo(&m_labels_layout, &m_scrollbars_layout,
                          m_field_width_label.getSize().y, m_field_width.getSize().y);
    m_scrollbars_layout.addWidget(&m_field_width);
    m_scrollbars_layout.addWidget(&m_field_height);
    m_scrollbars_layout.addWidget(&m_mines_count);
    m_scrollbars_layout.addWidget(&m_ducks_count);
    
    
    
    m_main_horisontal_layout.setPadding({40.f, 20.f, 10.f, 30.f});
    m_main_horisontal_layout.setMargin(20.f);
    m_main_horisontal_layout.addWidget(&m_scrollbars_layout);
    m_main_horisontal_layout.addWidget(&m_labels_layout);
    m_main_horisontal_layout.addWidget(&m_icons_layout);
    
    m_main_layout.addWidget(&m_main_horisontal_layout);
    m_main_layout.addWidget(&m_buttons_layout);
    
    
    
    m_background.setImage("popup_game_settings");
    m_background.setSize(m_main_layout.getSize());
    
    setSize(m_background.getSize());
    
    m_popup_case_new_game.setHide(true);
    
    core->goToCentre(this);
}



void PopupGameSettings::returnSliderToActualPositions()
{
    m_field_width.setSliderValue(m_game->getFieldSize().x);
    m_field_height.setSliderValue(m_game->getFieldSize().y);
    m_mines_count.setSliderValue(m_game->getTotalMinesNumber());
    m_ducks_count.setSliderValue(m_game->getTotalDucksNumber());
}



bool PopupGameSettings::isPassEvent(const sf::Event &)
{
    return false;
}



void PopupGameSettings::alignLayoutRelativeTo(const Layout *sample, Layout *target,
                                              float sample_element_heignt, float target_element_height)
{
    target->setPadding({
                           0.f,
                           (sample_element_heignt - target_element_height) / 2.f
                           + sample->getPadding().top,
                           0.f,
                           (sample_element_heignt - target_element_height) / 2.f
                           + sample->getPadding().bottom}
                       );
    target->setMargin(sample->getMargin()
                      + std::abs(target_element_height - sample_element_heignt));
}



// protected:



bool PopupGameSettings::canBeFocused_() const
{
    return true;
}



void PopupGameSettings::onEvent_(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed
            && !containsPoint({event.mouseButton.x, event.mouseButton.y}))
    {
        setHide(true);
    }
    
    m_background.onEvent(event);
    m_main_layout.onEvent(event);
    m_popup_case_new_game.onEvent(event);
}

void PopupGameSettings::onPositionChange(sf::Vector2f new_position)
{
    sf::Vector2f delta = new_position - getPosition();
    m_background.move(delta);
    m_main_layout.move(delta);
}

void PopupGameSettings::onStateChange(State new_state)
{
    m_main_layout.setState(new_state);
}



void PopupGameSettings::draw_(sf::RenderTarget &target, sf::RenderStates) const
{
    target.draw(m_background);
    target.draw(m_main_layout);
    target.draw(m_popup_case_new_game);
}



// private:



void PopupGameSettings::updateLabels()
{
    m_field_width_label.setString(std::to_wstring(m_field_width.getSliderValue()));
    m_field_height_label.setString(std::to_wstring(m_field_height.getSliderValue()));
    m_mines_count_label.setString(std::to_wstring(m_mines_count.getSliderValue()));
    m_ducks_count_label.setString(std::to_wstring(m_ducks_count.getSliderValue()));
}

void PopupGameSettings::updateGame()
{
    m_game->setFieldSize({m_field_width.getSliderValue(), m_game->getFieldSize().y});
    m_game->setFieldSize({m_game->getFieldSize().x, m_field_height.getSliderValue()});
    m_game->setTotalMinesNumber(m_mines_count.getSliderValue());
    m_game->setTotalDucksNumber(m_ducks_count.getSliderValue());
}

void PopupGameSettings::updateMineScrollbar()
{
    m_mines_count.setRange(m_game->getTotalMinesNumber(),
                           m_game->getMaxTotalMinesNumber());
    m_ducks_count.setRange(m_game->getMinTotalDucksNumber(),
                           m_game->getMaxTotalDucksNumber());
}

void PopupGameSettings::updateDuckScrollbar()
{
    m_mines_count.setRange(m_game->getTotalMinesNumber(),
                           m_game->getMaxTotalMinesNumber());
    m_ducks_count.setRange(m_game->getMinTotalDucksNumber(),
                           m_game->getMaxTotalDucksNumber());
}
