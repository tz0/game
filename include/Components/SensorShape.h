
#ifndef GAME_SENSORSHAPE_H
#define GAME_SENSORSHAPE_H

#include <chipmunk.h>
#include <functional>
#include <utility>

#include "Component.h"

namespace tjg {
    class SensorShape : public Component{
    private:
        cpShape *shape;
        cpSpaceShapeQueryFunc callback;

    public:

        SensorShape(cpShape *shape, cpSpaceShapeQueryFunc callback) :
            shape(shape),
            callback(std::move(callback)) {

            cpShapeSetSensor(shape, cpTrue);
        }

        cpShape *GetShape();
        cpSpaceShapeQueryFunc GetCallback();

    };
}


#endif //GAME_SENSORSHAPE_H
