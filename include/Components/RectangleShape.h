//
// Created by erik on 9/27/17.
//

#ifndef GAME_RECTANGLESHAPE_H
#define GAME_RECTANGLESHAPE_H

#include "Component.h"
#include "Entity.h"
#include "Components/Location.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace tjg {

    class RectangleShape : public Component {
    private:
        sf::RectangleShape rect;
        std::shared_ptr<Location> location;
    public:
        // Constructor
        explicit RectangleShape(sf::Vector2f size);
        // Size
        const sf::Vector2f & GetSize();
        // Render
        void Render(sf::RenderTarget &target);
        // Component methods
        void ConnectComponents() override;
    };

}

#endif //GAME_RECTANGLESHAPE_H
