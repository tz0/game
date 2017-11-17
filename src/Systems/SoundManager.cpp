#include "Systems/SoundManager.h"

namespace tjg {

    SoundManager::SoundManager(ResourceManager &resource_manager) :
            resource_manager(resource_manager) {
        Initialize();
    }

    void SoundManager::MenuScrollUp() {
        menu_up.play();
    }

    void SoundManager::MenuScrollDown() {
        menu_down.play();
    }

    void SoundManager::MenuSelect() {
        if (menu_select.getStatus() != sf::Sound::Playing) {
            menu_select.play();
        }
    }

    void SoundManager::MenuWoosh() {
        menu_woosh.play();
    }

    void SoundManager::Initialize() {
        // Initialize menu sounds.
        // .. Up
        menu_up = sf::Sound(*resource_manager.LoadSound("menu-scroll.wav"));
        // .. Down
        menu_down = sf::Sound(*resource_manager.LoadSound("menu-scroll.wav"));
        menu_down.setPitch(0.8);
        // .. Select
        menu_select = sf::Sound(*resource_manager.LoadSound("menu-select.wav"));
        menu_select.setPitch(1.5);
        // .. Woosh
        menu_woosh = sf::Sound(*resource_manager.LoadSound("menu-woosh.wav"));
    }

}
