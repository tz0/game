#include "Game.h"

namespace tjg {

    // Constructor.
    Game::Game() :
            // Set the default search folder to "media"
            resource_manager("media"),
            logic_center(resource_manager),
            view_manager(resource_manager, logic_center){}

    // Teardown.
    Game::~Game() = default;

    // Begin the game loop.
    void Game::Run() {
        view_manager.Initialize();
        view_manager.SwitchToMainMenuView();

        while (view_manager.Running()) {
            // Update the logic and handle input 60 times per second
            auto elapsed = update_clock.getElapsedTime();
            if (elapsed.asSeconds() > 1.f/60.f) {
                view_manager.Update(elapsed);
                update_clock.restart();
            }
            //Render current state
            view_manager.Render();
            //Switch to menu if reached exit
//            if(logic_center.DidReachExit()) {
//                view_manager.SwitchToPauseMenuView(State::WON);
//                logic_center.Reset();
//            }
        }

    }
}