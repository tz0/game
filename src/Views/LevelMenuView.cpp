#include "Views/LevelMenuView.h"

namespace tjg {
    LevelMenuView::LevelMenuView(ResourceManager &resource_manager, sf::RenderWindow &window) :
            View(window,resource_manager) {}


    void LevelMenuView::Initialize() {
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        // temp Set font for win message
        message.setFont(*avenir_bold);
        // Create a win message.
        message.setStyle(sf::Text::Bold);
        message.setCharacterSize(24);
        message.setString("LEVEL MENU\nPress ENTER/RETURN to start game");
        // Center the win message on the screen.
        sf::FloatRect textRect = message.getLocalBounds();
        message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);
    }

    //Handle keyboard control of the menu
    void LevelMenuView::Update() {

    }


    void LevelMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(message);
        window.display();
    }

    ViewSwitch LevelMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    // Toggle FPS counter on F1.
                    case sf::Keyboard::Return: {
                        return ViewSwitch::PLAYING;
                    }
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
        return ViewSwitch::CONTINUE;
    }
}