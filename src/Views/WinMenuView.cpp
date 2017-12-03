#include "Views/WinMenuView.h"

namespace tjg{
    WinMenuView::WinMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, std::shared_ptr<SoundManager> &sound_manager) :
            View(window, resource_manager, sound_manager) {}


    void WinMenuView::Initialize(const unsigned int level_number) {
        current_level = level_number;
        selection = 0;
        //load fonts
        auto monaco = resource_manager.LoadFont("monaco.ttf");

        auto background_texture = resource_manager.LoadTexture("menu-win.jpg");
        background_sprite.setTexture(*background_texture);
        options = {ViewSwitch {State::PLAYING, current_level + 1}, ViewSwitch {State::PLAYING, 0}, ViewSwitch {State::MAIN_MENU, 0}};

        selection_box_position = sf::Vector2f(WIN_MENU_BOX_X, WIN_MENU_BOX_Y_UP);
        selection_box.setSize(sf::Vector2f(363,43));
        selection_box.setPosition(selection_box_position);
        selection_box.setFillColor(sf::Color::Transparent);
        selection_box.setOutlineColor(sf::Color(255, 255, 255, 255));
        selection_box.setOutlineThickness(2.0f);

        //initialize story snippets
        snippets_background.setPosition(340,180);
        snippets_background.setSize(sf::Vector2f(440,300));
        snippets_background.setFillColor(sf::Color(0, 0, 0, 128));

        snippets.setFont(*monaco);
        snippets.setPosition(360,200);
        snippets.setCharacterSize(14);
        snippets.setFillColor(sf::Color(255, 255, 255, 255));
        LoadSnippets();
        auto wrappedString = wrapText(snippet_array[level_number].string_value(), 400, *snippets.getFont(), snippets.getCharacterSize());
        snippets.setString(wrappedString);

        // Stop level sounds.
        sound_manager->StopLevelSounds();
        sound_manager->StopSpatialSounds();
        sound_manager->ClearSpatialSounds();
        sound_manager->StopLevelMusic();

        // Start music.
        sound_manager->StartWinMusic();
    }

    void WinMenuView::Update() {
        selection_box.setPosition(selection_box_position);
    }

    void WinMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(background_sprite);
        window.draw(selection_box);
        window.draw(snippets_background);
        window.draw(snippets);
        window.display();
    }

    ViewSwitch WinMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 0) {
                            selection -= 1;
                            selection_box_position.y -= WIN_MENU_BOX_SHIFT;
                        } else {
                            selection = WIN_MENU_OPTIONS;
                            selection_box_position.y = WIN_MENU_BOX_Y_LOW;
                        }
                        // Play scroll sound.
                        sound_manager->MenuScrollUp();
                        break;
                    case sf::Keyboard::Down:
                        if (selection < WIN_MENU_OPTIONS) {
                            selection += 1;
                            selection_box_position.y += WIN_MENU_BOX_SHIFT;
                        } else {
                            selection = 0;
                            selection_box_position.y = WIN_MENU_BOX_Y_UP;
                        }
                        // Play scroll sound.
                        sound_manager->MenuScrollDown();
                        break;
                    case sf::Keyboard::Return:
                        // Play selection sound.
                        sound_manager->MenuSelect();
                        sound_manager->StopWinMusic();
                        return options[selection];
                    case sf::Keyboard::Escape:
                        sound_manager->MenuSelect();
                        sound_manager->StopWinMusic();
                        return options[2];
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
        return ViewSwitch {State::CONTINUE, 0};
    }

    void WinMenuView::LoadSnippets() {
        std::string err, file_address = "..//data//snippet.json";
        std::cout << "Reading snippets from " << file_address << std::endl;

        std::ifstream in(file_address);
        std::string raw_snippet((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        const auto parse_result = json11::Json::parse(raw_snippet, err);
        if (parse_result.is_array())
            snippet_array = parse_result.array_items();
    }

    // Source: https://gist.github.com/LiquidHelium/7858095
    sf::String WinMenuView::wrapText(sf::String string, unsigned width, const sf::Font &font, unsigned characterSize, bool bold) {
        unsigned currentOffset = 0;
        bool firstWord = true;
        std::size_t wordBegining = 0;

        for (std::size_t pos(0); pos < string.getSize(); ++pos) {
            auto currentChar = string[pos];
            if (currentChar == '\n'){
                currentOffset = 0;
                firstWord = true;
                continue;
            } else if (currentChar == ' ') {
                wordBegining = pos;
                firstWord = false;
            }

            auto glyph = font.getGlyph(currentChar, characterSize, bold);
            currentOffset += glyph.advance;

            if (!firstWord && currentOffset > width) {
                pos = wordBegining;
                string[pos] = '\n';
                firstWord = true;
                currentOffset = 0;
            }
        }

        return string;
    }

}