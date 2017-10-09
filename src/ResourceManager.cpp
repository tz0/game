#include "ResourceManager.h"

/**
 * @param resource_root Path to resources root folder
 */
tjg::ResourceManager::ResourceManager(const std::string &resource_root) {
    this->resource_root = resource_root;
}

/**
 * Load the given font
 * @param filename
 * @return pointer to the Font
 */
std::shared_ptr<sf::Font> tjg::ResourceManager::LoadFont(const std::string &filename) {
    return load(fonts, filename);
}

/**
 * Load the given texture
 * @param filename
 * @return pointer to the Texture
 */
std::shared_ptr<sf::Texture> tjg::ResourceManager::LoadTexture(const std::string &filename) {
    return load(textures, filename);
}

/**
 * Load the given sound
 * @param filename
 * @return pointer to the Sound
 */
std::shared_ptr<sf::SoundBuffer> tjg::ResourceManager::LoadSound(const std::string &filename) {
    return load(sounds, filename);
}
