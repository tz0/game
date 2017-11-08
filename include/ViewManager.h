#ifndef GAME_STATEMANAGER_H
#define GAME_STATEMANAGER_H

#include <SFML/Graphics.hpp>
#include "Views/LevelMenuView.h"
#include "Views/MainMenuView.h"
#include "Views/LevelView.h"
#include "Views/PauseMenuView.h"
#include "View.h"
#include "LogicCenter.h"
#include "Constants.h"

namespace tjg {

    class ViewManager {
    private:
        LogicCenter &logic_center;
        EventManager &event_manager;
        State state;
        sf::RenderWindow window;
        MainMenuView main_menu_view;
        LevelMenuView level_menu_view;
        LevelView player_view;
        PauseMenuView pause_menu_view;
        unsigned int current_level;

        bool running = true;

        void SwitchToMainMenuView();
        void SwitchToLevelMenuView();
        void SwitchToPauseMenuView(ViewSwitch view_switch);
        void SwitchToPlayerView(unsigned int level_number);
        void ResumePlayerView();

    public:
        explicit ViewManager(ResourceManager &resource_manager, LogicCenter &logic_center, EventManager &event_manager);
        void Initialize();
        bool Running();
        void Update(sf::Time elapsed);
        void Render();
        void SwitchView(ViewSwitch view_switch);
        void HandleWindowEvents(View &current_view);
    };
}
#endif //GAME_STATEMANAGER_H
