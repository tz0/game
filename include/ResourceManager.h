
#ifndef GAME_RESOURCEMANAGER_H
#define GAME_RESOURCEMANAGER_H

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class ResourceManager {
private:

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
                throw std::runtime_error(path + std::string(" not found"));
            }
            std::cout << "done." << std::endl;
        }
        return map[path];
    }

    std::string resource_root = std::string("");

    ResourceMap<sf::Font> fonts;
    ResourceMap<sf::SoundBuffer> sounds;
    ResourceMap<sf::Texture> textures;

public:
    ResourceManager() {}

    ResourceManager(const std::string &resource_root) {
        this->resource_root = resource_root;
    }

    std::shared_ptr<sf::Font> LoadFont(const std::string &filename) {
        return load(fonts, filename);
    }

    std::shared_ptr<sf::Texture> LoadTexture(const std::string &filename) {
        return load(textures, filename);
    }

    std::shared_ptr<sf::SoundBuffer> LoadSound(const std::string &filename) {
        return load(sounds, filename);
    }
};


#endif //GAME_RESOURCEMANAGER_H
