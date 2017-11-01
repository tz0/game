#ifndef GAME_PLAYERVIEW_H
#define GAME_PLAYERVIEW_H

#define STATUSBAR_HEIGHT 72

#include <SFML/Graphics.hpp>
#include <bitset>

#include "LogicCenter.h"
#include "Systems/SpriteRenderSystem.h"
#include "Systems/DialogSystem.h"
#include "View.h"
#include "Constants.h"

namespace tjg {

    class PlayerView : public View {
    private:

        LogicCenter &logic_center;
        sf::View camera;

        void CheckKeys(const sf::Time &elapsed);
        void HandleWindowEvents();

        // Sprite render systems.
        SpriteRenderSystem playerview_render_system;
        SpriteRenderSystem statusbar_render_system;

        // FPS display
        sf::Clock fps_clock;
        int fps = 0;
        int frames_drawn = 0;
        sf::Text info;
        bool show_info = false;

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
        DialogSystem dialog_system;

        // Dialog box methods.
        void initializeDialogSystem(std::vector<std::string> &dialog_snippets, float seconds_to_show_dialog, std::shared_ptr<sf::Font> font);

    public:
        // Constructor
        explicit PlayerView(ResourceManager &resource_manager, sf::RenderWindow &window, LogicCenter &logic_center);

        // Methods
        void Initialize();
        void Render();

        ViewSwitch HandleWindowEvents(sf::Event event) override;
        void Update(const sf::Time &elapsed);
    };

}

#endif //GAME_PLAYERVIEW_H
