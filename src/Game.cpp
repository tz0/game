#include "Game.h"

namespace tjg {

    // Constructor.
    Game::Game() :
            // Set the default search folder to "media"
            resource_manager("media"),
            logic_center(resource_manager, event_manager),
            view_manager(resource_manager, logic_center, event_manager){}

    // Teardown.
    Game::~Game() = default;

    // Begin the game loop.
    void Game::Run() {
        view_manager.Initialize();
        view_manager.SwitchView(ViewSwitch{State::MAIN_MENU, 0});

        while (view_manager.Running()) {
            // Update the logic and handle input 60 times per second
            auto elapsed = update_clock.getElapsedTime();
            if (elapsed.asSeconds() > 1.f/60.f) {
                view_manager.Update(elapsed);
                update_clock.restart();
            }
            //Render current state
            view_manager.Render();
        }

    }
}