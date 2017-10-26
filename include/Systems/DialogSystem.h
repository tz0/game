#ifndef GAME_DIALOGSYSTEM_H
#define GAME_DIALOGSYSTEM_H

#include <vector>
#include <string>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>

namespace tjg {

    class DialogSystem {
    private:
        // Text object to write dialog to.
        sf::Text dialog_box;

        // Vector containing dialog snippets to show, in order.
        std::vector<std::string> dialog_snippets;
        unsigned int dialog_index;

        // Current urgent message to show.
        std::string urgent_message;

        // Timing-related variables.
        float seconds_to_show_dialog;
        float seconds_to_show_urgent_message;
        float seconds_dialog_shown;
        float seconds_urgent_message_shown;

        // Flag to indicate an urgent message is being shown.
        bool showing_urgent_message;
    public:
        // Constructor
        DialogSystem(const sf::Text &dialog_box, std::vector<std::string> &dialog_snippets, float seconds_to_show_dialog);
        // Update the current dialog being shown.
        void UpdateDialog(const sf::Time &elapsed);
        // Show an urgent message.
        void ShowUrgentMessage(std::string message, float seconds_to_show);
    };

}


#endif //GAME_DIALOGSYSTEM_H
