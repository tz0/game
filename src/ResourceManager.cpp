#include "ResourceManager.h"

namespace tjg {
/**
 * @param resource_root Path to resources root folder
 */
    ResourceManager::ResourceManager(const std::string &resource_root) {

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
        placeholder_texture = std::make_shared<sf::Texture>();
        placeholder_texture->loadFromImage(placeholder_image);
        placeholder_texture->setRepeated(true);

        this->resource_root = resource_root;
    }

/**
 * Load the given font
 * @param filename
 * @return pointer to the Font
 */
    std::shared_ptr<sf::Font> ResourceManager::LoadFont(const std::string &filename) {
        return load(fonts, filename);
    }

/**
 * Load the given texture
 * @param filename
 * @return pointer to the Texture
 */
    std::shared_ptr<sf::Texture> ResourceManager::LoadTexture(const std::string &filename) {
        auto texture = load(textures, filename);
        if (texture == nullptr) {
            return placeholder_texture;
        }
        texture->setSmooth(true);
        return texture;
    }

/**
 * Load the given sound
 * @param filename
 * @return pointer to the Sound
 */
    std::shared_ptr<sf::SoundBuffer> ResourceManager::LoadSound(const std::string &filename) {
        return load(sounds, filename);
    }
}