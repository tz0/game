
#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define STATUSBAR_HEIGHT 72

#include <SFML/Graphics.hpp>

#include "LogicCenter.h"
#include "ResourceManager.h"
#include "Systems/SpriteRenderSystem.h"
#include "Systems/DialogSystem.h"
#include "View.h"

namespace tjg {

    class PlayerView : public View {

    private:

        ResourceManager &resource_manager;

        void CheckKeys(const sf::Time &elapsed);
        void HandleWindowEvents();

        sf::RenderWindow window;
        sf::View camera;

        // Sprite render systems.
        SpriteRenderSystem gameview_render_system;
        SpriteRenderSystem statusbar_render_system;

        // FPS display
        sf::Clock fps_clock;
        int fps = 0;
        int frames_drawn = 0;
        sf::Text info;
        bool show_info = false;

        sf::Text win_message;

        bool running = true;

        // Status bar pieces.
        sf::RectangleShape statusbar_background;
        sf::RectangleShape fuel_tank_background;
        sf::RectangleShape oxygen_tank_background;
        sf::RectangleShape dialog_background;
        float statusbar_element_height;
        float statusbar_x_padding;
        float statusbar_y_padding;
        sf::Vector2f trackers_initial_size;
        sf::Vector2f dialog_initial_size;

        // Status bar methods.
        void initializeStatusBar();
        void renderStatusBarBackground();
        void updateStatusBarTrackers();

        // Dialog box pieces.
        sf::Text dialog_box;
        DialogSystem dialog_system;

        // Dialog box methods.
        void initializeDialogSystem(std::vector<std::string> &dialog_snippets, float seconds_to_show_dialog, std::shared_ptr<sf::Font> font);

    public:
        // Constructor
        explicit PlayerView(ResourceManager &resource_manager, LogicCenter &logic_center);

        // Methods
        void Initialize() override;
        void Render();
        void Update(const sf::Time &elapsed);
        bool Running() override;
        void RenderWinMessage(); //TODO: This is a temporary solution
    };

}

#endif //GAME_PLAYERVIEW_H
