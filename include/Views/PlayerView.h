#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H

#include <SFML/Graphics.hpp>
#include <bitset>

#include "LogicCenter.h"
#include "Systems/SpriteRenderSystem.h"
#include "View.h"
#include "Constants.h"

namespace tjg {

    class PlayerView : public View {
    private:
        LogicCenter &logic_center;
        sf::View camera;
        SpriteRenderSystem sprite_render_system;

        void CheckKeys();

        sf::Clock fps_clock;
        int fps = 0;
        int frames_drawn = 0;

        sf::Text info;
        bool show_info = true;

        sf::Text countdown;
        bool show_countdown = true;
        bool countdown_mode_binary = false; // set it to false for a regular decimal timer

    public:
        // Constructor
        explicit PlayerView(ResourceManager &resource_manager, sf::RenderWindow &window, LogicCenter &logic_center);

        // Methods
        void Initialize() override;
        void Render();
        void Update();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };

}

#endif //GAME_PLAYERVIEW_H
