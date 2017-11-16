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

        // Sound methods.
        void MenuScrollUp();
        void MenuScrollDown();
    };

}

#endif //GAME_SOUNDMANAGER_H
