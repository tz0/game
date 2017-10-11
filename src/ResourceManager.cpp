#include "ResourceManager.h"

namespace tjg {
/**
 * @param resource_root Path to resources root folder
 */
    ResourceManager::ResourceManager(const std::string &resource_root) {
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