#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H


#include <SFML/Window/Keyboard.hpp>
#include <Systems/PlayerControlSystem.h>
#include "Systems/SpriteRenderSystem.h"
#include "ResourceManager.h"

namespace tjg {

    class PlayerView {
    private:
        ResourceManager resource_manager;
        SpriteRenderSystem sprite_render_system;
        PlayerControlSystem player_control_system;
    public:
        // Constructor
        PlayerView(ResourceManager resource_manager);

        // Destructor
        ~PlayerView();

        // Used for handling key presses
        void keyPressed(sf::Keyboard::Key key);

        // Update view
        void update();

        // Render
        void render();

        // Accessor methods.
        ResourceManager getResourceManager();
        SpriteRenderSystem getSpriteRenderSystem();
        PlayerControlSystem getPlayerControlSystem();
    };

}


#endif //GAME_PLAYERVIEW_H
