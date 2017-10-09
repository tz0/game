
#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

namespace tjg {

    // Defined in its own header.
    class Entity;

    class Component {
    protected:
        Entity *entity;
        long entity_id;
    public:
        virtual void ConnectComponents() = 0;
        void SetEntity(Entity *entity);
    };

}

#endif //GAME_COMPONENT_H
