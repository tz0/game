
#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

#include "View.h"

namespace tjg {

    class PlayerView : public View {

    private:
        // Called by the base class Initialize/Update methods respectively
        void initialize() override;

        void update() override;

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
        sf::Text win_message;

        sf::Clock countdown_clock;
        sf::Time time_countdown;
        bool show_countdown = true;
        bool countdown_mode_binary = true; // set it to fasle for a regular decimal timer
        sf::Text countdown;
        unsigned int max_countdown = 30;

        bool running = true;

    public:
        // Constructor
        explicit PlayerView(ResourceManager &resource_manager);

        // Methods
        void Render();
        bool Running() override;
        void RenderWinMessage(); //temp
    };

}

#endif //GAME_PLAYERVIEW_H
