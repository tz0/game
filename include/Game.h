
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.h"
#include "chipmunk.h"

#include "Entity.h"
#include "Components/Follower.h"
#include "Components/Gravity.h"
#include "Components/PlayerInput.h"
#include "Components/Location.h"
#include "Components/RigidBody.h"
#include "Components/Sprite.h"
#include "Components/Velocity.h"

class Game
{
  public:

    Game();
    ~Game();
    // Begin the game loop
    void Run();

  private:
    ResourceManager resource_manager;

    sf::RenderWindow window;
    sf::View camera;
    sf::Clock clock;

    sf::Clock fps_clock;
    int fps = 0;
    int frames_drawn = 0;
    bool show_info = false;

    sf::Text info;
    sf::Text hello;

    std::vector<std::shared_ptr<Entity>> characters;

    cpSpace *space;
    cpShape *ground;
    cpShape *leftwall;

    void Update();
    void Draw();
    void HandleEvents();
};

#endif //GAME_H
