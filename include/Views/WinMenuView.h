#ifndef GAME_WINMENUVIEW_H
#define GAME_WINMENUVIEW_H

#include <SFML/Graphics.hpp>
#include <json11.hpp>
#include <iostream>
#include <fstream>
#include "View.h"

namespace tjg {
    class WinMenuView : public View {
    private:
        sf::Sprite background_sprite;
        sf::RectangleShape selection_box, snippets_background;
        sf::Vector2f selection_box_position;
        unsigned int current_level;
        unsigned int selection = 0;
        std::vector<ViewSwitch> options = {};
        sf::Text snippets;
        json11::Json::array snippet_array;
        void LoadSnippets();
        sf::String wrapText(sf::String string, unsigned width, const sf::Font &font, unsigned characterSize, bool bold = false);

    public:
        WinMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, std::shared_ptr<SoundManager> &sound_manager);
        void Initialize(unsigned int level_number);
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_WINMENUVIEW_H
