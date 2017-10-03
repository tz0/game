
#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

namespace JPG {
    class Entity;

    class Component {
    protected:
        Entity *entity;
    public:
        virtual void ConnectComponents() = 0;

        void SetEntity(Entity *entity) {
            this->entity = entity;
        }
    };

}
#endif //GAME_COMPONENT_H
