#include "Level.h"

namespace tjg {
    //Level::Level() :
    //    exit.x(-1000),
    //    exit.y(-200) {
    //}

    Level::Level() : 
        exit_{-1000, -200}, entrance_{0, 0},  total_fuel_(5), total_oxygen_(45) {
    }

    Level::~Level() = default;

    void Level::JsonTest() {        
        //level1.json test
        std::cout << "level1 read successfully." << std::endl;
        std::ifstream in("..//data//level1.json");  //universal seperator 
                                                    //std::ifstream in("..\\data\\level1.json");        
        std::string raw_levelfile((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        //std::cout << "[raw file] " << raw_levelfile << std::endl;

        std::string err;
        const auto parse_result = json11::Json::parse(raw_levelfile, err);
        //std::cout << "[parse result]" << parse_result.dump() << '\n';

        std::cout << std::endl << "---- [level info]" << std::endl;
        std::cout << "[level]: " << parse_result["level"].dump() << std::endl;
        std::cout << "[gas]: " << parse_result["gas"].dump() << std::endl;
        std::cout << "[oxygen]: " << parse_result["oxygen"].dump() << std::endl;
        //std::cout << "[]: " << parse_result[""].dump() << std::endl;

        std::cout << std::endl << "---- [entrance]" << std::endl;
        //std::cout << "[entrance]: " << parse_result["entrance"].dump() << std::endl;
        //std::cout << "[entrance]: " << parse_result["entrance"].is_object() << std::endl;        
        //std::cout << "[entrance]: " << typeid(parse_result["entrance"]).name() << std::endl;
        std::cout << "[x]: " << parse_result["entrance"]["x"].dump() << std::endl;
        std::cout << "[y]: " << parse_result["entrance"]["y"].dump() << std::endl;

        std::cout << std::endl << "---- [exit]" << std::endl;
        std::cout << "[x]: " << parse_result["exit"]["x"].dump() << std::endl;
        std::cout << "[y]: " << parse_result["exit"]["y"].dump() << std::endl;

        std::cout << std::endl << "---- [fans]" << std::endl;
        std::cout << "[size]: " << parse_result["fans"].array_items().size() << "\n";
        unsigned fan_counter = 0;
        for (auto &fan : parse_result["fans"].array_items()) {
            std::cout << "[" << ++fan_counter << "] [Origin]" << fan["Endpoints"]["Origin"].dump() << "\n";
            std::cout << "[" << fan_counter << "] [Endpoint]" << fan["Endpoints"]["Endpoint"].dump() << "\n";
            std::cout << "[" << fan_counter << "] [Width]: " << fan["Width"].dump() << "\n";
            std::cout << "[" << fan_counter << "] [Width]: " << typeid(fan["Width"].dump()).name() << "\n";
        }


        std::cout << std::endl << "---- [dialogues]" << std::endl;
        std::cout << "[size]: " << parse_result["dialogues"].array_items().size() << "\n";
        //std::cout << "[dialogues - 1]: " << parse_result["dialogues"].array_items()[0].dump() << "\n"; //using std <vector> as array
        unsigned dialogue_counter = 0;
        for (auto &k : parse_result["dialogues"].array_items()) {
            std::cout << '[' << ++dialogue_counter << ']' << k.dump() << "\n";
        }
        //std::cout << "k2: " << parse_result["k2"].dump() << "\n";
        //std::cout << "k3: " << parse_result["k3"].dump() << "\n";
        //for (auto &k : parse_result["k3"].array_items()) {
        //    std::cout << "    - " << k.dump() << "\n";
        //}

    }

    void Level::Read(const unsigned & current_level = 1) {
        std::string err, level_address = "..//data//level" + std::to_string(current_level) +".json";

        std::cout << "Reading level from = " << level_address << std::endl;

        std::ifstream in(level_address);  
        std::string raw_levelfile((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        const auto parse_result = json11::Json::parse(raw_levelfile, err);

        //TODO: add is_number check here
        exit_.x = static_cast<float>(parse_result["exit"]["x"].number_value());        
        exit_.y = static_cast<float>(parse_result["exit"]["y"].number_value());
        entrance_.x = static_cast<float>(parse_result["entrance"]["x"].number_value());
        entrance_.y = static_cast<float>(parse_result["entrance"]["y"].number_value());
        total_fuel_ = static_cast<float>(parse_result["total_fuel"].number_value());
        total_oxygen_ = static_cast<float>(parse_result["total_oxygen"].number_value());
        
        std::cout << std::endl << "[read]" << std::endl;
        std::cout << "[x]: " << exit_.x << std::endl;
        std::cout << "[y]: " << exit_.y << std::endl;        
        std::cout << "[total fuel]: " << total_fuel_ << std::endl;
        std::cout << "[total oxygen]: " << total_oxygen_ << std::endl;
        

        std::cout << "[fans] vector test: " << std::endl;
        fans_.clear();
        fans_.shrink_to_fit();
        std::cout << "[fans empty]: " << fans_.empty() << std::endl;
        std::cout << "[fans max_size]: " << fans_.max_size() << std::endl;
        std::cout << "[fans capacity]: " << fans_.capacity() << std::endl;
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
        std::cout << "[fans] shrinked vector: " << std::endl;
        std::cout << "[fans max_size]: " << fans_.max_size() << std::endl;
        std::cout << "[fans capacity]: " << fans_.capacity() << std::endl;

        //fans_.clear();
        //fans_.shrink_to_fit();
        //std::cout << "[fans empty]: " << fans_.empty() << std::endl;
        //std::cout << "[fans max_size]: " << fans_.max_size() << std::endl;
        //std::cout << "[fans capacity]: " << fans_.capacity() << std::endl;
        
        

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


}