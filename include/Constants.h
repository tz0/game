#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u
#define STATUSBAR_HEIGHT 72

namespace tjg {
    enum class State {CONTINUE, MAIN_MENU, LEVEL_MENU, PLAYING, RESUME, PAUSED, WON, FAILED, EXIT};
    struct ViewSwitch {
        State state;
        unsigned int level_number;
    };
}

#endif //GAME_CONSTANTS_H
