
#ifndef GAME_SENSORSHAPE_H
#define GAME_SENSORSHAPE_H

#include <chipmunk.h>
#include <functional>
#include <utility>

#include "Component.h"

namespace tjg {

    /**
     * SensorShape can be used to associate a Chipmunk shape with a callback to be used for shape queries.
     * The physics system performs a shape query for each entity containing this component, and will provide a pointer
     * to the parent entity through the third argument of the callback (void*).
     *
     * A simple example:
     *
     * my_entity->AddComponent<SensorShape>(my_entity->GetComponent<DynamicBody>->GetShape(), [](cpShape *shape, cpContactPointSet *points, void *entity_ptr){
     *      auto entity = static_cast<Entity*>(entity_ptr);
     *      std::cout << "sensed a shape." << std::endl;
     * }
     */

    class SensorShape : public Component{
    private:
        // shape to check (will be made into a sensor shape)
        cpShape *shape;
        // callback to call for each query result
        std::function<void(cpShape*)> callback;

    public:

        SensorShape(cpShape *shape, std::function<void(cpShape*)> callback);
        void Query(cpSpace *space);

        // Accessors
        cpShape *GetShape();

    };
}


#endif //GAME_SENSORSHAPE_H
