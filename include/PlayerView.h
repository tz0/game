#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H


#include <SFML/Window/Keyboard.hpp>
#include "Systems/SpriteRenderSystem.h"
#include "ResourceManager.h"

namespace tjg {

    class PlayerView {
    private:
        ResourceManager resource_manager;
        SpriteRenderSystem sprite_render_system;
    public:
        // Constructors
        PlayerView(ResourceManager resource_manager, SpriteRenderSystem sprite_render_system);

        // Used for handling key presses
        void keyPressed(sf::Keyboard::Key key);

        // Render
        void render();

        // Accessor methods.
        ResourceManager getResourceManager();
        SpriteRenderSystem getSpriteRenderSystem();
    };

}


#endif //GAME_PLAYERVIEW_H
