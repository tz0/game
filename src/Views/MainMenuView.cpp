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
        message.setString("MAIN MENU\n\nENTER/ Select Levels\nESC/ Exit Game");
        // Center the win message on the screen.
        sf::FloatRect textRect = message.getLocalBounds();
        message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);
    }


    //TODO: Implement or remove
    void MainMenuView::Update() {
        message.setString("Selected: " + std::to_string(selection) + "\nMAIN MENU\n\nENTER/ Select Levels\nESC/ Exit Game");
    }


    void MainMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(message);
        window.display();
    }

    ViewSwitch MainMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 0) selection -= 1;
                        break;
                    case sf::Keyboard::Down:
                        if (selection < options.size() - 1) selection += 1;
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