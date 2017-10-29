#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <LevelReader.h>

namespace tjg {

    class Level {
    public:
        Level();
        ~Level();        
    //private:
        float exit_x;
        float exit_y;
    };
}
#endif //GAME_LEVEL_H