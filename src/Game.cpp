#include "Game.h"

namespace tjg {

    // Constructor.
    Game::Game() :
            // Set the default search folder to "media"
            resource_manager("media"),
            logic_center(resource_manager),
            state_manager(resource_manager, logic_center){}

    // Teardown.
    Game::~Game() = default;

    // Begin the game loop.
    void Game::Run() {
        state_manager.Initialize();
        state_manager.SwitchToMainMenuView();
        state_manager.SwitchToLevelMenuView();
        state_manager.SwitchToPlayerView();

        while (state_manager.Running()) {
            // Update the logic and handle input 60 times per second
            auto elapsed = update_clock.getElapsedTime();
            if (elapsed.asSeconds() > 1.f/60.f) {
                state_manager.Update(elapsed);
                update_clock.restart();
            }
            //Render current state
            state_manager.Render();
            //Switch to menu if reached exit
            if(logic_center.DidReachExit()) {
                state_manager.SwitchToPauseMenuView(State::WON);
                logic_center.Reset();
            }
        }

    }
}