
#ifndef GAME_LINE_H
#define GAME_LINE_H

#include "Component.h"

namespace tjg {

    class Line : public Component {
        sf::Vertex line[2] = { };
    public:
        // Constructors
        Line(sf::Vector2f a, sf::Vector2f b);
        Line(float x1, float y1, float x2, float y2);
        // Render line
        void Render(sf::RenderTarget &target);
        // Component methods
        void ConnectComponents() override;
    };

}

#endif //GAME_LINE_H
