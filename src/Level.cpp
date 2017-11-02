#include "Level.h"

namespace tjg {
    Level::Level() : 
        camera_center_{ -500, 0 }, // initialization for struct member in C 
        camera_size_{ 2080, 1280 }, 
        exit_{ -1000, -200 }, 
        entrance_{ 0, 0 }, 
        fuel_(5), 
        oxygen_(45) {
    }

    Level::~Level() = default;

    void Level::JsonTest(const std::string & level_address) {        
        std::string err;
        std::ifstream in(level_address);
        std::string raw_levelfile((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        const auto parse_result = json11::Json::parse(raw_levelfile, err);

        std::cout << std::endl << "##### [level info] start #####" << std::endl;
        std::cout << "# [level]: " << parse_result["level"].dump() << std::endl;
        std::cout << "# [fuel]: " << parse_result["fuel"].dump() << std::endl;
        std::cout << "# [oxygen]: " << parse_result["oxygen"].dump() << std::endl;

        std::cout << '#' << std::endl << "##### [camera center]" << std::endl;
        std::cout << "# [x]: " << parse_result["camera center"]["x"].dump() << std::endl;
        std::cout << "# [y]: " << parse_result["camera center"]["y"].dump() << std::endl;

        std::cout << '#' << std::endl << "##### [camera size]" << std::endl;
        std::cout << "# [x]: " << parse_result["camera size"]["x"].dump() << std::endl;
        std::cout << "# [y]: " << parse_result["camera size"]["y"].dump() << std::endl;

        std::cout << '#' << std::endl << "##### [entrance]" << std::endl;
        std::cout << "# [x]: " << parse_result["entrance"]["x"].dump() << std::endl;
        std::cout << "# [y]: " << parse_result["entrance"]["y"].dump() << std::endl;

        std::cout << '#' << std::endl << "##### [exit]" << std::endl;
        std::cout << "# [x]: " << parse_result["exit"]["x"].dump() << std::endl;
        std::cout << "# [y]: " << parse_result["exit"]["y"].dump() << std::endl;

        std::cout << '#' << std::endl << "##### [fans]" << std::endl;
        std::cout << "# [size]: " << parse_result["fans"].array_items().size() << "\n";
        unsigned fan_counter = 0;
        for (auto &fan : parse_result["fans"].array_items()) {
            std::cout << "# [" << ++fan_counter << "] [Origin]" << fan["Origin"].dump() << "\n";
            std::cout << "#     [Endpoint]" << fan["Endpoint"].dump() << "\n";
            std::cout << "#     [Width]: " << fan["Width"].dump() << "\n";
        }

        std::cout << '#' << std::endl << "##### [walls]" << std::endl;
        std::cout << "# [size]: " << parse_result["walls"].array_items().size() << "\n";
        unsigned wall_counter = 0;
        for (auto &wall : parse_result["walls"].array_items()) {
            std::cout << "# [" << ++wall_counter << "] [Origin]" << wall["Origin"].dump() << "\n";
            std::cout << "#     [Endpoint]" << wall["Endpoint"].dump() << "\n";
            std::cout << "#     [radius]: " << wall["Radius"].dump() << "\n";
        }

        std::cout << '#' << std::endl << "##### [dialogues]" << std::endl;
        std::cout << "# [size]: " << parse_result["dialogues"].array_items().size() << "\n";
        unsigned dialogue_counter = 0;
        for (auto &k : parse_result["dialogues"].array_items()) {
            std::cout << "# [" << ++dialogue_counter << ']' << k.dump() << "\n";
        }

        std::cout << "##### [level info] end #####" << '\n' << '\n' << '\n';
    }

    void Level::Read(const unsigned & current_level = 1, const bool & debug = 0) {
        std::string err, level_address = "..//data//level" + std::to_string(current_level) +".json";
        std::cout << "Reading level from = " << level_address << std::endl;
        
        // trigger debug method
        if (debug) JsonTest(level_address);

        std::ifstream in(level_address);  
        std::string raw_levelfile((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        const auto parse_result = json11::Json::parse(raw_levelfile, err);

        // security check before loading basic info. 
        // If invalid, use the default value from construction to prevent game black page.
        if (parse_result["camera center"]["x"].is_number())
            camera_center_.x = static_cast<float>(parse_result["camera center"]["x"].number_value());
        if (parse_result["camera center"]["y"].is_number())
            camera_center_.y = static_cast<float>(parse_result["camera center"]["y"].number_value());
        if (parse_result["camera size"]["x"].is_number())
            camera_size_.x = static_cast<float>(parse_result["camera size"]["x"].number_value());
        if (parse_result["camera size"]["y"].is_number())
            camera_size_.y = static_cast<float>(parse_result["camera size"]["y"].number_value());
        if (parse_result["exit"]["x"].is_number())
            exit_.x = static_cast<float>(parse_result["exit"]["x"].number_value());        
        if (parse_result["exit"]["y"].is_number())
            exit_.y = static_cast<float>(parse_result["exit"]["y"].number_value());
        if (parse_result["entrance"]["x"].is_number())
            entrance_.x = static_cast<float>(parse_result["entrance"]["x"].number_value());
        if (parse_result["entrance"]["y"].is_number())
            entrance_.y = static_cast<float>(parse_result["entrance"]["y"].number_value());
        if (parse_result["fuel"].is_number())
            fuel_ = static_cast<float>(parse_result["fuel"].number_value());
        if (parse_result["oxygen"].is_number())
            oxygen_ = static_cast<float>(parse_result["oxygen"].number_value());
        
        // read fan informations        
        fans_.clear();
        fans_.shrink_to_fit();
        for (auto &fan : parse_result["fans"].array_items()) {
            fans_.emplace_back(                
                static_cast<float>(fan["Origin"]["x"].number_value()),
                static_cast<float>(fan["Origin"]["y"].number_value()),                
                static_cast<float>(fan["Endpoint"]["x"].number_value()),
                static_cast<float>(fan["Endpoint"]["y"].number_value()),
                static_cast<float>(fan["Width"].number_value()),
                static_cast<float>(fan["Origin"]["strength"].number_value()),
                static_cast<float>(fan["Endpoint"]["strength"].number_value()));
        }
        fans_.shrink_to_fit();
                
        // read wall informations
        walls_.clear();
        walls_.shrink_to_fit();        
        for (auto &wall : parse_result["walls"].array_items()) {
            walls_.emplace_back(
                static_cast<float>(wall["Origin"]["x"].number_value()),
                static_cast<float>(wall["Origin"]["y"].number_value()),
                static_cast<float>(wall["Endpoint"]["x"].number_value()),
                static_cast<float>(wall["Endpoint"]["y"].number_value()),
                static_cast<float>(wall["Radius"].number_value()));
        }
        walls_.shrink_to_fit();
        
        // read dialogues informations        
        dialogues_.clear();
        dialogues_.shrink_to_fit();
        for (auto &dialogue : parse_result["dialogues"].array_items()) {
            dialogues_.emplace_back(Dialogue(dialogue.string_value(), 1));
        }
        dialogues_.shrink_to_fit();
    }

    const Level::CameraCenter & Level::GetCameraCenter()
    {
        return camera_center_;
    }

    const Level::CameraSize & Level::GetCameraSize()
    {
        return camera_size_;
    }

    const Level::Exit & Level::GetExit()
    {
        return exit_;
    }

    const Level::Entrance & Level::GetEntrance()
    {
        return entrance_;
    }

    const float & Level::GetFuel()
    {
        return fuel_;
    }

    const float & Level::GetOxygen()
    {
        return oxygen_;
    }

    const std::vector<Level::Fan>& Level::GetFans()
    {
        return fans_;
    }

    const std::vector<Level::Wall>& Level::GetWalls()
    {
        return walls_;
    }

    const std::vector<Dialogue>& Level::GetDialogues()
    {
        return dialogues_;
    }


}