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
        menu_select.setPitch(0.75);
        menu_select.setVolume(25);
        // .. Woosh
        menu_woosh = sf::Sound(*resource_manager.LoadSound("menu-woosh.wav"));
        menu_woosh.setVolume(200);


        // Music
        // .. Menu/Pause
        menu_music = resource_manager.LoadMusic("menu-music.wav");
        menu_music->setVolume(25);
        menu_music->setLoop(true);
        // .. Level
        level_music = resource_manager.LoadMusic("level-music.wav");
        level_music->setVolume(40);
        level_music->setLoop(true);
        // .. Lose
        lose_music = resource_manager.LoadMusic("lose-music.wav");
        lose_music->setVolume(50);
        lose_music->setLoop(true);
        // .. Win
        win_music = resource_manager.LoadMusic("win-music.wav");
        win_music->setVolume(3);
        win_music->setLoop(true);
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

    void SoundManager::StartLevelMusic() {
        if (level_music->getStatus() != sf::Music::Playing) {
            level_music->play();
        }
    }

    void SoundManager::PauseLevelMusic() {
        if (level_music->getStatus() != sf::Music::Paused) {
            level_music->pause();
        }
    }

    void SoundManager::StopLevelMusic() {
        if (level_music->getStatus() == sf::Music::Playing) {
            level_music->stop();
        }
    }

    void SoundManager::StartWinMusic() {
        if (win_music->getStatus() != sf::Music::Playing) {
            win_music->play();
        }

    }

    void SoundManager::StopWinMusic() {
        if (win_music->getStatus() == sf::Music::Playing) {
            win_music->stop();
        }

    }

    void SoundManager::StartLoseMusic() {
        if (lose_music->getStatus() != sf::Music::Playing) {
            lose_music->play();
        }
    }

    void SoundManager::StopLoseMusic() {
        if (lose_music->getStatus() == sf::Music::Playing) {
            lose_music->stop();
        }

    }

}
