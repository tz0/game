#include "Components/Sprite.h"

namespace tjg {

    Sprite::Sprite(sf::Sprite sprite, const int layer) {
        // Centers the sprite origin.
        auto bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

        frames = std::vector<sf::Sprite> {sprite};
        this->layer = layer;
    }

    Sprite::Sprite(std::vector<sf::Sprite> frames, const int frame_delay, const int layer) {
        this->frames = std::move(frames);
        this->layer = layer;
        this->frame_delay = frame_delay;
        // Center each frame on the origin
        for (auto &frame : this->frames) {
            auto bounds = frame.getLocalBounds();
            frame.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        }
    }

    sf::Sprite &Sprite::GetSprite() {
        return GetSprite(current_frame);
    }

    sf::Sprite &Sprite::GetSprite(const unsigned int frame) {
        if (playing) {
            // check if clock has passed the frame time
            if (animation_clock.getElapsedTime().asMilliseconds() > frame_delay) {
                // Advance the frame by one
                current_frame++;
                // loop back to the beginning if necessary, and stop if not looping
                if (current_frame > frames.size() - 1) {
                    playing = loop;
                    current_frame = 0;
                }
                animation_clock.restart();
            }
        }
        return frames[frame];
    }

    void Sprite::Play(const bool loop) {
        playing = true;
        this->loop = loop;
        animation_clock.restart();
    }

    void Sprite::Pause() {
        playing = false;
    }

    sf::FloatRect Sprite::GetBounds() {
        return frames[current_frame].getGlobalBounds();
    }

    int Sprite::GetLayer() {
        return layer;
    }

    void Sprite::SetSize(sf::Vector2f size) {
        for (auto &sprite : frames) {
            auto sprite_size = sf::Vector2f(sprite.getTextureRect().width, sprite.getTextureRect().height);
            sprite.setScale(size.x / sprite_size.x, size.y / sprite_size.y);
        }
    }
}
