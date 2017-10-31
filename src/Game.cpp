#include "Game.h"

namespace tjg {

    // Constructor.
    Game::Game() :
            // Set the default search folder to "media"
            resource_manager("media"),
            logic_center(resource_manager),
            player_view(resource_manager, logic_center) {}

    // Teardown.
    Game::~Game() = default;

    // Begin the game loop.
    void Game::Run() {
        unsigned level_number = 1; // Change 1 to x if you want to test levelx.json
        level.Read(level_number, true); // Read level file. Set debug to false to disable json file debug. 
        logic_center.Initialize(level);
        player_view.Initialize(level);

        while (player_view.Running()) {

            // Update the logic and handle input 60 times per second
            auto elapsed = update_clock.getElapsedTime();
            if (elapsed.asSeconds() > 1.f/60.f) {
                logic_center.Update(elapsed);
                player_view.Update(elapsed);
                update_clock.restart();
            }

            if(!logic_center.DidReachExit()) {
                player_view.Render();
            } else {
                player_view.RenderWinMessage();
            }
        }

    }
}