#include "Game.h"

namespace tjg {

    // Constructor.
    Game::Game() :
            resource_manager("media"),
            view(resource_manager) {}

    // Teardown.
    Game::~Game() {
    }

    // Begin the game loop.
    void Game::Run() {
        view.Initialize();

        while (view.Running()) {
            view.Render();

            sf::Time elapsed = clock.restart();
            view.Update(elapsed);
        }

    }
}