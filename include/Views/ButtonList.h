#ifndef GAME_BUTTONLIST_H
#define GAME_BUTTONLIST_H

#include "Views/MenuButton.h"

namespace tjg{
    class ButtonList{
    private:
        MenuButton *head = nullptr;
        MenuButton *tail = nullptr;
        MenuButton *curr_selected = nullptr;
    public:
        ButtonList();
        void Append(std::string &text, State state, unsigned int level_number, bool enabled);
        void SelectPrevious();
        void SelectNext();
        MenuButton *GetCurrentSelected();
    };
}

#endif //GAME_BUTTONLIST_H
