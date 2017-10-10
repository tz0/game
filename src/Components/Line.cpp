#include "Components/Line.h"

namespace tjg {
    Line::Line(sf::Vector2f a, sf::Vector2f b) {
        line[0] = a;
        line[1] = b;
    }

    Line::Line(float x1, float y1, float x2, float y2) {
        sf::Vector2f a = sf::Vector2f(x1, y1);
        sf::Vector2f b = sf::Vector2f(x2, y2);
        line[0] = a;
        line[1] = b;
    }

    void Line::Render(sf::RenderTarget &target) {
        target.draw(line, 2, sf::Lines);
    }

    void Line::ConnectComponents() {
        // TODO ?
    }
}