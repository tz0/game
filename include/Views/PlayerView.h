
#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H

#include "View.h"

namespace tjg {

    class PlayerView : public View {

    private:
        // Called by the base class Initialize/Update methods respectively
        void initialize() override;
        void update(sf::Time elapsed) override;

        void CheckKeys();
        void HandleWindowEvents();

        sf::RenderWindow window;
        sf::View camera;

        SpriteRenderSystem sprite_render_system;

        sf::Clock fps_clock;
        int fps = 0;
        int frames_drawn = 0;
        bool show_info = true;
        sf::Text info;

        bool running = true;

    public:
        // Constructor
        explicit PlayerView(ResourceManager &resource_manager);

        // Methods
        void Render();
        bool Running() override;
    };

}

#endif //GAME_PLAYERVIEW_H
