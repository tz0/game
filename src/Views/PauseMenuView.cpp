#include "Views/PauseMenuView.h"

namespace tjg{
    PauseMenuView::PauseMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, std::shared_ptr<SoundManager> &sound_manager) :
            View(window, resource_manager, sound_manager) {}


    void PauseMenuView::Initialize(const unsigned int level_number) {
        current_level = level_number;
        selection = 0;
        auto background_texture = resource_manager.LoadTexture("menu-pause.jpg");
        background_sprite.setTexture(*background_texture);
        options = {ViewSwitch {State::RESUME, 0}, ViewSwitch {State::LEVEL_MENU, 0}, ViewSwitch {State::PLAYING, 0}, ViewSwitch {State::MAIN_MENU, 0}};

        selection_box_position = sf::Vector2f(PAUSE_MENU_BOX_X, PAUSE_MENU_BOX_Y_UP);
        selection_box.setSize(sf::Vector2f(363,43));
        selection_box.setPosition(selection_box_position);
        selection_box.setFillColor(sf::Color::Transparent);
        selection_box.setOutlineColor(sf::Color(255, 255, 255, 255));
        selection_box.setOutlineThickness(2.0f);

        // Pause level music and spatial sounds.
        sound_manager->StopLevelSounds();
        sound_manager->PauseLevelMusic();
        sound_manager->PauseSpatialSounds();

        // Play music.
        sound_manager->StartMenuMusic();
    }

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
                        // Play scroll sound.
                        sound_manager->MenuScrollUp();
                        break;
                    case sf::Keyboard::Down:
                        if (selection < PAUSE_MENU_OPTIONS) {
                            selection += 1;
                            selection_box_position.y += PAUSE_MENU_BOX_SHIFT;
                        } else {
                            selection = 0;
                            selection_box_position.y = PAUSE_MENU_BOX_Y_UP;
                        }
                        // Play scroll sound.
                        sound_manager->MenuScrollDown();
                        break;
                    case sf::Keyboard::Return:
                        // Play selection sound.
                        sound_manager->MenuSelect();
                        if (selection == 0) {
                            // If the player chooses to continue, stop the menu music and continue the level music and sounds.
                            sound_manager->StopMenuMusic();
                            sound_manager->StartLevelMusic();
                            sound_manager->StartSpatialSounds();
                        }
                        else if (selection == 2) {
                            // If the player chooses to restart, stop the menu music and restart the level music and sounds.
                            sound_manager->StopMenuMusic();
                            sound_manager->StopLevelMusic();
                            sound_manager->StopSpatialSounds();
                        }
                        else {
                            // If the player goes to level select or the main menu, completely stop the level music and sounds.
                            sound_manager->StopLevelMusic();
                            sound_manager->StopSpatialSounds();
                            sound_manager->ClearSpatialSounds();
                        }
                        return options[selection];
                    case sf::Keyboard::Escape:
                        sound_manager->StopMenuMusic();
                        sound_manager->StartLevelMusic();
                        sound_manager->StartSpatialSounds();
                        return options[0];
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