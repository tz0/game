#include "Views/PauseMenuView.h"

namespace tjg{
    PauseMenuView::PauseMenuView(ResourceManager &resource_manager, sf::RenderWindow &window) :
            View(window,resource_manager) {}


    void PauseMenuView::Initialize() {
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        // temp Set font for win message
        message.setFont(*avenir_bold);
        // Create a win message.
        message.setStyle(sf::Text::Bold);
        message.setCharacterSize(24);
        message.setString("You Reached the Exit!");
        // Center the win message on the screen.
        sf::FloatRect textRect = message.getLocalBounds();
        message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);
    }

    //Handle keyboard control of the menu
    void PauseMenuView::Update() {
    }


    void PauseMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(message);
        window.display();
    }

    void PauseMenuView::HandleWindowEvents(sf::Event event) {

    }

}