
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <chipmunk.h>

#include <EventManager.h>
#include <Event.h>

#include <ResourceManager.h>

#include <Entity.h>
#include <EntityFactory.h>

#include <Components/Appendage.h>
#include <Components/DynamicBody.h>
#include <Components/Location.h>
#include <Components/Sprite.h>
#include <Components/StaticSegment.h>

#include <System.h>

namespace tjg {

    class Game {
    public:
        Game();
        ~Game();
        void Run();
    private:
        cpSpace *space;

        ResourceManager resource_manager;
        EventManager event_manager;
        EntityFactory entity_factory;

        SpriteRenderSystem sprite_render_system;

        sf::RenderWindow window;
        sf::View camera;
        sf::Clock clock;

        sf::Clock fps_clock;
        int fps = 0;
        int frames_drawn = 0;
        bool show_info = false;

        sf::Text info;

        std::vector<std::shared_ptr<Entity>> entities;
        std::shared_ptr<Entity> tech17;

        void Update();

        void Draw();

        void HandleEvents();
    };
}
#endif //GAME_H
