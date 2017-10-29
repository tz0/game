#include "LevelReader.h"

namespace tjg {
    LevelReader::LevelReader(const std::string &level_root) : level_root(level_root) {        
        std::cout << "Gason test begin" << std::endl;
        std::cout << "level_root = " << level_root << std::endl;      
    }

    LevelReader::~LevelReader() {

    }

    void LevelReader::JsonTest() {

        ////const std::string simple_test 
        //    R"({"k1":"v1", "k2":42, "k3":["a",123,true,false,null]})";
        //std::string err;
        //const auto json = json11::Json::parse(simple_test, err);
        //std::cout << "k1: " << json["k1"].string_value() << "\n";
        //std::cout << "k3: " << json["k3"].dump() << "\n";
        //for (auto &k : json["k3"].array_items()) {
        //    std::cout << "    - " << k.dump() << "\n";
        //}
    
        ////test.json test
        //std::cout << "file read test." << std::endl;
        //std::ifstream in("..//data//test.json");
        ////std::ifstream in("..\\data\\test.json");        
        //std::string raw_levelfile((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        //std::cout << "[raw file] " << raw_levelfile << std::endl;

        //std::string err;
        //const auto parse_result = json11::Json::parse(raw_levelfile, err);
        //std::cout << "k1: " << parse_result["k1"].string_value() << "\n";        
        //std::cout << "k2: " << parse_result["k2"].dump() << "\n";
        //std::cout << "k3: " << parse_result["k3"].dump() << "\n";
        //for (auto &k : parse_result["k3"].array_items()) {
        //    std::cout << "    - " << k.dump() << "\n";
        //}

        //std::cout << parse_result.dump() << '\n';
        //std::cout << typeid(parse_result.dump()).name() << '\n';
        //std::cout << parse_result[1].dump() << '\n'; // null, nothing
        //std::cout << typeid(parse_result[1].dump()).name() << '\n'; //using std <vector> as array
        //std::cout << typeid(parse_result).name() << std::endl; //  class json11::Json



        //level1.json test
        std::cout << "level1 read successfully." << std::endl;
        std::ifstream in("..//data//level1.json");
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
        std::cout << "[height]: " << parse_result["entrance"]["height"].dump() << std::endl;
        std::cout << "[weight]: " << parse_result["entrance"]["weight"].dump() << std::endl;
        
        std::cout << std::endl << "---- [exit]" << std::endl;        
        std::cout << "[x]: " << parse_result["exit"]["x"].dump() << std::endl;
        std::cout << "[y]: " << parse_result["exit"]["y"].dump() << std::endl;
        std::cout << "[height]: " << parse_result["exit"]["height"].dump() << std::endl;
        std::cout << "[weight]: " << parse_result["exit"]["weight"].dump() << std::endl;

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





}