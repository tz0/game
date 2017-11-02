#ifndef GAME_DIALOGUESYSTEM_H
#define GAME_DIALOGUESYSTEM_H

#include <vector>
#include <string>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>

namespace tjg {

    // DialogueSnippet struct to hold text and time to show.
    struct Dialogue {
        float time_to_show;
        std::string message;

        inline Dialogue(std::string message, float time_to_show) :
                time_to_show(time_to_show),
                message(std::move(message)){}
    };

    class DialogueSystem {
    private:
        // Text object to write dialog to.
        sf::Text dialog_box;

        // Vector containing dialog snippets to show, in order.
        std::vector<Dialogue> dialogues;
        unsigned int dialog_index;

        // Width to wrap text to.
        unsigned wrap_width;

        // Current urgent message to show.
        std::string urgent_message;
        std::string dialog_before_urgent_message;

        // Timing-related variables.
        float seconds_to_show_urgent_message;
        float seconds_dialog_shown;
        float seconds_urgent_message_shown;

        // Flag to indicate an urgent message is being shown.
        bool showing_urgent_message;

        // Used to wrap text to the proper size.
        sf::String wrapText(sf::String string, unsigned width, const sf::Font &font, unsigned characterSize, bool bold = false);
    public:
        // Initialize dialog system.
        void Initialize(sf::Text dialog_box, std::vector<Dialogue> &dialogues, unsigned wrap_width);
        // Update the current dialog being shown.
        void Update(const sf::Time &elapsed);
        // Show an urgent message.
        void ShowUrgentMessage(std::string message, float seconds_to_show);
        // Get the sf:Text object used to display dialog.
        sf::Text GetDialogueBox();
    };

}


#endif //GAME_DIALOGUESYSTEM_H
