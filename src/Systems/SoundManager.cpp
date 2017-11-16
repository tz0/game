#include "Systems/SoundManager.h"

namespace tjg {

    SoundManager::SoundManager(ResourceManager &resource_manager) :
            resource_manager(resource_manager) {
    }

    void SoundManager::MenuScrollUp() {
        auto buffer = resource_manager.LoadSound("menu-scroll.wav");
        sf::Sound sound;
        sound.setBuffer(*buffer);
        sound.setPitch(1.2);
        sound.play();
    }

    void SoundManager::MenuScrollDown() {
        auto buffer = resource_manager.LoadSound("menu-scroll.wav");
        sf::Sound sound;
        sound.setBuffer(*buffer);
        sound.setPitch(0.8);
        sound.play();
    }

}
