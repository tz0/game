#include <iostream>

#include "Game.h"


// TODO:
// Create a System class which user can derive from and create systems that update
// components.
// Has a "AddEntity" method which
// 1. Verifies that the specified entity contains the required components
// 2. Adds it to a vector to use later
// 3. Provides a facility for disabling/removing entities
// These systems are in charge of updating the various components of an entity
//
// Example: a movement system, which requires components have position+velocity
// this system would allow the position to be updated based on velocity
//
// this removes the need for components themselves to update data, also removing
// the need for components to be aware of eachother. (i.e. no more ConnectComponents)

Game::Game() :
        resource_manager("media"),
        window(sf::VideoMode(800, 600, 32), "Game", sf::Style::Titlebar | sf::Style::Close) {

    window.setVerticalSyncEnabled(true);


    space = cpSpaceNew();
    cpSpaceSetGravity(space, cpv(0, 100));
}

Game::~Game() {
    cpSpaceFree(space);
}

void Game::Run() {
    auto font = resource_manager.LoadFont("from_cartoon_blocks/FromCartoonBlocks.ttf");
    auto tex = resource_manager.LoadTexture("female_tilesheet.png");

    //
    // Example of event system registering an event
    //
    event_manager.RegisterListener<KeyPress>([&](KeyPress &key) {
        switch (key.GetKey()) {
            case sf::Keyboard::Left:
                targetedEntity--;
                break;
            case sf::Keyboard::Right:
                targetedEntity++;
                break;
            default:
                break;
        }
        if (targetedEntity < 0) targetedEntity = static_cast<int>(entities.size()) - 1;
        if (targetedEntity > static_cast<int>(entities.size()) - 1) targetedEntity = 0;
    });

    // Set up a ground to prevent the characters from falling forever
    auto ground = std::make_shared<Entity>();
    ground->AddComponent<Location>(400, 600);
    ground->AddComponent<StaticSegment>(space, 0, 600, 800, 500);
    ground->AddComponent<Line>(0, 600, 800, 500);
    entities.push_back(ground);

    auto leftwall = std::make_shared<Entity>();
    leftwall->AddComponent<Location>(0, 300);
    leftwall->AddComponent<StaticSegment>(space, 0, 0, 0, 600);
    leftwall->AddComponent<Line>(0, 0, 0, 600);
    entities.push_back(leftwall);

    sf::Sprite girl;
    girl.setTexture(*tex);
    girl.setTextureRect(sf::IntRect(1, 12, 70, 91));

    // Create many character's for testing purposes
    for (auto i = 0; i < 20; ++i) {
        auto character = std::make_shared<Entity>();
        character->AddComponent<Location>();
        character->AddComponent<Sprite>(girl);
        character->AddComponent<RigidBody>(space, floor(i / 4) * 100 + 50, 100 * (i % 4), 1,
                                           girl.getGlobalBounds().width,
                                           girl.getGlobalBounds().height);
        character->ConnectComponents();
        entities.push_back(character);
    }

    info.setFont(*font);
    info.setStyle(sf::Text::Bold);
    info.setCharacterSize(24);

    instructions.setFont(*font);
    instructions.setStyle(sf::Text::Bold);
    instructions.setCharacterSize(35);
    instructions.setPosition(100, 50);
    instructions.setString("Use the arrow keys to cycle camera's\nfocus through the entities");


    camera.setCenter(400, 300);
    camera.setSize(800, 600);

    while (window.isOpen()) {
        Draw();
        Update();
        HandleEvents();
    }

}

void Game::HandleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed: {
                //
                // Example of event system triggering an event
                //
                event_manager.Fire<KeyPress>(event.key.code);

                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::F1:
                        show_info = !show_info;
                        break;

                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
    }
}

void Game::Update() {
    sf::Time elapsed = clock.restart();

    //
    // Update all of the entities' components
    //
    for (auto entity : entities) {
        auto rigidbody = entity->GetComponent<RigidBody>();
        if (rigidbody) rigidbody->Update();
    }

    //
    // Example of moving the camera location
    //
    camera.setCenter(camera.getCenter() * 0.9f + entities[targetedEntity]->GetComponent<Location>()->position * 0.1f);

    cpSpaceStep(space, elapsed.asSeconds() * 2);
}

void Game::Draw() {
    window.clear(sf::Color::Black);
    window.setView(camera);

    // Drawing to the camera view
    for (auto &entity : entities) {
        auto spriteComponent = entity->GetComponent<Sprite>();
        if (spriteComponent) spriteComponent->Render(window);

        auto lineComponent = entity->GetComponent<Line>();
        if (lineComponent) lineComponent->Render(window);

    }


    // Drawing that should take place separate from the "camera" should go below here.
    window.setView(window.getDefaultView());

    window.draw(instructions);

    if (show_info) {
        info.setString(std::to_string(fps) + " FPS");
        window.draw(info);
    }

    window.display();

    // Count FPS
    frames_drawn++;
    if (fps_clock.getElapsedTime().asSeconds() > 1.0f) {
        fps_clock.restart();
        fps = frames_drawn;
        frames_drawn = 0;
    }
}
