
#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

#include <SFML/Graphics.hpp>

#include "LogicCenter.h"
#include "ResourceManager.h"
#include "Systems/SpriteRenderSystem.h"
#include "View.h"

namespace tjg {

    class PlayerView : public View {
    private:
        LogicCenter &logic_center;
        sf::View camera;
        SpriteRenderSystem sprite_render_system;
        bool running = true;

        void CheckKeys();

        sf::Clock fps_clock;
        int fps = 0;
        int frames_drawn = 0;

        sf::Text info;
        bool show_info = true;

        sf::Text countdown;
        bool show_countdown = true;
        bool countdown_mode_binary = true; // set it to false for a regular decimal timer

    public:
        // Constructor
        explicit PlayerView(ResourceManager &resource_manager, sf::RenderWindow &window, LogicCenter &logic_center);

        // Methods
        void Initialize() override;
        void Render();
        void Update();
        void HandleWindowEvents(sf::Event event) override;
    };

}

#endif //GAME_PLAYERVIEW_H
