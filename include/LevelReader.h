#ifndef GAME_LEVELREADER_H
#define GAME_LEVELREADER_H

#include <iostream>
#include <string>
#include "gason.h"

namespace tjg {

    class LevelReader {

    private:
        std::string level_root = std::string("");

    public:
        LevelReader(const std::string &level_root = "");
        ~LevelReader();
    };





}
#endif // !GAME_LEVELREADER_H
