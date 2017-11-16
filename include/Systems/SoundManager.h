#ifndef GAME_SOUNDMANAGER_H
#define GAME_SOUNDMANAGER_H

#include <ResourceManager.h>
#include "System.h"

namespace tjg {

    class SoundManager {
    private:
        ResourceManager &resource_manager;
    public:
        // Constructor takes a resource manager so it sounds can be loaded.
        explicit SoundManager(ResourceManager &resource_manager);

        // Menu sounds.
        void MenuScrollUp();
        void MenuScrollDown();
        void MenuSelect();
        void MenuBack();

        // In-game sounds.

        // Music.
    };

}

#endif //GAME_SOUNDMANAGER_H
