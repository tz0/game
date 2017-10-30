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
        struct Exit {
            float x;
            float y;
        };

        struct Entrance {
            float x;
            float y;
        };

        Level();
        ~Level();

        void Read(const unsigned &);
        void JsonTest();

        const Exit & GetExit(); 
        const Entrance & GetEntrance(); //

        const float & GetTotalFuel();
        const float & GetTotalOxygen(); //

    private:        
        Exit exit_; 
        Entrance entrance_;
        float total_fuel_;
        float total_oxygen_;
    };
}
#endif //GAME_LEVEL_H