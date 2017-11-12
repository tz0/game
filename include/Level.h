#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <iostream>
#include <fstream>

#include "Systems/DialogueSystem.h"

#include "json11.hpp"

namespace tjg {

    class Level {
    public:        
        struct CameraCenter {
            float x, y;           
        };

        struct CameraSize {
            float x, y;            
        };

        struct Exit {
            float x, y;
        };

        struct Entrance {
            float x, y;
        };

        struct ShockBox {
            float x, y;

            inline ShockBox(float x, float y) :
                    x(x),
                    y(y) {}
        };

        struct Fan {
            float origin_x, origin_y, endpoint_x, endpoint_y, width, origin_strength, endpoint_strength;

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
            bool lethal;

            inline Wall(float origin_x, float origin_y, float endpoint_x, float endpoint_y, float radius, bool lethal) :
                origin_x(origin_x),
                origin_y(origin_y),
                endpoint_x(endpoint_x),
                endpoint_y(endpoint_y),
                radius(radius),
                lethal(lethal){}
        };

        struct StaticDecoration {
            std::string texture;
            sf::IntRect texture_rect;
            sf::Vector2f position;
            sf::Vector2f scale;
            float rotation;

            inline StaticDecoration(std::string texture, sf::IntRect texture_rect, sf::Vector2f position, sf::Vector2f scale, float rotation) :
                texture(std::move(texture)),
                texture_rect(texture_rect),
                position(position),
                scale(scale),
                rotation(rotation){}
        };

        // Constructor initiate the level class with default entities information without any fans
        Level();
        ~Level();

        /**
        * Utilize json11.hpp (from Dropbox, Inc) to parse a level file at ..//data//level<level>.json.
        * Update class member to store the latest level information.
        * Set debug to true if want to enable json file debug
        */
        void Read(const unsigned & level, const bool & debug);

        // Accessors
        const CameraCenter & GetCameraCenter();
        const CameraSize & GetCameraSize();
        const Exit & GetExit(); 
        const Entrance & GetEntrance(); 
        const float & GetFuel();
        const float & GetOxygen(); 
        const std::vector<Level::Fan> & GetFans();
        const std::vector<Level::Wall> & GetWalls();
        const std::vector<Dialogue> & GetDialogues();
        const std::vector<Level::StaticDecoration> & GetStaticDecorations();
        const std::vector<Level::ShockBox> & GetShockBoxes();

    private:        
        CameraCenter camera_center_;
        CameraSize camera_size_;
        Exit exit_; 
        Entrance entrance_;
        float fuel_;
        float oxygen_;        
        std::vector<Fan> fans_;
        std::vector<Wall> walls_;
        std::vector<Dialogue> dialogues_;
        std::vector<StaticDecoration> static_decorations_;
        std::vector<ShockBox> shock_boxes_;
        
        /**
        * Print parsing result from a target level for level file debugging.
        *
        */
        void JsonTest(const std::string & level_address);
    };
}
#endif //GAME_LEVEL_H