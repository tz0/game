
#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u
#define STATUSBAR_HEIGHT 72u

#include <SFML/Graphics.hpp>

#include "LogicCenter.h"
#include "ResourceManager.h"
#include "Systems/SpriteRenderSystem.h"
#include "View.h"

namespace tjg {

    class PlayerView : public View {

    private:

        ResourceManager &resource_manager;

        void CheckKeys();
        void HandleWindowEvents();

        sf::RenderWindow window;
        sf::View camera;

        SpriteRenderSystem sprite_render_system;

        // FPS display
        sf::Clock fps_clock;
        int fps = 0;
        int frames_drawn = 0;
        sf::Text info;
        bool show_info = false;

        sf::Text win_message;

        bool running = true;

        // Status bar pieces.
        sf::Text countdown;
        bool show_countdown = true;

        // Render status bar.
        void renderStatusBar();

    public:
        // Constructor
        explicit PlayerView(ResourceManager &resource_manager, LogicCenter &logic_center);

        // Methods
        void Initialize() override;
        void Render();
        void Update();
        bool Running() override;
        void RenderWinMessage(); //TODO: This is a temporary solution
    };

}

#endif //GAME_PLAYERVIEW_H
