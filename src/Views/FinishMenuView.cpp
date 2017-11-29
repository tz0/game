#include "Views/FinishMenuView.h"

namespace tjg{
    FinishMenuView::FinishMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, std::shared_ptr<SoundManager> &sound_manager) :
            View(window, resource_manager, sound_manager) {}


    void FinishMenuView::Initialize() {
        selection = 0;
        //load fonts
        auto monaco = resource_manager.LoadFont("monaco.ttf");

        auto background_texture = resource_manager.LoadTexture("menu-finish.jpg");
        background_sprite.setTexture(*background_texture);
        options = {ViewSwitch {State::MAIN_MENU, 0}};

        selection_box_position = sf::Vector2f(WIN_MENU_BOX_X, WIN_MENU_BOX_Y_UP);
        selection_box.setSize(sf::Vector2f(363,43));
        selection_box.setPosition(selection_box_position);
        selection_box.setFillColor(sf::Color::Transparent);
        selection_box.setOutlineColor(sf::Color(255, 255, 255, 255));
        selection_box.setOutlineThickness(2.0f);

        // Stop level sounds.
        sound_manager->StopLevelSounds();
        sound_manager->StopSpatialSounds();
        sound_manager->ClearSpatialSounds();
        sound_manager->StopLevelMusic();

        // Start music.
        sound_manager->StartWinMusic();
    }

    void FinishMenuView::Update() {
        selection_box.setPosition(selection_box_position);
    }

    void FinishMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(background_sprite);
        window.draw(selection_box);
        window.display();
    }

    ViewSwitch FinishMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        // Play scroll sound.
                        sound_manager->MenuScrollUp();
                        break;
                    case sf::Keyboard::Down:
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