#ifndef GAME_SOUNDMANAGER_H
#define GAME_SOUNDMANAGER_H

#include "ResourceManager.h"
#include "CollisionCenter.h"
#include "Components/StaticSegment.h"
#include "Components/Location.h"
#include "Entity.h"

namespace tjg {

    class SoundManager {
    private:
        // Resource manager to load sounds with.
        ResourceManager &resource_manager;

        // Menu sounds.
        sf::Sound menu_up;
        sf::Sound menu_down;
        sf::Sound menu_select;
        sf::Sound menu_woosh;

        // Music
        std::shared_ptr<sf::Music> menu_music;
        std::shared_ptr<sf::Music> level_music;
        std::shared_ptr<sf::Music> win_music;
        std::shared_ptr<sf::Music> lose_music;

        // In-game SFX
        sf::Sound jetpack_loop;
        std::vector<sf::Sound> spatial_sounds;

        // Load and store non-spatial sounds.
        void Initialize();

    public:
        // Constructor takes a resource manager so it sounds can be loaded.
        explicit SoundManager(ResourceManager &resource_manager);

        // Build the sounds used in the level view that depend on a location.
        void InitializeSpatialSounds(std::vector<std::shared_ptr<Entity>> &fans,
                                     std::vector<std::shared_ptr<Entity>> &shock_boxes,
                                     std::vector<std::shared_ptr<Entity>> &pressure_sources,
                                     std::vector<std::shared_ptr<Entity>> &walls);

        // Update the listener position (for 3D sound).
        void UpdateListenerPosition(std::shared_ptr<Location> &player_location);

        // Spatial sound controls.
        void StartSpatialSounds();
        void PauseSpatialSounds();
        void StopSpatialSounds();

        // Menu sound controls.
        void MenuScrollUp();
        void MenuScrollDown();
        void MenuSelect();
        void MenuWoosh();

        // Music controls.
        void StartMenuMusic();
        void StopMenuMusic();
        void StartLevelMusic();
        void PauseLevelMusic();
        void StopLevelMusic();
        void StartWinMusic();
        void StopWinMusic();
        void StartLoseMusic();
        void StopLoseMusic();

        // In-game sound controls.
        void StartJetPack();
        void StopJetPack();
    };

}

#endif //GAME_SOUNDMANAGER_H
