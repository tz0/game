#include "Views/ButtonList.h"

namespace tjg {
    ButtonList::ButtonList() = default;

    void ButtonList::Append(std::string &text, State state, unsigned int level_number, bool enabled) {
        auto *new_button = new MenuButton(text, state, level_number, enabled);
        if (head == nullptr) {
            head = new_button;
            tail = new_button;
        } else {
            new_button -> SetPrevious(tail);
            tail -> SetNext(new_button);
            tail = new_button;
        }
    }

    void ButtonList::SelectPrevious() {
        curr_selected = curr_selected -> GetPrevious();
    }

    void ButtonList::SelectNext() {
        curr_selected = curr_selected -> GetNext();
    }

    MenuButton *ButtonList::GetCurrentSelected(){
        return curr_selected;
    }
}