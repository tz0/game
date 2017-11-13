#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u
#define STATUSBAR_HEIGHT 72

#define MAIN_MENU_BOX_X 803u
#define MAIN_MENU_BOX_Y_UP 503u
#define MAIN_MENU_BOX_Y_LOW 563u
#define MAIN_MENU_BOX_SHIFT 60u

#define LEVEL_MENU_OPTIONS 12u  //options.size()-1

#define PAUSE_MENU_OPTIONS 3u  //options.size()-1
#define PAUSE_MENU_BOX_X 62u
#define PAUSE_MENU_BOX_Y_UP 214u
#define PAUSE_MENU_BOX_Y_LOW 394u
#define PAUSE_MENU_BOX_SHIFT 60u

#define WIN_MENU_OPTIONS 2u  //options.size()-1
#define WIN_MENU_BOX_X 879u
#define WIN_MENU_BOX_Y_UP 214u
#define WIN_MENU_BOX_Y_LOW 334u
#define WIN_MENU_BOX_SHIFT 60u

#define FAIL_MENU_OPTIONS 1u  //options.size()-1
#define FAIL_MENU_BOX_X 62u
#define FAIL_MENU_BOX_Y_UP 455u
#define FAIL_MENU_BOX_Y_LOW 515u
#define FAIL_MENU_BOX_SHIFT 60u

namespace tjg {
    enum class State {CONTINUE, MAIN_MENU, LEVEL_MENU, PLAYING, RESUME, PAUSED, WON, FAILED, EXIT};
    struct ViewSwitch {
        State state;
        unsigned int level_number;
    };
}

#endif //GAME_CONSTANTS_H
