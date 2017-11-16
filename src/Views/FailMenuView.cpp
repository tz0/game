#include "Views/FailMenuView.h"

namespace tjg{
    FailMenuView::FailMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, SoundManager &sound_manager) :
            View(window, resource_manager, sound_manager) {}


    void FailMenuView::Initialize(const unsigned int level_number) {
        current_level = level_number;
        selection = 0;
        auto background_texture = resource_manager.LoadTexture("menu-fail.jpg");
        background_sprite.setTexture(*background_texture);
        options = {ViewSwitch {State::PLAYING, 0}, ViewSwitch {State::MAIN_MENU, 0}};

        selection_box_position = sf::Vector2f(FAIL_MENU_BOX_X, FAIL_MENU_BOX_Y_UP);
        selection_box.setSize(sf::Vector2f(363,43));
        selection_box.setPosition(selection_box_position);
        selection_box.setFillColor(sf::Color::Transparent);
        selection_box.setOutlineColor(sf::Color(255, 255, 255, 255));
        selection_box.setOutlineThickness(2.0f);
    }


    //TODO: Implement or remove
    void FailMenuView::Update() {
        selection_box.setPosition(selection_box_position);
    }


    void FailMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(background_sprite);
        window.draw(selection_box);
        window.display();
    }

    ViewSwitch FailMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 0) {
                            selection -= 1;
                            selection_box_position.y -= FAIL_MENU_BOX_SHIFT;
                        } else {
                            selection = FAIL_MENU_OPTIONS;
                            selection_box_position.y = FAIL_MENU_BOX_Y_LOW;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (selection < FAIL_MENU_OPTIONS) {
                            selection += 1;
                            selection_box_position.y += FAIL_MENU_BOX_SHIFT;
                        } else {
                            selection = 0;
                            selection_box_position.y = FAIL_MENU_BOX_Y_UP;
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