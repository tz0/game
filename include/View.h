
#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "LogicCenter.h"

namespace tjg {
    class View {

    protected:
        LogicCenter &logic_center;

    public:
        View(LogicCenter &logic_center) : logic_center(logic_center) {};

        virtual void Initialize() = 0;

        /**
         * @return whether the view is still running
         */
        virtual bool Running() = 0;
    };
}
#endif //GAME_VIEW_H
