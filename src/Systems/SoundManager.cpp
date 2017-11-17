#include "Systems/SoundManager.h"

namespace tjg {

    SoundManager::SoundManager(ResourceManager &resource_manager) :
            resource_manager(resource_manager) {
        Initialize();
    }

    void SoundManager::Initialize() {
        // Menu sounds.
        // .. Up
        menu_up = sf::Sound(*resource_manager.LoadSound("menu-scroll.wav"));
        menu_up.setRelativeToListener(true);
        // .. Down
        menu_down = sf::Sound(*resource_manager.LoadSound("menu-scroll.wav"));
        menu_down.setRelativeToListener(true);
        menu_down.setPitch(0.8);
        // .. Select
        menu_select = sf::Sound(*resource_manager.LoadSound("menu-select.wav"));
        menu_select.setRelativeToListener(true);
        menu_select.setPitch(0.75);
        menu_select.setVolume(25);
        // .. Woosh
        menu_woosh = sf::Sound(*resource_manager.LoadSound("menu-woosh.wav"));
        menu_woosh.setRelativeToListener(true);
        menu_woosh.setVolume(200);

        // Music and ambience
        // .. Menu/Pause
        menu_music = resource_manager.LoadMusic("menu-music.wav");
        menu_music->setRelativeToListener(true);
        menu_music->setVolume(50);
        menu_music->setLoop(true);
        // .. Level
        level_music = resource_manager.LoadMusic("level-music.wav");
        level_music->setRelativeToListener(true);
        level_music->setVolume(50);
        level_music->setLoop(true);
        // .. Lose
        lose_music = resource_manager.LoadMusic("lose-music.wav");
        lose_music->setRelativeToListener(true);
        lose_music->setVolume(50);
        lose_music->setLoop(true);
        // .. Win
        win_music = resource_manager.LoadMusic("win-music.wav");
        win_music->setRelativeToListener(true);
        win_music->setVolume(10);
        win_music->setLoop(true);

        // In-game SFX
        // .. Jetpack
        jetpack_loop = sf::Sound(*resource_manager.LoadSound("jetpack-loop.wav"));
        jetpack_loop.setRelativeToListener(true);
        jetpack_loop.setVolume(75);
        jetpack_loop.setLoop(true);
    }

    void SoundManager::InitializeSpatialSounds(std::vector<std::shared_ptr<Entity>> fans,
                                               std::vector<std::shared_ptr<Entity>> shock_boxes,
                                               std::vector<std::shared_ptr<Entity>> pressure_sources,
                                               std::vector<std::shared_ptr<Entity>> walls) {

        // TODO: implement me.
    }

    void SoundManager::UpdateListenerPosition(std::shared_ptr<Location> &player_location) {
        auto position = player_location->GetPosition();
        sf::Listener::setPosition(sf::Vector3f(position.x, position.y, 0));
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

    void SoundManager::StartJetPack() {
        if (jetpack_loop.getStatus() != sf::Music::Playing) {
            jetpack_loop.play();
        }
    }

    void SoundManager::StopJetPack() {
        if (jetpack_loop.getStatus() == sf::Music::Playing) {
            jetpack_loop.stop();
        }
    }

}
