
#ifndef GAME_STATEMANAGER_H
#define GAME_STATEMANAGER_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

#include <SFML/Graphics.hpp>
#include "Views/LevelMenuView.h"
#include "Views/MainMenuView.h"
#include "Views/PlayerView.h"
#include "Views/PauseMenuView.h"
#include "View.h"
#include "LogicCenter.h"
#include "Constants.h"

namespace tjg {

    class ViewManager {
    private:
        State state;
        ResourceManager &resource_manager;
        LogicCenter &logic_center;
        MainMenuView main_menu_view;
        LevelMenuView level_menu_view;
        PlayerView player_view;
        PauseMenuView pause_menu_view;
        sf::RenderWindow window;

        bool running = true;

    public:
        explicit ViewManager(ResourceManager &resource_manager, LogicCenter &logic_center);
        void Initialize();
        bool Running();
        void Update(sf::Time elapsed);
        void Render();
        void SwitchView(ViewSwitch view_switch);
        void SwitchToMainMenuView();
        void SwitchToLevelMenuView();
        void SwitchToPauseMenuView(State state);
        void SwitchToPlayerView();
        void ResumePlayerView();
        void HandleWindowEvents(View &current_view);
    };
}
#endif //GAME_STATEMANAGER_H
