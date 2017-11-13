#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u
#define STATUSBAR_HEIGHT 72

#define MAIN_MENU_BOX_X 803u
#define MAIN_MENU_BOX_Y_UP 503u
#define MAIN_MENU_BOX_Y_LOW 563u
#define MAIN_MENU_BOX_SHIFT 60u

#define LEVEL_MENU_OPTIONS 3u  //options.size()-1
#define LEVEL_MENU_BOX_X_LEFT 530u
#define LEVEL_MENU_BOX_X_RIGHT 530u
#define LEVEL_MENU_BOX_Y_UP 346u
#define LEVEL_MENU_BOX_Y_LOW 404u
#define LEVEL_MENU_BOX_SHIFT 29u

#define PAUSE_MENU_BOX_X 350u
#define PAUSE_MENU_BOX_Y_UP 361u
#define PAUSE_MENU_BOX_Y_LOW 361u
#define PAUSE_MENU_BOX_SHIFT 29u

namespace tjg {
    enum class State {CONTINUE, MAIN_MENU, LEVEL_MENU, PLAYING, RESUME, PAUSED, WON, FAILED, EXIT};
    struct ViewSwitch {
        State state;
        unsigned int level_number;
    };
}

#endif //GAME_CONSTANTS_H
