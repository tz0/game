#include "Level.h"

namespace tjg {
    Level::Level() : 
        exit_{-1000, -200}, entrance_{0, 0},  total_fuel_(5), total_oxygen_(45) {
    }

    Level::~Level() = default;

    void Level::JsonTest(const std::string & level_address) {        
        std::string err;
        std::ifstream in(level_address);
        std::string raw_levelfile((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        const auto parse_result = json11::Json::parse(raw_levelfile, err);

        std::cout << std::endl << "##### [level info] start #####" << std::endl;
        std::cout << "# [level]: " << parse_result["level"].dump() << std::endl;
        std::cout << "# [total_fuel]: " << parse_result["total_fuel"].dump() << std::endl;
        std::cout << "# [total_oxygen]: " << parse_result["total_oxygen"].dump() << std::endl;

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
            std::cout << "# [" << ++fan_counter << "] [Origin]" << fan["Endpoints"]["Origin"].dump() << "\n";
            std::cout << "#     [Endpoint]" << fan["Endpoints"]["Endpoint"].dump() << "\n";
            std::cout << "#     [Width]: " << fan["Width"].dump() << "\n";
        }

        std::cout << '#' << std::endl << "##### [walls]" << std::endl;
        std::cout << "# [size]: " << parse_result["walls"].array_items().size() << "\n";
        unsigned wall_counter = 0;
        for (auto &wall : parse_result["walls"].array_items()) {
            std::cout << "# [" << ++wall_counter << "] [Origin]" << wall["Endpoints"]["Origin"].dump() << "\n";
            std::cout << "#     [Endpoint]" << wall["Endpoints"]["Endpoint"].dump() << "\n";
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

        //TODO: add is_number check here, since other members believe level check is very unnecessary. This TODO can wait or abort.
        exit_.x = static_cast<float>(parse_result["exit"]["x"].number_value());        
        exit_.y = static_cast<float>(parse_result["exit"]["y"].number_value());
        entrance_.x = static_cast<float>(parse_result["entrance"]["x"].number_value());
        entrance_.y = static_cast<float>(parse_result["entrance"]["y"].number_value());
        total_fuel_ = static_cast<float>(parse_result["total_fuel"].number_value());
        total_oxygen_ = static_cast<float>(parse_result["total_oxygen"].number_value());
        
        // read fan informations        
        fans_.clear();
        fans_.shrink_to_fit();
        for (auto &fan : parse_result["fans"].array_items()) {
            fans_.emplace_back(                
                static_cast<float>(fan["Endpoints"]["Origin"]["x"].number_value()),
                static_cast<float>(fan["Endpoints"]["Origin"]["y"].number_value()),                
                static_cast<float>(fan["Endpoints"]["Endpoint"]["x"].number_value()),
                static_cast<float>(fan["Endpoints"]["Endpoint"]["y"].number_value()),
                static_cast<float>(fan["Width"].number_value()),
                static_cast<float>(fan["Endpoints"]["Origin"]["strength"].number_value()),
                static_cast<float>(fan["Endpoints"]["Endpoint"]["strength"].number_value()));
        }
        fans_.shrink_to_fit();
                
        // read wall informations
        walls_.clear();
        walls_.shrink_to_fit();        
        for (auto &wall : parse_result["walls"].array_items()) {
            walls_.emplace_back(
                static_cast<float>(wall["Endpoints"]["Origin"]["x"].number_value()),
                static_cast<float>(wall["Endpoints"]["Origin"]["y"].number_value()),
                static_cast<float>(wall["Endpoints"]["Endpoint"]["x"].number_value()),
                static_cast<float>(wall["Endpoints"]["Endpoint"]["y"].number_value()),
                static_cast<float>(wall["Radius"].number_value()));
        }
        walls_.shrink_to_fit();
        
        // read dialogues informations        
        dialogues_.clear();
        dialogues_.shrink_to_fit();
        for (auto &dialogue : parse_result["dialogues"].array_items()) {
            dialogues_.emplace_back(dialogue.string_value());
        }
        dialogues_.shrink_to_fit();
    }

    const Level::Exit & Level::GetExit()
    {
        return exit_;
    }

    const Level::Entrance & Level::GetEntrance()
    {
        return entrance_;
    }

    const float & Level::GetTotalFuel()
    {
        return total_fuel_;
    }

    const float & Level::GetTotalOxygen()
    {
        return total_oxygen_;
    }

    const std::vector<Level::Fan>& Level::GetFans()
    {
        return fans_;
    }

    const std::vector<Level::Wall>& Level::GetWalls()
    {
        return walls_;
    }

    const std::vector<std::string>& Level::GetDialogues()
    {
        return dialogues_;
    }


}