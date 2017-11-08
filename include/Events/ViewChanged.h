
#ifndef GAME_VIEWCHANGED_H
#define GAME_VIEWCHANGED_H


#include "Constants.h"
#include "Event.h"

namespace tjg {
    class ViewChanged : public Event {
    private:
        ViewSwitch view_switch;

    public:
        explicit ViewChanged(ViewSwitch view_switch) : view_switch(view_switch) {};
        ViewSwitch GetViewSwitch() {
            return view_switch;
        }
    };
}


#endif //GAME_VIEWCHANGED_H
