
#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H

#include "View.h"

namespace tjg {

    class PlayerView : public View {

    private:
        // Called by the base class Initialize/Update methods respectively
        void initialize();
        void update(const sf::Time);

        void CheckKeys(const sf::Time);
        void HandleWindowEvents();

        sf::RenderWindow window;
        sf::View camera;

        SpriteRenderSystem sprite_render_system;

        sf::Clock fps_clock;
        int fps = 0;
        int frames_drawn = 0;
        bool show_info = false;
        sf::Text info;

        bool running = true;

    public:
        // Constructor
        explicit PlayerView(ResourceManager &resource_manager);

        // Methods
        void Render();
        bool Running();
    };

}

#endif //GAME_PLAYERVIEW_H
