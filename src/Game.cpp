#include "Game.h"

namespace tjg {

    // Constructor.
    Game::Game() :
            // Set the default search folder to "media"
            resource_manager("media"),
            logic_center(resource_manager),
            view(resource_manager, logic_center) {}

    // Teardown.
    Game::~Game() = default;

    // Begin the game loop.
    void Game::Run() {
        logic_center.Initialize();
        view.Initialize();

        while (view.Running()) {

            // Update the logic and handle input 60 times per second
            auto elapsed = update_clock.getElapsedTime();
            if (elapsed.asSeconds() > 1.f/60.f) {
                logic_center.Update(elapsed);
                view.Update();
                update_clock.restart();
            }

            if(!logic_center.DidReachExit()) {
                view.Render();
            } else {
                view.RenderWinMessage();
            }
        }

    }
}