#include "Systems/DialogSystem.h"

namespace tjg {

    void DialogSystem::Initialize(sf::Text dialog_box, std::vector<std::string> &dialog_snippets, float seconds_to_show_dialog) {
        // Store dialog box reference.
        this->dialog_box = std::move(dialog_box);

        // Store dialog snippets and the number of seconds to show each snippet.
        this->dialog_snippets = dialog_snippets;
        this->seconds_to_show_dialog = seconds_to_show_dialog;

        // Set initial dialog index to 0.
        this->dialog_index = 0;

        // Set initial text.
        if (!this->dialog_snippets.empty()) {
            auto first_string = this->dialog_snippets[0];
            this->dialog_box.setString(first_string);
            this->seconds_dialog_shown = 0;
        }

        // Set urgent message flag to false.
        showing_urgent_message = false;
    }

    void DialogSystem::Update(const sf::Time &elapsed) {
        if (showing_urgent_message && seconds_urgent_message_shown <= seconds_to_show_urgent_message) {
            // If showing an urgent message and need to keep showing it, increment the time it has been shown.
            seconds_urgent_message_shown += elapsed.asSeconds();
        }
        else if (showing_urgent_message) {
            // If showing an urgent message and don't need to show it anymore, switch back to dialog.
            showing_urgent_message = false;
            dialog_box.setString(dialog_snippets[dialog_index]);
        }
        else if (seconds_dialog_shown <= seconds_to_show_dialog) {
            // If the current dialog hasn't been shown long enough, just increment the time.
            seconds_dialog_shown += elapsed.asSeconds();
        }
        else if (dialog_index < dialog_snippets.size()){
            // Move to the next dialog snippet if there is one.
            dialog_index++;
            if (dialog_index < dialog_snippets.size()) {
                // Update the text in the dialog box.
                dialog_box.setString(dialog_snippets[dialog_index]);
                // Reset the time this dialog has been shown.
                seconds_dialog_shown = 0;
            }
        }
        else {
            // Clear the dialog box if there's nothing to show.
            dialog_box.setString("");
        }
    }

    void DialogSystem::ShowUrgentMessage(std::string message, float seconds_to_show) {
        // Reset the time the urgent message has been shown and set the urgent message flag.
        showing_urgent_message = true;
        seconds_urgent_message_shown = 0;
        // Store the amount of time to show this urgent message.
        seconds_to_show_urgent_message = seconds_to_show;
        // Update the text in the dialog box.
        dialog_box.setString(message);
    }

    sf::Text DialogSystem::GetDialogBox() {
        return dialog_box;
    }

}
