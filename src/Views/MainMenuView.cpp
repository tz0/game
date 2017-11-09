#include "Views/MainMenuView.h"

namespace tjg {
    MainMenuView::MainMenuView(ResourceManager &resource_manager, sf::RenderWindow &window, LogicCenter &logic_center) :
            View(window,resource_manager),
            logic_center(logic_center)
    {
        window.setVerticalSyncEnabled(true);
    }


    void MainMenuView::Initialize() {
        selection = 0;
        auto background_texture = resource_manager.LoadTexture("interstellar.png");
        background_sprite.setTexture(*background_texture);
        background_sprite.setTextureRect(sf::IntRect(0, 0, 1280, 720));

        selection_box_position = sf::Vector2f(803, 503);
        selection_box.setSize(sf::Vector2f(363,43));
        selection_box.setPosition(selection_box_position);
        selection_box.setFillColor(sf::Color::Transparent);
        selection_box.setOutlineColor(sf::Color(255, 255, 255, 255));
        selection_box.setOutlineThickness(2.0f);
    }


    //TODO: Implement or remove
    void MainMenuView::Update() {
        selection_box.setPosition(selection_box_position);
    }


    void MainMenuView::Render() {
        window.clear(sf::Color(50, 50, 50, 255));
        window.setView(window.getDefaultView());
        window.draw(background_sprite);
        window.draw(selection_box);
        window.display();
    }

    ViewSwitch MainMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 0) {
                            selection -= 1;
                            selection_box_position.y -= 60;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (selection < options.size() - 1) {
                            selection += 1;
                            selection_box_position.y += 60;
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