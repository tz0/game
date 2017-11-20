#ifndef GAME_LEVELVIEW_H
#define GAME_LEVELVIEW_H

#include <sstream>
#include <iomanip>

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "LogicCenter.h"
#include "Systems/DialogueSystem.h"
#include "Systems/SpriteRenderSystem.h"
#include "Systems/ParticleSystem.h"
#include "Systems/PhysicsParticleSystem.h"
#include "View.h"

namespace tjg {

    class LevelView : public View {
    private:

        LogicCenter &logic_center;
        sf::View camera;

        void CheckKeys(const sf::Time &elapsed);

        // Sprite render systems.
        SpriteRenderSystem main_render_system;
        SpriteRenderSystem statusbar_render_system;

        PhysicsParticleSystem fan_particle_system;
        PhysicsParticleSystem shockbox_particle_system;
        ParticleSystem jetpack_flame_system;

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
        sf::RectangleShape dialogue_background;
        sf::Text fuel_numeric_text;
        sf::Text oxygen_numeric_text;
        float statusbar_element_height;
        float statusbar_x_padding;
        float statusbar_y_padding;
        sf::Vector2f trackers_initial_size;
        sf::Vector2f dialog_initial_size;
        sf::Clock statusbar_blinker;
        sf::Time statusbar_blinktime = sf::seconds(0.5);

        // Status bar methods.
        void InitializeStatusBar(std::shared_ptr<sf::Font> hud_font);
        void RenderStatusBar();
        void UpdateStatusBarTrackers();

        // Dialogue box pieces.
        DialogueSystem dialogue_system;

        // Dialogue box methods.
        void InitializeDialogueSystem(std::vector<Dialogue> &dialogues, std::shared_ptr<sf::Font> font);

    public:
        // Constructor
        explicit LevelView(sf::RenderWindow &window, ResourceManager &resource_manager, std::shared_ptr<SoundManager> &sound_manager, LogicCenter &logic_center);

        // Methods
        void Initialize();
        void Render();

        ViewSwitch HandleWindowEvents(sf::Event event) override;
        void Update(const sf::Time &elapsed);
    };

}

#endif //GAME_LEVELVIEW_H
