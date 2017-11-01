#ifndef GAME_MAINMENUVIEW_H
#define GAME_MAINMENUVIEW_H

#include <SFML/Graphics.hpp>
#include "View.h"
#include "Views/ButtonList.h"

namespace tjg {
    class MainMenuView : public View {
    private:
        sf::Text message;
//        ButtonList button_list;
    public:
        MainMenuView(ResourceManager &resource_manager, sf::RenderWindow &window);
        void Initialize();
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_MAINMENUVIEW_H
