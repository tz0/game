#include "Views/LevelMenuView.h"

namespace tjg {
    LevelMenuView::LevelMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, SoundManager &sound_manager) :
            View(window, resource_manager, sound_manager) {}


    void LevelMenuView::Initialize(const unsigned int unlocked) {
        //initialize menu
        unlocked_ = unlocked;
        selection = 1;

        //load background
        auto background_texture = resource_manager.LoadTexture("menu-level.jpg");
        background_sprite.setTexture(*background_texture);
        background_sprite.setTextureRect(sf::IntRect(0, 0, 1280, 720));

        auto animation_texture = resource_manager.LoadTexture("animation-sprite.jpg");
        animation_sprite.setTexture(*animation_texture);
        //load fonts
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");

        //initialize level numbers
        for (unsigned int i = 0; i < LEVEL_MENU_OPTIONS; i++) {
            menu[i] -> setFont(*avenir_bold);
            menu[i] -> setCharacterSize(30);
            menu[i] -> setFillColor(sf::Color(255, 255, 255, 128));
            menu[i] -> setString(std::to_string(i+1));
        }

        //make unlocked levels bright
        for (unsigned int i = 0; i < unlocked_; i++) {
            menu[i] -> setFillColor(sf::Color(255, 255, 255, 255));
            menu[i] -> setOutlineColor(sf::Color(0, 0, 0, 255));
            menu[i] -> setOutlineThickness(2);
        }

        //make current selection big
        menu[selection - 1] -> setCharacterSize(72);

        //set level number positions
        level_1.setPosition(1041, 111);
        level_2.setPosition(1124, 259);
        level_3.setPosition(1136, 414);
        level_4.setPosition(1052, 569);
        level_5.setPosition(908, 635);
        level_6.setPosition(746, 614);
        level_7.setPosition(644, 538);
        level_8.setPosition(582, 409);
        level_9.setPosition(594, 278);
        level_10.setPosition(630, 145);
        level_11.setPosition(730, 55);
        level_12.setPosition(890, 42);
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

    void LevelMenuView::RenderAnimation() {
        sf::Clock clock;
        int i = 0;
        while (i < 10) {
            if (clock.getElapsedTime().asSeconds() > 0.03f) {
                animation_sprite.setTextureRect(sf::IntRect(0, 6480 - i * 720, 1280, 7200 - i * 720));
                window.clear(sf::Color(50, 50, 50, 255));
                window.setView(window.getDefaultView());
                window.draw(animation_sprite);
                window.display();

                clock.restart();
                i++;
            }
        }
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
                            selection = unlocked_;
                            menu[selection - 1] -> setCharacterSize(72);
                        }
                        // Play scroll sound.
                        sound_manager.MenuScrollUp();
                        break;
                    case sf::Keyboard::Down:
                        if (selection < unlocked_) {
                            menu[selection - 1] -> setCharacterSize(30);
                            selection += 1;
                            menu[selection - 1] -> setCharacterSize(72);
                        } else {
                            menu[selection -1] -> setCharacterSize(30);
                            selection = 1;
                            menu[selection - 1] -> setCharacterSize(72);
                        }
                        // Play scroll sound.
                        sound_manager.MenuScrollDown();
                        break;
                    case sf::Keyboard::Return:
                        // Play selection sound.
                        sound_manager.MenuSelect();
                        return ViewSwitch {State::PLAYING, selection};
                    case sf::Keyboard::Escape:
                        sound_manager.MenuBack();
                        RenderAnimation();
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
