
#ifndef GAME_STATEMANAGER_H
#define GAME_STATEMANAGER_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

#include <SFML/Graphics.hpp>
#include "Views/PlayerView.h"
#include "Views/PauseMenuView.h"
#include "LogicCenter.h"

namespace tjg {
    enum class State {MAIN_MENU, LEVEL_MENU, PAUSE_MENU, PLAYING};

    class StateManager {
    private:
        State state;
        ResourceManager &resource_manager;
        LogicCenter &logic_center;
        PlayerView player_view;
        PauseMenuView pause_menu_view;
        sf::RenderWindow window;

        sf::Clock update_clock;
        bool running = true;

    public:
        explicit StateManager(ResourceManager &resource_manager, LogicCenter &logic_center);
        void Initialize();
        bool Running();
        void Update();
        void Render();
        void SwitchToMainMenuView();
        void SwitchToLevelMenuView();
        void SwitchToPauseMenuView();
        void SwitchToPlayerView();
        void HandleWindowEvents();
    };
}
#endif //GAME_STATEMANAGER_H
