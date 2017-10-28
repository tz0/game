#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

namespace tjg {
    enum class State {MAIN_MENU, LEVEL_MENU, PLAYING, PAUSED, WON, FAILED};
    enum class ViewSwitch {CONTINUE, MAIN_MENU, LEVEL_MENU, PLAYING, RESUME, PAUSED, WON, FAILED, EXIT};
}

#endif //GAME_CONSTANTS_H
