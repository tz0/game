#include "Components/SensorShape.h"

namespace tjg {
    SensorShape::SensorShape(cpShape *shape, std::function<void(cpShape*)> callback) :
        shape(shape),
        callback(std::move(callback)) {

        // Prevents the shape from causing collisions
        cpShapeSetSensor(shape, cpTrue);
    }

    void SensorShape::Query(cpSpace *space) {
        // Create a capture-less lambda which casts the void* user_data to the correct function type
        // And call it with the shape pointer.
        auto callback_wrapper = [](cpShape *shape, cpContactPointSet *points, void *f){
            (void)points;
            (*static_cast<std::function<void(cpShape*)>*>(f))(shape);
        };

        // Pass the "actual" callback as the user_data pointer, to allow callbacks with captures to be used.
        cpSpaceShapeQuery(space, shape, callback_wrapper, &callback);
    }

    // Accessors
    cpShape *SensorShape::GetShape() {
        return shape;
    };

}
