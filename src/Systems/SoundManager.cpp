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
        menu_select.setVolume(50);
        // .. Woosh
        menu_woosh = sf::Sound(*resource_manager.LoadSound("menu-woosh.ogg"));
        menu_woosh.setRelativeToListener(true);
        menu_woosh.setVolume(400);

        // Music and ambience
        // .. Menu/Pause
        menu_music = resource_manager.LoadMusic("menu-music.ogg");
        menu_music->setRelativeToListener(true);
        menu_music->setVolume(50);
        menu_music->setLoop(true);
        // .. Level
        level_music = resource_manager.LoadMusic("level-music.ogg");
        level_music->setRelativeToListener(true);
        level_music->setVolume(25);
        level_music->setLoop(true);
        // .. Lose
        lose_music = resource_manager.LoadMusic("lose-music.ogg");
        lose_music->setRelativeToListener(true);
        lose_music->setVolume(50);
        lose_music->setLoop(true);
        // .. Win
        win_music = resource_manager.LoadMusic("win-music.ogg");
        win_music->setRelativeToListener(true);
        win_music->setVolume(10);
        win_music->setLoop(true);

        // In-game SFX
        // .. Jetpack
        jetpack = sf::Sound(*resource_manager.LoadSound("jetpack.ogg"));
        jetpack.setRelativeToListener(true);
        jetpack.setVolume(75);
        jetpack.setLoop(true);
        // .. Collisions
        collision = sf::Sound(*resource_manager.LoadSound("collision.ogg"));
        collision.setRelativeToListener(true);
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
            fan_sound.setAttenuation(4);
            fan_sound.setMinDistance(200);

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
            shock_box_sound.setAttenuation(4);
            shock_box_sound.setMinDistance(150);

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
            pressure_source_sound.setAttenuation(5);
            pressure_source_sound.setVolume(150);
            pressure_source_sound.setMinDistance(300);

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
                // Build a new sound node at the first end of the laser wall.
                sf::Sound laser_sound_first = sf::Sound(*resource_manager.LoadSound("laser-hum.ogg"));
                laser_sound_first.setLoop(true);
                laser_sound_first.setAttenuation(10);
                laser_sound_first.setVolume(75);
                laser_sound_first.setMinDistance(125);
                // Get the position of the first end of the wall and put the node there.
                auto point1 = cpSegmentShapeGetA(shape);
                laser_sound_first.setPosition(static_cast<float>(point1.x), static_cast<float>(point1.y), 0);
                // Add the sound to the spatial sounds vector.
                spatial_sounds.push_back(std::move(laser_sound_first));

                // Build a new sound node at the center of the laser wall.
                sf::Sound laser_sound_middle = sf::Sound(*resource_manager.LoadSound("laser-hum.ogg"));
                laser_sound_middle.setLoop(true);
                laser_sound_middle.setAttenuation(10);
                laser_sound_middle.setVolume(75);
                laser_sound_middle.setMinDistance(125);
                // Get the position of the center of the wall and put a sound node there
                auto middle_position = wall->GetComponent<Location>()->GetPosition();
                laser_sound_middle.setPosition(middle_position.x, middle_position.y, 0);
                // Add the sound to the spatial sounds vector.
                spatial_sounds.push_back(std::move(laser_sound_middle));

                // Build a new sound node at the second end of the laser wall.
                sf::Sound laser_sound_second = sf::Sound(*resource_manager.LoadSound("laser-hum.ogg"));
                laser_sound_second.setLoop(true);
                laser_sound_second.setAttenuation(10);
                laser_sound_second.setVolume(75);
                laser_sound_second.setMinDistance(125);
                // Get the position of the first end of the wall and put the node there.
                auto point2 = cpSegmentShapeGetB(shape);
                laser_sound_second.setPosition(static_cast<float>(point2.x), static_cast<float>(point2.y), 0);
                // Add the sound to the spatial sounds vector.
                spatial_sounds.push_back(std::move(laser_sound_second));
            }
        }
    }

    void SoundManager::UpdateListenerPosition(std::shared_ptr<Location> &player_location) {
        auto position = player_location->GetPosition();
        sf::Listener::setPosition(sf::Vector3f(position.x, position.y, 0));
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

    void SoundManager::ClearSpatialSounds() {
        spatial_sounds.clear();
        spatial_sounds.shrink_to_fit();
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
        if (jetpack.getStatus() != sf::Music::Playing) {
            jetpack.play();
        }
    }

    void SoundManager::StopJetPack() {
        if (jetpack.getStatus() != sf::Music::Stopped) {
            jetpack.stop();
        }
    }

    void SoundManager::Collision(cpVect impulse) {
        if (collision.getStatus() != sf::Music::Playing) {
            collision.setVolume(std::abs(static_cast<float>(impulse.x + impulse.y)) / 3.f);
            collision.play();
        }
    }

}
