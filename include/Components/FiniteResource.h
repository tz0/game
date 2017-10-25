#ifndef GAME_FINITERESOURCE_H
#define GAME_FINITERESOURCE_H

#include <Component.h>

namespace tjg {

    class FiniteResource : public Component {
    private:
        // Level of the resource to start with.
        float max_level;
        // Current level of the resource remaining.
        float current_level;
    public:
        // Constructor.
        explicit FiniteResource(float max_level);
        // Accessor methods.
        float GetMaxLevel();
        float GetCurrentLevel();
        int GetCurrentLevelAsInt();
        void SetCurrentLevel(float new_level);
        float ExpendResource(float amount);
        bool IsDepleted();
    };

}


#endif //GAME_FINITERESOURCE_H
