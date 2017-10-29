#ifndef GAME_LEVELREADER_H
#define GAME_LEVELREADER_H

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

    class LevelReader {

    private:
        std::string level_root = std::string("");

    public:
        LevelReader(const std::string &level_root = "");
        ~LevelReader();

        void JsonTest();
    };





}
#endif // !GAME_LEVELREADER_H
