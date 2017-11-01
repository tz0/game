#include "Views/MenuButton.h"

namespace tjg{
    MenuButton::MenuButton(std::string &text, State state, unsigned int level_number, bool enabled) {
        this -> text = text;
        this -> view_switch = ViewSwitch {.state = state, .level_number = level_number};
        this -> enabled = enabled;
    }

    ViewSwitch MenuButton::GetViewSwitch() {
        return view_switch;
    }

    bool MenuButton::isEnabled() {
        return enabled;
    }

    MenuButton* MenuButton::GetPrevious() {
        return previous;
    }

    MenuButton* MenuButton::GetNext() {
        return next;
    }

    void MenuButton::SetPrevious(MenuButton *menu_button) {
        previous = menu_button;
    }

    void MenuButton::SetNext(MenuButton *menu_button) {
        next = menu_button;
    }
}