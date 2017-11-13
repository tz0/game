#include "Views/PauseMenuView.h"

namespace tjg{
    PauseMenuView::PauseMenuView(ResourceManager &resource_manager, sf::RenderWindow &window) :
            View(window,resource_manager) {}


    void PauseMenuView::Initialize(const unsigned int level_number) {
        current_level = level_number;
        selection = 0;
        auto background_texture = resource_manager.LoadTexture("pause-menu.png");
        background_sprite.setTexture(*background_texture);
        options = {ViewSwitch {State::RESUME, 0}, ViewSwitch {State::LEVEL_MENU, 0}, ViewSwitch {State::PLAYING, 0}, ViewSwitch {State::MAIN_MENU, 0}};

        selection_box_position = sf::Vector2f(PAUSE_MENU_BOX_X, PAUSE_MENU_BOX_Y_UP);
        selection_box.setSize(sf::Vector2f(363,43));
        selection_box.setPosition(selection_box_position);
        selection_box.setFillColor(sf::Color::Transparent);
        selection_box.setOutlineColor(sf::Color(255, 255, 255, 255));
        selection_box.setOutlineThickness(2.0f);
    }


    //TODO: Implement or remove
    void PauseMenuView::Update() {
        selection_box.setPosition(selection_box_position);
    }


    void PauseMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(background_sprite);
        window.draw(selection_box);
        window.display();
    }

    ViewSwitch PauseMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 0) {
                            selection -= 1;
                            selection_box_position.y -= PAUSE_MENU_BOX_SHIFT;
                        } else {
                            selection = PAUSE_MENU_OPTIONS;
                            selection_box_position.y = PAUSE_MENU_BOX_Y_LOW;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (selection < PAUSE_MENU_OPTIONS) {
                            selection += 1;
                            selection_box_position.y += PAUSE_MENU_BOX_SHIFT;
                        } else {
                            selection = 0;
                            selection_box_position.y = PAUSE_MENU_BOX_Y_UP;
                        }
                        break;
                    case sf::Keyboard::Return:
                        return options[selection];
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
        return ViewSwitch {State::CONTINUE, 0};
    }

}