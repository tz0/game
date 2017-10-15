
#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include <vector>

#include "Component.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

namespace tjg {

    class Sprite : public Component {
    private:
        // Contains the SFML sprite object(s)
        std::vector<sf::Sprite> frames;

        // Tracking animation
        unsigned int current_frame = 0;
        sf::Clock animation_clock;
        // time between frames, in milliseconds
        int frame_delay;
        bool playing = false;
        bool loop = true;

        // Used by SpriteRenderSystem to order sprites (lower values are drawn before higher values)
        int layer;
    public:
        // Constructor
        explicit Sprite(sf::Sprite, int layer = 0);
        Sprite(std::vector<sf::Sprite> frames, int frame_delay, int layer = 0);

        // Sprite methods
        /**
         * @return the sprite associated with the current frame of animation
         */
        sf::Sprite & GetSprite();

        /**
         * Sets all associated sprites to be exactly the specified size in pixels
         * @param size
         */
        void SetSize(sf::Vector2f size);

        /**
         * @param frame of animation desired
         * @return the sprite associated with the specified frame of animation
         */
        sf::Sprite & GetSprite(unsigned int frame);

        /**
         * @return the SFML bounds for the current frame of animation
         */
        sf::FloatRect GetBounds();

        /**
         * Play the animation
         * @param loop whether the animation should loop or stop after playing once.s
         */
        void Play(bool loop = true);

        /**
         * Pause the animation.
         */
        void Pause();

        /**
         * @return the sprite's sorting layer
         */
        int GetLayer();
    };
}
#endif //GAME_SPRITE_H
