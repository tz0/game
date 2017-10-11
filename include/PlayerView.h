#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H


#include <SFML/Window/Keyboard.hpp>
#include <Systems/PlayerControlSystem.h>
#include "Systems/SpriteRenderSystem.h"
#include "ResourceManager.h"
#include "EntityFactory.h"
#include "EventManager.h"

namespace tjg {

    class PlayerView {
    private:
        std::shared_ptr<ResourceManager> resource_manager;
        EventManager event_manager;

        EntityFactory entity_factory;

        SpriteRenderSystem sprite_render_system;
        PlayerControlSystem player_control_system;

        sf::RenderWindow window;
        sf::View camera;
        sf::Clock clock;

        // Build the player character and add it to the appropriate systems. To be used in constructor or an init() method.
        void InitPlayerCharacter();
    public:
        // Constructor
        explicit PlayerView(std::shared_ptr<ResourceManager> resource_manager_ptr);

        // Destructor
        ~PlayerView();

        // Used for handling key presses
        void KeyPressed(sf::Keyboard::Key key);

        // Handle events.
        void HandleEvents();

        // Update view
        void Update();

        // Draw the frame
        void Render();

        // Accessor methods.
        ResourceManager GetResourceManager();
        SpriteRenderSystem GetSpriteRenderSystem();
        PlayerControlSystem GetPlayerControlSystem();
    };

}


#endif //GAME_PLAYERVIEW_H
