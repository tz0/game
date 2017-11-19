#include "Components/FiniteResource.h"

namespace tjg {

    FiniteResource::FiniteResource(const float max_level) {
        this->max_level = max_level;
        this->current_level = max_level;
    }

    float FiniteResource::GetMaxLevel() {
        return max_level;
    }

    float FiniteResource::GetCurrentLevel() {
        return current_level;
    }

    void FiniteResource::SetCurrentLevel(float new_level) {
        current_level = new_level;
        if (current_level < 0) {
            current_level = 0;
        }
    }

    void FiniteResource::ExpendResource(float amount) {
        current_level -= amount;
        if (current_level < 0) {
            current_level = 0;
        }
    }

    bool FiniteResource::IsDepleted() {
        return current_level <= 0;
    }

    float FiniteResource::GetPercentRemaining() {
        return current_level/max_level;
    }

}
