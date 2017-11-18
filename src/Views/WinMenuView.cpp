#include "Views/WinMenuView.h"

namespace tjg{
    WinMenuView::WinMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, std::shared_ptr<SoundManager> &sound_manager) :
            View(window, resource_manager, sound_manager) {}


    void WinMenuView::Initialize(const unsigned int level_number) {
        current_level = level_number;
        selection = 0;
        auto background_texture = resource_manager.LoadTexture("menu-win.jpg");
        background_sprite.setTexture(*background_texture);
        options = {ViewSwitch {State::PLAYING, current_level + 1}, ViewSwitch {State::PLAYING, 0}, ViewSwitch {State::MAIN_MENU, 0}};

        selection_box_position = sf::Vector2f(WIN_MENU_BOX_X, WIN_MENU_BOX_Y_UP);
        selection_box.setSize(sf::Vector2f(363,43));
        selection_box.setPosition(selection_box_position);
        selection_box.setFillColor(sf::Color::Transparent);
        selection_box.setOutlineColor(sf::Color(255, 255, 255, 255));
        selection_box.setOutlineThickness(2.0f);

        // Stop level sounds.
        sound_manager->StopSpatialSounds();
        sound_manager->StopLevelMusic();

        // Start music.
        sound_manager->StartWinMusic();
    }

    void WinMenuView::Update() {
        selection_box.setPosition(selection_box_position);
    }

    void WinMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(background_sprite);
        window.draw(selection_box);
        window.display();
    }

    ViewSwitch WinMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 0) {
                            selection -= 1;
                            selection_box_position.y -= WIN_MENU_BOX_SHIFT;
                        } else {
                            selection = WIN_MENU_OPTIONS;
                            selection_box_position.y = WIN_MENU_BOX_Y_LOW;
                        }
                        // Play scroll sound.
                        sound_manager->MenuScrollUp();
                        break;
                    case sf::Keyboard::Down:
                        if (selection < WIN_MENU_OPTIONS) {
                            selection += 1;
                            selection_box_position.y += WIN_MENU_BOX_SHIFT;
                        } else {
                            selection = 0;
                            selection_box_position.y = WIN_MENU_BOX_Y_UP;
                        }
                        // Play scroll sound.
                        sound_manager->MenuScrollDown();
                        break;
                    case sf::Keyboard::Return:
                        // Play selection sound.
                        sound_manager->MenuSelect();
                        sound_manager->StopWinMusic();
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