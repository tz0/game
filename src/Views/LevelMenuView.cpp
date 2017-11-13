#include "Views/LevelMenuView.h"

namespace tjg {
    LevelMenuView::LevelMenuView(ResourceManager &resource_manager, sf::RenderWindow &window) :
            View(window,resource_manager) {}


    void LevelMenuView::Initialize() {
        selection = 1;
        auto background_texture = resource_manager.LoadTexture("level-menu.png");
        background_sprite.setTexture(*background_texture);
        background_sprite.setTextureRect(sf::IntRect(0, 0, 1280, 720));

        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        auto copper_plate = resource_manager.LoadFont("Copperplate-Gothic-Light.ttf");

        for (unsigned int i = 0; i < LEVEL_MENU_OPTIONS; i++) {
            menu[i] -> setFont(*avenir_bold);
            menu[i] -> setCharacterSize(30);
            menu[i] -> setFillColor(sf::Color(50, 50, 50, 128));
            menu[i] -> setString(std::to_string(i+1));
        }

        for (unsigned int i = 0; i < unlocked; i++) {
            menu[i] -> setFillColor(sf::Color(50, 50, 50, 255));
        }

        menu[selection - 1] -> setCharacterSize(72);

        level_1.setPosition(1047, 129);
        level_2.setPosition(1141, 262);
        level_3.setPosition(1161, 420);
        level_4.setPosition(1055, 581);
        level_5.setPosition(907, 652);
        level_6.setPosition(773, 630);
        level_7.setPosition(640, 544);
        level_8.setPosition(590, 415);
        level_9.setPosition(597, 278);
        level_10.setPosition(655, 167);
        level_11.setPosition(765, 67);
        level_12.setPosition(909, 67);
    }


    //TODO: Implement or remove
    void LevelMenuView::Update() {

    }


    void LevelMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(background_sprite);
        for (auto level_text : menu) {
            window.draw(*level_text);
        }
        window.display();
    }

    ViewSwitch LevelMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 1) {
                            menu[selection - 1] -> setCharacterSize(30);
                            selection -= 1;
                            menu[selection - 1] -> setCharacterSize(72);
                        } else {
                            menu[selection - 1] -> setCharacterSize(30);
                            selection = unlocked;
                            menu[selection - 1] -> setCharacterSize(72);
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (selection < unlocked) {
                            menu[selection - 1] -> setCharacterSize(30);
                            selection += 1;
                            menu[selection - 1] -> setCharacterSize(72);
                        } else {
                            menu[selection -1] -> setCharacterSize(30);
                            selection = 1;
                            menu[selection - 1] -> setCharacterSize(72);
                        }
                        break;
                    case sf::Keyboard::Return:
                        return ViewSwitch {State::PLAYING, selection};
                    case sf::Keyboard::Escape:
                        return ViewSwitch {State::MAIN_MENU, 0};
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