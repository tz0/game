
#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

namespace tjg {

    class Entity;

    class Component {
    protected:
        Entity *entity;
        long entity_id;
    public:
        virtual void ConnectComponents() = 0;

        void SetEntity(Entity *entity) {
            this->entity = entity;
        }
    };

}
#endif //GAME_COMPONENT_H
