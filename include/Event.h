
#ifndef GAME_EVENT_H
#define GAME_EVENT_H

class Event {};

class KeyPress : public Event {
private:
    sf::Keyboard::Key key;
public:
    KeyPress(sf::Keyboard::Key key) {
        this->key = key;
    }
    sf::Keyboard::Key GetKey(){
        return this->key;
    }
};

#endif //GAME_EVENT_H
