#include "Game.h"

namespace tjg {

    // Constructor.
    Game::Game() :
            // Set the default search folder to "media"
            resource_manager("media"),
            logic_center(resource_manager),
//            view(resource_manager, logic_center),
            state_manager(resource_manager, logic_center){}

    // Teardown.
    Game::~Game() = default;

    // Begin the game loop.
    void Game::Run() {
//        logic_center.Initialize();
//        view.Initialize();
        state_manager.Initialize();
        //state_manager.SwitchToMenuView();
        state_manager.SwitchToPlayerView();

        while (state_manager.Running()) {
            state_manager.Update();
            // Update the logic and handle input 60 times per second
//            auto elapsed = update_clock.getElapsedTime();
//            if (elapsed.asSeconds() > 1.f/60.f) {
//                logic_center.Update(elapsed);
//                view.Update();
//                update_clock.restart();
//            }
            state_manager.Render();
            if(logic_center.DidReachExit()) {
                state_manager.SwitchToPauseMenuView();
                logic_center.Reset();
            }
        }

    }
}