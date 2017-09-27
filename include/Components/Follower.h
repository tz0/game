//
// Created by erik on 9/23/17.
//

#ifndef GAME_FOLLOWER_H
#define GAME_FOLLOWER_H

#include "Components/Velocity.h"
#include "Components/Location.h"

class Follower : public Component {
private:
    std::shared_ptr<Velocity> velocity;
    std::shared_ptr<Location> myLocation;
    std::shared_ptr<Location> targetLocation;
    std::weak_ptr<Entity> target;
public:
    Follower(std::weak_ptr<Entity> target){
        this->target = target;
    }
    void Update(sf::Time elapsed) {
            velocity->velocity.x += (targetLocation->position.x - myLocation->position.x) * 0.001f * elapsed.asSeconds();
            velocity->velocity.y += (targetLocation->position.y - myLocation->position.y) * 0.001f * elapsed.asSeconds();
    }
    void ConnectComponents() {
        velocity = entity->GetComponent<Velocity>();
        if (auto tar = target.lock()){
            targetLocation = tar->GetComponent<Location>();
        }
        myLocation = entity->GetComponent<Location>();
    }
};

#endif //GAME_FOLLOWER_H
