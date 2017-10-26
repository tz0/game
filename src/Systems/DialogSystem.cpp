#include "Systems/DialogSystem.h"

namespace tjg {

    void DialogSystem::Initialize(sf::Text dialog_box, std::vector<std::string> &dialog_snippets, float seconds_to_show_dialog, unsigned wrap_width) {
        // Store dialog box reference.
        this->dialog_box = std::move(dialog_box);

        // Store dialog snippets and the number of seconds to show each snippet.
        this->dialog_snippets = dialog_snippets;
        this->seconds_to_show_dialog = seconds_to_show_dialog;

        // Set initial dialog index to 0.
        this->dialog_index = 0;

        // Set initial text.
        if (!this->dialog_snippets.empty()) {
            auto wrapped_string = wrapText(this->dialog_snippets[dialog_index], wrap_width, *this->dialog_box.getFont(), this->dialog_box.getCharacterSize());
            this->dialog_box.setString(wrapped_string);
            this->seconds_dialog_shown = 0;
        }

        // Set urgent message flag to false.
        showing_urgent_message = false;

        // Store wrap width.
        this->wrap_width = wrap_width;
    }

    void DialogSystem::Update(const sf::Time &elapsed) {
        if (showing_urgent_message && seconds_urgent_message_shown <= seconds_to_show_urgent_message) {
            // If showing an urgent message and need to keep showing it, increment the time it has been shown.
            seconds_urgent_message_shown += elapsed.asSeconds();
        }
        else if (showing_urgent_message) {
            // If showing an urgent message and don't need to show it anymore, switch back to dialog.
            showing_urgent_message = false;
            dialog_box.setString(dialog_before_urgent_message);
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
                auto wrapped_string = wrapText(dialog_snippets[dialog_index], wrap_width, *dialog_box.getFont(), dialog_box.getCharacterSize());
                dialog_box.setString(wrapped_string);
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
        // Store the old text in the dialog box.
        auto previous_string = dialog_box.getString();
        if (dialog_index < dialog_snippets.size()) {
            auto wrapped_string = wrapText(dialog_snippets[dialog_index], wrap_width, *dialog_box.getFont(), dialog_box.getCharacterSize());
            dialog_before_urgent_message = wrapped_string;
        }
        else {
            dialog_before_urgent_message = "";
        }
        // Update the text in the dialog box.
        auto wrapped_message = wrapText(message, wrap_width, *dialog_box.getFont(), dialog_box.getCharacterSize());
        dialog_box.setString(wrapped_message);
    }

    sf::Text DialogSystem::GetDialogBox() {
        return dialog_box;
    }

    // Source: https://gist.github.com/LiquidHelium/7858095
    sf::String DialogSystem::wrapText(sf::String string, unsigned width, const sf::Font &font, unsigned characterSize, bool bold) {
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
