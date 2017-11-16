#include "Systems/SoundManager.h"

namespace tjg {

    SoundManager::SoundManager(ResourceManager &resource_manager) :
            resource_manager(resource_manager) {
    }

    void SoundManager::PlayMenuScroll() {
        auto buffer = resource_manager.LoadSound("menu-scroll.wav");
        sf::Sound sound;
        sound.setBuffer(*buffer);
        sound.play();
    }

}
