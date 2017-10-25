
#ifndef GAME_STATEMANAGER_H
#define GAME_STATEMANAGER_H

#include <SFML/Graphics.hpp>

namespace tjg {
    enum class State {MAIN_MENU, LEVEL_MENU, PAUSE_MENU, PLAYING};

    class StateManager {
    private:
        State state;
        sf::RenderWindow &window;
    public:
        explicit StateManager(sf::RenderWindow &window);
        void SetState(State state);
        void Draw();
        void DrawMainMenu();
        void DrawLevelMenu();
        void DrawPauseMenu();
        void DrawPlaying();
    };
}
#endif //GAME_STATEMANAGER_H
