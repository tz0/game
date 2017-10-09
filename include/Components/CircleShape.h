
#ifndef GAME_CIRCLESHAPE_H
#define GAME_CIRCLESHAPE_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "Components/Location.h"
#include "Entity.h"

namespace tjg {

    class CircleShape : public Component {
        sf::CircleShape circle;
        std::shared_ptr<Location> location;
    public:
        // Constructor
        explicit CircleShape(float radius);
        // Render
        void Render(sf::RenderTarget &target);
        // Size
        float GetSize();
        // Component methods
        void ConnectComponents();
    };

}

#endif //GAME_CIRCLESHAPE_H
