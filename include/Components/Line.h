//
// Created by erik on 9/27/17.
//

#ifndef GAME_LINE_H
#define GAME_LINE_H

#include "Component.h"

namespace JPG {

    class Line : public Component {
        sf::Vertex line[2];
    public:
        Line(sf::Vector2f a, sf::Vector2f b) : line{a, b} {}

        Line(float x1, float y1, float x2, float y2) :
                Line(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2)) {}

        void Render(sf::RenderTarget &target) {
            target.draw(line, 2, sf::Lines);
        }

        void ConnectComponents() {}
    };

}

#endif //GAME_LINE_H
