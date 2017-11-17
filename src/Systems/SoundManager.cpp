#include "Systems/SoundManager.h"

namespace tjg {

    SoundManager::SoundManager(ResourceManager &resource_manager) :
            resource_manager(resource_manager) {
        Initialize();
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
        menu_select.setPitch(0.8);
        menu_select.setVolume(50);
        // .. Woosh
        menu_woosh = sf::Sound(*resource_manager.LoadSound("menu-woosh.wav"));
        menu_woosh.setVolume(200);
        // .. Music
        menu_music = resource_manager.LoadMusic("menu-music.wav");
        menu_music->setVolume(3);
        menu_music->setLoop(true);
    }

    void SoundManager::MenuScrollUp() {
        menu_up.play();
    }

    void SoundManager::MenuScrollDown() {
        menu_down.play();
    }

    void SoundManager::MenuSelect() {
        menu_select.play();
    }

    void SoundManager::MenuWoosh() {
        menu_woosh.play();
    }

    void SoundManager::StartMenuMusic() {
        if (menu_music->getStatus() != sf::Music::Playing) {
            menu_music->play();
        }
    }

    void SoundManager::StopMenuMusic() {
        if (menu_music->getStatus() == sf::Music::Playing) {
            menu_music->stop();
        }
    }

}
