#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <cassert>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>

#include "json11.hpp"

#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <type_traits>

#include <fstream>
#include <typeinfo>

namespace tjg {

    class Level {
    public:
        Level();
        ~Level();
        void Read(const unsigned &);
        void JsonTest();

    //private:
        float exit_x;
        float exit_y;
    };
}
#endif //GAME_LEVEL_H