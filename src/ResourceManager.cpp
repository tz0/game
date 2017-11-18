#include "ResourceManager.h"

namespace tjg {
    /**
    * @param resource_root Path to resources root folder
    */
    ResourceManager::ResourceManager(const std::string &resource_root,
                                     const std::string &font_folder,
                                     const std::string &texture_folder,
                                     const std::string &sound_folder,
                                     const std::string &music_folder) {

        // Generate placeholder image with checkerboard pattern
        sf::Image placeholder_image;
        placeholder_image.create(8, 8, sf::Color::Red);
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                placeholder_image.setPixel(x, y, sf::Color::White);
                placeholder_image.setPixel(x + 4, y + 4, sf::Color::Blue);
            }
        }

        // Load the placeholder texture from the placeholder image generated above.
        textures[placeholder] = std::make_shared<sf::Texture>();
        textures[placeholder]->loadFromImage(placeholder_image);
        textures[placeholder]->setRepeated(true);

        // Placeholder sound.
        sounds[placeholder] = std::make_shared<sf::SoundBuffer>();

        // Placeholder music.
        music[placeholder] = std::make_shared<sf::Music>();

        // Placeholder font.
        fonts[placeholder] = std::make_shared<sf::Font>();

        // Store resource directory information.
        this->resource_root = resource_root;
        this->font_folder = font_folder;
        this->texture_folder = texture_folder;
        this->sound_folder = sound_folder;
        this->music_folder = music_folder;
    }

    /**
     * Load the given font
     * @param filename
     * @return pointer to the Font
    */
    std::shared_ptr<sf::Font> ResourceManager::LoadFont(const std::string &filename) {
        return load(fonts, resource_root + "/" + font_folder + "/" + filename);
    }

    /**
    * Load the given texture
    * @param filename
    * @return pointer to the Texture
    */
    std::shared_ptr<sf::Texture> ResourceManager::LoadTexture(const std::string &filename) {
        auto texture = load(textures, resource_root + "/" + texture_folder + "/" + filename);
        texture->setSmooth(true);
        return texture;
    }

    /**
    * Load the given sound using a SoundBuffer
    * @param filename
    * @return pointer to the SoundBuffer
    */
    std::shared_ptr<sf::SoundBuffer> ResourceManager::LoadSound(const std::string &filename) {
        return load(sounds, resource_root + "/" + sound_folder + "/" + filename);
    }

    /**
    * Load the music
    * @param filename
    * @return pointer to the Music
    */
    std::shared_ptr<sf::Music> ResourceManager::LoadMusic(const std::string &filename) {
        //return openMusic(music, resource_root + "/" + music_folder + "/" + filename);
        std::function<bool(std::shared_ptr<sf::Music>, const std::string &)> openFromFile =
                [](std::shared_ptr<sf::Music> res, const std::string &p) -> bool {
                    return res->openFromFile(p);
                };

        return load(music, std::string(resource_root + "/" + music_folder + "/" + filename), openFromFile);
    }
}