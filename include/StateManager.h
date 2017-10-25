
#ifndef GAME_STATEMANAGER_H
#define GAME_STATEMANAGER_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

#include <SFML/Graphics.hpp>

namespace tjg {
    enum class State {MAIN_MENU, LEVEL_MENU, PAUSE_MENU, PLAYING};

    class StateManager {
    private:
        State state;
        sf::RenderWindow &window;
        bool running = true;

        sf::Text win_message;
    public:
        explicit StateManager(sf::RenderWindow &window);
        void Initialize(sf::Font &font);
        void SetState(State state);
        void Draw();
        void DrawMainMenu();
        void DrawLevelMenu();
        void DrawPauseMenu();
        void DrawPlaying();
    };
}
#endif //GAME_STATEMANAGER_H
