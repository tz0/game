#include "CollisionCenter.h"

namespace tjg {
    void CollisionCenter::AddHandler(CollisionGroup group1, CollisionGroup group2,
                                     std::function<cpBool(cpArbiter *arb, cpSpace *space)> callback) {

        auto handler = cpSpaceAddCollisionHandler(
            space,
            static_cast<cpCollisionType>(group1),
            static_cast<cpCollisionType>(group2)
        );

        handlers.emplace_back(std::pair<cpCollisionHandler*, std::function<cpBool(cpArbiter *, cpSpace *)>>(
                handler, std::move(callback)
        ));
        handler->userData = &handlers.back().second;
        handler->beginFunc = [](cpArbiter *arb, struct cpSpace *space, cpDataPointer f) -> cpBool {
            return (*static_cast<std::function<cpBool (cpArbiter*, cpSpace*)>*>(f))(arb, space);
        };

    }
}