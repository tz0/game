#include "Systems/DialogueSystem.h"

namespace tjg {

    void DialogueSystem::Initialize(sf::Text dialog_box, std::vector<Dialogue> &dialogues, unsigned wrap_width) {
        // Store dialog box reference.
        this->dialogue_box = std::move(dialog_box);

        // Store dialog snippets and the number of seconds to show each snippet.
        this->dialogues = dialogues;

        // Set initial dialog index to 0.
        this->dialogue_index = 0;

        // Set initial text.
        if (!this->dialogues.empty()) {
            auto wrapped_string = wrapText(this->dialogues[dialogue_index].message, wrap_width, *this->dialogue_box.getFont(), this->dialogue_box.getCharacterSize());
            this->dialogue_box.setString(wrapped_string);
            this->seconds_dialogue_shown = 0;
        }

        // Set urgent message flag to false.
        showing_urgent_message = false;

        // Store wrap width.
        this->wrap_width = wrap_width;
    }

    void DialogueSystem::Update(const sf::Time &elapsed) {
        if (showing_urgent_message && seconds_urgent_message_shown <= urgent_message.time_to_show) {
            // If showing an urgent message and need to keep showing it, increment the time it has been shown.
            seconds_urgent_message_shown += elapsed.asSeconds();
        }
        else if (showing_urgent_message) {
            // If showing an urgent message and don't need to show it anymore, switch back to dialog.
            showing_urgent_message = false;
            auto wrapped_string = wrapText(dialogue_before_urgent_message.message, wrap_width, *dialogue_box.getFont(), dialogue_box.getCharacterSize());
            dialogue_box.setString(wrapped_string);
        }
        else if (dialogue_index < dialogues.size() && seconds_dialogue_shown <= dialogues[dialogue_index].time_to_show) {
            // If the current dialog hasn't been shown long enough, just increment the time.
            seconds_dialogue_shown += elapsed.asSeconds();
        }
        else if (dialogue_index < dialogues.size()){
            // Move to the next dialog snippet if there is one.
            dialogue_index++;
            if (dialogue_index < dialogues.size()) {
                // Update the text in the dialog box.
                auto wrapped_string = wrapText(dialogues[dialogue_index].message, wrap_width, *dialogue_box.getFont(), dialogue_box.getCharacterSize());
                dialogue_box.setString(wrapped_string);
                // Reset the time this dialog has been shown.
                seconds_dialogue_shown = 0;
            }
        }
        else {
            // Clear the dialog box if there's nothing to show.
            dialogue_box.setString("");
        }
    }

    void DialogueSystem::ShowUrgentMessage(Dialogue urgent_message) {
        // Reset the time the urgent message has been shown and set the urgent message flag.
        showing_urgent_message = true;
        seconds_urgent_message_shown = 0;
        // Store the urgent message.
        this->urgent_message = urgent_message;
        // Store the old text in the dialog box.
        auto previous_string = dialogue_box.getString();
        if (dialogue_index < dialogues.size()) {
            dialogue_before_urgent_message = dialogues[dialogue_index];
        }
        else {
            dialogue_before_urgent_message = Dialogue("", INT_MAX);
        }
        // Update the text in the dialog box.
        auto wrapped_message = wrapText(urgent_message.message, wrap_width, *dialogue_box.getFont(), dialogue_box.getCharacterSize());
        dialogue_box.setString(wrapped_message);
    }

    sf::Text DialogueSystem::GetDialogueBox() {
        return dialogue_box;
    }

    // Source: https://gist.github.com/LiquidHelium/7858095
    sf::String DialogueSystem::wrapText(sf::String string, unsigned width, const sf::Font &font, unsigned characterSize, bool bold) {
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
