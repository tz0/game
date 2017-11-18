#include "Systems/SoundManager.h"

namespace tjg {

    SoundManager::SoundManager(ResourceManager &resource_manager) :
            resource_manager(resource_manager) {
        Initialize();
    }

    void SoundManager::Initialize() {
        // Menu sounds.
        // .. Up
        menu_up = sf::Sound(*resource_manager.LoadSound("menu-scroll.ogg"));
        menu_up.setRelativeToListener(true);
        // .. Down
        menu_down = sf::Sound(*resource_manager.LoadSound("menu-scroll.ogg"));
        menu_down.setRelativeToListener(true);
        menu_down.setPitch(0.8);
        // .. Select
        menu_select = sf::Sound(*resource_manager.LoadSound("menu-select.ogg"));
        menu_select.setRelativeToListener(true);
        menu_select.setPitch(0.75);
        menu_select.setVolume(25);
        // .. Woosh
        menu_woosh = sf::Sound(*resource_manager.LoadSound("menu-woosh.ogg"));
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
        jetpack_loop = sf::Sound(*resource_manager.LoadSound("jetpack.ogg"));
        jetpack_loop.setRelativeToListener(true);
        jetpack_loop.setVolume(75);
        jetpack_loop.setLoop(true);
    }

    void SoundManager::InitializeSpatialSounds(std::vector<std::shared_ptr<Entity>> &fans,
                                               std::vector<std::shared_ptr<Entity>> &shock_boxes,
                                               std::vector<std::shared_ptr<Entity>> &pressure_sources,
                                               std::vector<std::shared_ptr<Entity>> &walls) {

        // Create fan sounds.
        for (auto &fan : fans) {
            // Build a new fan sound.
            sf::Sound fan_sound = sf::Sound(*resource_manager.LoadSound("fan.ogg"));
            fan_sound.setLoop(true);
            fan_sound.setPitch(0.9);
            fan_sound.setAttenuation(3);
            fan_sound.setMinDistance(100);

            // Get the position of the fan and put the sound there.
            auto position = fan->GetComponent<Location>()->GetPosition();
            fan_sound.setPosition(position.x, position.y, 0);

            // Add the sound to the spatial sounds vector.
            spatial_sounds.push_back(std::move(fan_sound));
        }

        // Create shock box sounds.
        for (auto &shock_box : shock_boxes) {
            // Build a new shock box sound.
            sf::Sound shock_box_sound = sf::Sound(*resource_manager.LoadSound("shock-box.ogg"));
            shock_box_sound.setLoop(true);
            shock_box_sound.setAttenuation(5);
            shock_box_sound.setMinDistance(100);

            // Get the position of the shock box and put the sound there.
            auto position = shock_box->GetComponent<Location>()->GetPosition();
            shock_box_sound.setPosition(position.x, position.y, 0);

            // Add the sound to the spatial sounds vector.
            spatial_sounds.push_back(std::move(shock_box_sound));
        }

        // Create pressure source sounds.
        for (auto &pressure_source : pressure_sources) {
            // Build a new pressure source sound.
            sf::Sound pressure_source_sound = sf::Sound(*resource_manager.LoadSound("pressure-source.ogg"));
            pressure_source_sound.setLoop(true);
            pressure_source_sound.setAttenuation(3);
            pressure_source_sound.setMinDistance(100);

            // Get the position of the pressure source and put the sound there.
            auto position = pressure_source->GetComponent<Location>()->GetPosition();
            pressure_source_sound.setPosition(position.x, position.y, 0);

            // Add the sound to the spatial sounds vector.
            spatial_sounds.push_back(std::move(pressure_source_sound));
        }

        for (auto &wall : walls) {
            auto shape = wall->GetComponent<StaticSegment>()->GetShape();
            // Only make a sound if the wall is lethal (a laser wall).
            if (cpShapeGetCollisionType(shape) == static_cast<cpCollisionType>(CollisionGroup::LETHAL)) {
                // Build a new pressure source sound.
                sf::Sound laser_sound_middle = sf::Sound(*resource_manager.LoadSound("laser-wall.ogg"));
                laser_sound_middle.setLoop(true);
                laser_sound_middle.setAttenuation(5);
                laser_sound_middle.setMinDistance(100);

                // Get the position of the pressure source and put the sound there.
                auto position = wall->GetComponent<Location>()->GetPosition();
                laser_sound_middle.setPosition(position.x, position.y, 0);

                // Add the sound to the spatial sounds vector.
                spatial_sounds.push_back(std::move(laser_sound_middle));
            }
        }
    }

    void SoundManager::StartSpatialSounds() {
        for (auto &spatial_sound : spatial_sounds) {
            if (spatial_sound.getStatus() != sf::Music::Playing) {
                spatial_sound.play();
            }
        }
    }

    void SoundManager::PauseSpatialSounds() {
        for (auto &spatial_sound : spatial_sounds) {
            if (spatial_sound.getStatus() == sf::Music::Playing) {
                spatial_sound.pause();
            }
        }
    }

    void SoundManager::StopSpatialSounds() {
        for (auto &spatial_sound : spatial_sounds) {
            if (spatial_sound.getStatus() != sf::Music::Stopped) {
                spatial_sound.stop();
            }
        }
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
        if (menu_music->getStatus() != sf::Music::Stopped) {
            menu_music->stop();
        }
    }

    void SoundManager::StartLevelMusic() {
        if (level_music->getStatus() != sf::Music::Playing) {
            level_music->play();
        }
    }

    void SoundManager::PauseLevelMusic() {
        if (level_music->getStatus() == sf::Music::Playing) {
            level_music->pause();
        }
    }

    void SoundManager::StopLevelMusic() {
        if (level_music->getStatus() != sf::Music::Stopped) {
            level_music->stop();
        }
    }

    void SoundManager::StartWinMusic() {
        if (win_music->getStatus() != sf::Music::Playing) {
            win_music->play();
        }

    }

    void SoundManager::StopWinMusic() {
        if (win_music->getStatus() != sf::Music::Stopped) {
            win_music->stop();
        }
    }

    void SoundManager::StartLoseMusic() {
        if (lose_music->getStatus() != sf::Music::Playing) {
            lose_music->play();
        }
    }

    void SoundManager::StopLoseMusic() {
        if (lose_music->getStatus() != sf::Music::Stopped) {
            lose_music->stop();
        }
    }

    void SoundManager::StartJetPack() {
        if (jetpack_loop.getStatus() != sf::Music::Playing) {
            jetpack_loop.play();
        }
    }

    void SoundManager::StopJetPack() {
        if (jetpack_loop.getStatus() != sf::Music::Stopped) {
            jetpack_loop.stop();
        }
    }

}
