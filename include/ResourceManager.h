
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
        std::shared_ptr<T> load(ResourceMap<T> &map, const std::string &path) {
            // Check if the resource was found in the proper map.
            if (map.find(path) == map.end()) {
                // Put a new KVP in the map.
                std::pair<std::string, std::shared_ptr<T>> resource(path, std::make_shared<T>());
                map.insert(std::move(resource));

                // Print a brief loading message.
                std::cout << "Loading " << path << " ... ";
                // Attempt to load from file.
                auto success = map[path]->loadFromFile(path);
                if (!success) {
                    std::cout << path << " not found." << std::endl;
                    return map[placeholder];
                }
                // Print that loading is done.
                std::cout << "done." << std::endl;
            }

            // If the resource was found in the path, just return it.
            return map[path];
        }

        // Resource directory information
        std::string resource_root = std::string("");
        std::string font_folder = std::string("");
        std::string texture_folder = std::string("");
        std::string sound_folder = std::string("");

        // Resource maps
        ResourceMap<sf::Font> fonts;
        ResourceMap<sf::SoundBuffer> sounds;
        ResourceMap<sf::Texture> textures;

    public:
        // Constructors
        explicit ResourceManager(const std::string &resource_root = "resources",
                                 const std::string &font_folder = "fonts",
                                 const std::string &texture_folder = "textures",
                                 const std::string &sound_folder = "sounds");
        // Resource loading
        std::shared_ptr<sf::Font> LoadFont(const std::string &filename);
        std::shared_ptr<sf::Texture> LoadTexture(const std::string &filename);
        std::shared_ptr<sf::SoundBuffer> LoadSound(const std::string &filename);
    };

}

#endif //GAME_RESOURCEMANAGER_H
