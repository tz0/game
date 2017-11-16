#include "Systems/SoundManager.h"

namespace tjg {

    SoundManager::SoundManager(tjg::ResourceManager &resource_manager) :
            resource_manager(resource_manager) {
    }

    void SoundManager::PlayMenuScroll() {
        printf("Trigger menu scroll sound...\n");
        auto buffer = resource_manager.LoadSound("menu-scroll.wav");
        printf("\tSound loaded.\n");
        sf::Sound sound;
        sound.setBuffer(*buffer);
        sound.play();
        printf("\tSound played.\n");
    }

}
