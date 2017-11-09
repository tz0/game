#include "Views/MainMenuView.h"

namespace tjg {
    MainMenuView::MainMenuView(ResourceManager &resource_manager, sf::RenderWindow &window) :
            View(window,resource_manager) {}


    void MainMenuView::Initialize() {
        selection = 0;
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        // temp Set font for win message
        message.setFont(*avenir_bold);
        // Create a win message.
        message.setStyle(sf::Text::Bold);
        message.setCharacterSize(24);
        message.setString("MAIN MENU\n\nSelect Levels\nExit Game");
        // Center the win message on the screen.
        sf::FloatRect textRect = message.getLocalBounds();
        message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);

        selection_box_position = sf::Vector2f(540, 360);
        selection_box.setSize(sf::Vector2f(200,29));
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
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(message);
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
                            selection_box_position.y -= 29;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (selection < options.size() - 1) {
                            selection += 1;
                            selection_box_position.y += 29;
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