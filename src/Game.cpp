#include "Game.h"

namespace tjg {

    // Constructor.
    Game::Game() :
            // Set the default search folder to "media"
            resource_manager("media"),
            view(resource_manager) {}

    // Teardown.
    Game::~Game() {
    }

    // Begin the game loop.
    void Game::Run() {
        view.Initialize();

        while (view.Running()) {
            if(!view.DidReachExit()) {
                view.Render();

                sf::Time elapsed = clock.restart();
                view.Update(elapsed);
            } else {
                view.RenderWinMessage();
            }
        }

    }
}