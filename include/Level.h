#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <iostream>
#include <fstream>

#include "json11.hpp"

namespace tjg {

    class Level {
    public:        
        struct Exit {
            float x, y;
        };

        struct Entrance {
            float x, y;
        };

        struct Fan {
            float width, origin_x, origin_y, origin_strength, endpoint_x, endpoint_y, endpoint_strength;

            inline Fan(float origin_x, float origin_y, float endpoint_x, float endpoint_y, float width, float origin_strength, float endpoint_strength) :
                origin_x(origin_x), 
                origin_y(origin_y), 
                endpoint_x(endpoint_x), 
                endpoint_y(endpoint_y), 
                width(width), 
                origin_strength(origin_strength), 
                endpoint_strength(endpoint_strength) {}
        };

        struct Wall {
            float origin_x, origin_y, endpoint_x, endpoint_y, radius;

            inline Wall(float origin_x, float origin_y, float endpoint_x, float endpoint_y, float radius) :
                origin_x(origin_x),
                origin_y(origin_y),
                endpoint_x(endpoint_x),
                endpoint_y(endpoint_y),
                radius(radius){}
        };

        // Constructor innitiate the level class with default entities information without any fans
        Level();
        ~Level();

        /**
        * Utilize json11.hpp (from Dropbox, Inc) to parse a level file at ..//data//level<level>.json.
        * Update class member to store the latest level information.
        * Set debug to ture if want to enable json file debug
        */
        void Read(const unsigned & level, const bool & debug);

        // Accessors
        const Exit & GetExit(); 
        const Entrance & GetEntrance(); 
        const float & GetTotalFuel();
        const float & GetTotalOxygen(); 
        const std::vector<Level::Fan> & GetFans();
        const std::vector<Level::Wall> & GetWalls();

    private:        
        Exit exit_; 
        Entrance entrance_;
        float total_fuel_;
        float total_oxygen_;
        std::vector<Fan> fans_;
        std::vector<Wall> walls_;
        std::vector<std::string> dialogues_;
        
        /**
        * Print parsing result from a target level for level file debugging.
        *
        */
        void JsonTest(const std::string & level_address);
    };
}
#endif //GAME_LEVEL_H