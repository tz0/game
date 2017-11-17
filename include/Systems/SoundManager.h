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

        // Load and store sounds.
        void Initialize();
    public:
        // Constructor takes a resource manager so it sounds can be loaded.
        explicit SoundManager(ResourceManager &resource_manager);

        // Play menu sounds.
        void MenuScrollUp();
        void MenuScrollDown();
        void MenuSelect();
        void MenuWoosh();

        // Play in-game sounds.

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
    };

}

#endif //GAME_SOUNDMANAGER_H
