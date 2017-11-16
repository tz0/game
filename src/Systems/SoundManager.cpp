#include "Systems/SoundManager.h"

namespace tjg {

    SoundManager::SoundManager(ResourceManager &resource_manager) :
            resource_manager(resource_manager) {
    }

    void SoundManager::MenuScrollUp() {
        auto buffer = resource_manager.LoadSound("menu-scroll.wav");
        sf::Sound sound;
        sound.setBuffer(*buffer);
        sound.play();
    }

    void SoundManager::MenuScrollDown() {
        auto buffer = resource_manager.LoadSound("menu-scroll.wav");
        sf::Sound sound;
        sound.setBuffer(*buffer);
        sound.setPitch(0.8);
        sound.play();
    }

    void SoundManager::MenuSelect() {
        auto buffer = resource_manager.LoadSound("menu-scroll.wav");
        sf::Sound sound;
        sound.setBuffer(*buffer);
        sound.setPitch(1.5);
        sound.play();
    }

    void SoundManager::MenuBack() {
        auto buffer = resource_manager.LoadSound("menu-scroll.wav");
        sf::Sound sound;
        sound.setBuffer(*buffer);
        sound.setPitch(0.5);
        sound.play();
    }

}
