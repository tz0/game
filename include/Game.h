
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "chipmunk.h"

#include "EventManager.h"
#include "Event.h"

#include "ResourceManager.h"

#include "Entity.h"
#include "Components/Line.h"
#include "Components/Location.h"
#include "Components/RigidBody.h"
#include "Components/Sprite.h"
#include "Components/StaticSegment.h"

class Game
{
  public:

    Game();
    ~Game();
    // Begin the game loop
    void Run();

  private:
    ResourceManager resource_manager;
    EventManager event_manager;



    sf::RenderWindow window;
    sf::View camera;
    sf::Clock clock;

    sf::Clock fps_clock;
    int fps = 0;
    int frames_drawn = 0;
    bool show_info = false;

    sf::Text info;
    sf::Text instructions;
    int targetedEntity = 0;

    std::vector<std::shared_ptr<Entity>> entities;

    cpSpace *space;

    void Update();
    void Draw();
    void HandleEvents();
};

#endif //GAME_H
