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

    int FiniteResource::GetCurrentLevelAsInt() {
        return int(this->current_level);
    }

    void FiniteResource::SetCurrentLevel(float new_level) {
        this->current_level = new_level;
    }

    float FiniteResource::ExpendResource(float amount) {
        this->current_level -= amount;
        return this->current_level;
    }

    bool FiniteResource::IsDepleted() {
        return current_level <= 0;
    }

}
