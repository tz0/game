#ifndef GAME_STATEMANAGER_H
#define GAME_STATEMANAGER_H

#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "Systems/SoundManager.h"
#include "Views/LevelMenuView.h"
#include "Views/MainMenuView.h"
#include "Views/LevelView.h"
#include "Views/PauseMenuView.h"
#include "Views/WinMenuView.h"
#include "Views/FailMenuView.h"
#include "View.h"
#include "LogicCenter.h"
#include "Constants.h"

namespace tjg {

    class ViewManager {
    private:
        LogicCenter &logic_center;
        EventManager &event_manager;
        SoundManager sound_manager;
        State state;
        sf::RenderWindow window;
        MainMenuView main_menu_view;
        LevelMenuView level_menu_view;
        LevelView level_view;
        PauseMenuView pause_menu_view;
        WinMenuView win_menu_view;
        FailMenuView fail_menu_view;
        unsigned int current_level;
        unsigned int unlocked;

        bool running = true;

        void SwitchToMainMenuView();
        void SwitchToLevelMenuView(unsigned int unlocked);
        void SwitchToPauseMenuView();
        void SwitchToWinMenuView();
        void SwitchToFailMenuView();
        void SwitchToPlayerView(unsigned int level_number);
        void ResumePlayerView();
        unsigned int ReadUnlockedLevel();
        void WriteUnlockedLevel(unsigned int level_number);

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
