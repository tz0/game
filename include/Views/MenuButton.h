#ifndef GAME_MENUBUTTON_H
#define GAME_MENUBUTTON_H

#include <string>
#include <Constants.h>

namespace tjg {
    class MenuButton {
    private:
        std::string text;
        ViewSwitch view_switch;
        bool enabled;
        MenuButton *previous = nullptr;
        MenuButton *next = nullptr;
    public:
        MenuButton(std::string &text, State state, unsigned int level_number, bool enabled);
        ViewSwitch GetViewSwitch();
        bool isEnabled();
        MenuButton *GetPrevious();
        MenuButton *GetNext();
        void SetPrevious(MenuButton *menu_button);
        void SetNext(MenuButton *menu_button);
    };
}
#endif //GAME_MENUBUTTON_H
