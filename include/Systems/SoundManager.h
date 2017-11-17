#ifndef GAME_SOUNDMANAGER_H
#define GAME_SOUNDMANAGER_H

#include <ResourceManager.h>
#include "System.h"

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
        std::vector<sf::Sound> fan_sounds;
        std::vector<sf::Sound> shock_box_sounds;
        std::vector<sf::Sound> pressure_source_sounds;
        std::vector<sf::Sound> lethal_wall_sounds;

        // Load and store sounds.
        void Initialize();

    public:
        // Constructor takes a resource manager so it sounds can be loaded.
        explicit SoundManager(ResourceManager &resource_manager);

        // Build the sounds used in the level view that depend on a location.
        void InitializeSpatialSounds(std::vector<std::shared_ptr<Entity>> fans,
                                     std::vector<std::shared_ptr<Entity>> shock_boxes,
                                     std::vector<std::shared_ptr<Entity>> pressure_sources,
                                     std::vector<std::shared_ptr<Entity>> walls);

        // Update the listener position (for 3D sound).
        void UpdateListenerPosition(std::shared_ptr<Location> &player_location);

        // Play menu sounds.
        void MenuScrollUp();
        void MenuScrollDown();
        void MenuSelect();
        void MenuWoosh();

        // Play music.
        void StartMenuMusic();
        void StopMenuMusic();
        void StartLevelMusic();
        void PauseLevelMusic();
        void StopLevelMusic();
        void StartWinMusic();
        void StopWinMusic();
        void StartLoseMusic();
        void StopLoseMusic();

        // Play in-game sounds.
        void StartJetPack();
        void StopJetPack();
    };

}

#endif //GAME_SOUNDMANAGER_H
