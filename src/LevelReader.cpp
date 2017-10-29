#include "LevelReader.h"

namespace tjg {
    LevelReader::LevelReader(const std::string &level_root) : level_root(level_root)
    {        
        std::cout << "Gason test begin" << std::endl;
        std::cout << "level_root = " << level_root << std::endl;      
    }

    LevelReader::~LevelReader()
    {
    }

    void LevelReader::JsonTest() {
        const std::string simple_test =
            R"({"k1":"v1", "k2":42, "k3":["a",123,true,false,null]})";

        std::string err;
        const auto json = json11::Json::parse(simple_test, err);

        std::cout << "k1: " << json["k1"].string_value() << "\n";
        std::cout << "k3: " << json["k3"].dump() << "\n";

        for (auto &k : json["k3"].array_items()) {
            std::cout << "    - " << k.dump() << "\n";
        }
    }





}