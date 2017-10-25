
#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

#include <SFML/Graphics.hpp>

#include "LogicCenter.h"
#include "ResourceManager.h"
#include "Systems/SpriteRenderSystem.h"
#include "View.h"
#include "Views/StateManager.h"

namespace tjg {

    class PlayerView : public View {

    private:

        ResourceManager &resource_manager;
        StateManager state_manager;

        void CheckKeys();
        void HandleWindowEvents();

        sf::RenderWindow window;
        sf::View camera;

        SpriteRenderSystem sprite_render_system;

        sf::Clock fps_clock;
        int fps = 0;
        int frames_drawn = 0;

        sf::Text info;
        bool show_info = true;

        sf::Text countdown;
        bool show_countdown = true;
        bool countdown_mode_binary = true; // set it to false for a regular decimal timer

        sf::Text win_message;

        bool running = true;

    public:
        // Constructor
        explicit PlayerView(ResourceManager &resource_manager, LogicCenter &logic_center);

        // Methods
        void Initialize() override;
        void Render();
        void Update();
        bool Running() override;
        void RenderWinMessage(); //temp
    };

}

#endif //GAME_PLAYERVIEW_H
