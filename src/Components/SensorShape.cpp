#include "Components/SensorShape.h"

namespace tjg {

    cpShape* SensorShape::GetShape() {
        return shape;
    }

    cpSpaceShapeQueryFunc SensorShape::GetCallback() {
        return callback;
    }

}
