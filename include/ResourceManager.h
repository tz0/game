
#ifndef GAME_RESOURCEMANAGER_H
#define GAME_RESOURCEMANAGER_H

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace tjg {

    class ResourceManager {
    private:
        const std::string placeholder = "PLACEHOLDER";

        template<typename T>
        using ResourceMap = std::unordered_map<std::string, std::shared_ptr<T>>;

        template<typename T>
        std::shared_ptr<T> load(ResourceMap<T> &map, const std::string &filename) {

            auto path = resource_root + "/" + filename;

            if (map.find(path) == map.end()) {
                // Not found, need to load
                std::pair<std::string, std::shared_ptr<T>> resource(path, std::make_shared<T>());
                map.insert(std::move(resource));

                std::cout << "Loading " << path << "...";
                auto success = map[path]->loadFromFile(path);
                if (!success) {
                    std::cout << path << " not found." << std::endl;
                    return map[placeholder];
                }
                std::cout << "done." << std::endl;
            }
            return map[path];
        }

        // Resource root path
        std::string resource_root = std::string("");

        // Resource maps
        ResourceMap<sf::Font> fonts;
        ResourceMap<sf::SoundBuffer> sounds;
        ResourceMap<sf::Texture> textures;

    public:
        // Constructors
        explicit ResourceManager(const std::string &resource_root = "");
        // Resource loading
        std::shared_ptr<sf::Font> LoadFont(const std::string &filename);
        std::shared_ptr<sf::Texture> LoadTexture(const std::string &filename);
        std::shared_ptr<sf::SoundBuffer> LoadSound(const std::string &filename);
    };

}

#endif //GAME_RESOURCEMANAGER_H
