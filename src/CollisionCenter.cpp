#include "CollisionCenter.h"

namespace tjg {
    void CollisionCenter::AddHandler(CollisionGroup group1, CollisionGroup group2,
                                     std::function<void(cpArbiter *arb, cpSpace *space)> callback) {

        auto handler = cpSpaceAddCollisionHandler(
            space,
            static_cast<cpCollisionType>(group1),
            static_cast<cpCollisionType>(group2)
        );

        // Check if an identical handler has already been created. If so, display a warning.
        if (callbacks.find(handler) != callbacks.end()) {
            std::cout << "Warning: Overwriting collision handler for groups: "
                      << static_cast<int>(group1) << ", "
                      << static_cast<int>(group2) << "." << std::endl;
        }

        // Insert the callback into the map
        callbacks[handler] = std::move(callback);

        // Assign the callback as user data
        handler->userData = &callbacks[handler];

        // Setup the callback wrapper
        handler->postSolveFunc = [](cpArbiter *arb, cpSpace *space, cpDataPointer f) {
            (*static_cast<std::function<void (cpArbiter*, cpSpace*)>*>(f))(arb, space);
        };
    }
}