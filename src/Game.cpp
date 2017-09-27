#include <iostream>

#include "Game.h"


Game::Game() :
        resource_manager("media"),
        window(sf::VideoMode(800, 600, 32), "Game", sf::Style::Titlebar | sf::Style::Close) {

    window.setVerticalSyncEnabled(true);
    //window.setMouseCursorVisible(false);

    space = cpSpaceNew();
    ground = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(0, 500), cpv(800, 500), 1);
    leftwall = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(0, 0), cpv(0, 600), 1);

}

Game::~Game() {
    cpShapeFree(ground);
    cpShapeFree(leftwall);
    cpSpaceFree(space);
}

void Game::Run() {
    auto font = resource_manager.LoadFont("from_cartoon_blocks/FromCartoonBlocks.ttf");
    auto tex = resource_manager.LoadTexture("female_tilesheet.png");

    auto balltex = resource_manager.LoadTexture("ball.png");

    event_manager.RegisterListener<KeyPress>([&](Event &keyPress){
        std::cout << static_cast<KeyPress&>(keyPress).GetKey() << " was pressed." << std::endl;
    });

    event_manager.RegisterListener<KeyPress>([&](Event &keyPress){
        std::cout << static_cast<KeyPress&>(keyPress).GetKey() << " got fucked.." << std::endl;
    });

    sf::Sprite girl;
    girl.setTexture(*tex);
    girl.setTextureRect(sf::IntRect(1, 12, 70, 91));



    cpSpaceSetGravity(space, cpv(0, 0));
    cpShapeSetFriction(ground, .7);
    cpShapeSetElasticity(ground, 0.5);
    cpSpaceAddShape(space, ground);
    cpSpaceAddShape(space, leftwall);

    for (auto i = 0; i < 20; ++i) {
        std::shared_ptr<Entity> character = std::make_shared<Entity>();
        character->AddComponent(std::make_shared<Location>());
        character->AddComponent(std::make_shared<Sprite>(girl));
        character->AddComponent(std::make_shared<RigidBody>(space, floor(i / 4) * 100 + 50, 100 * (i % 4), 1,
                                                            girl.getGlobalBounds().width,
                                                            girl.getGlobalBounds().height));
        character->ConnectComponents();
        characters.push_back(character);
    }

    sf::Sprite ballsprite;
    ballsprite.setTexture(*balltex);
    ballsprite.setScale(0.5f, 0.5f);
    std::shared_ptr<Entity> ball = std::make_shared<Entity>();
    ball->AddComponent(std::make_shared<Location>());
    ball->AddComponent(std::make_shared<Sprite>(ballsprite));
    ball->AddComponent(std::make_shared<RigidBody>(space, 300, 300, 10, ballsprite.getGlobalBounds().width / 2.0f));
    ball->ConnectComponents();
    cpShapeSetFriction(ball->GetComponent<RigidBody>()->GetShape(), 2);
    characters.push_back(ball);


    info.setFont(*font);
    info.setFillColor(sf::Color::White);
    info.setCharacterSize(24);
    info.setStyle(sf::Text::Bold);
    info.setPosition(0, 0);

    hello.setFont(*font);
    hello.setFillColor(sf::Color::White);
    hello.setCharacterSize(60);
    hello.setString("Hi!!");
    hello.setStyle(sf::Text::Bold);
    auto bounds = hello.getGlobalBounds();
    hello.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    hello.setPosition(50, 50);

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
                //auto evt = KeyPress(event.key.code);
                event_manager.TriggerEvent<KeyPress>(event.key.code);
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Space: {
                        auto body = characters.back()->GetComponent<RigidBody>()->GetBody();
                        cpBodyApplyImpulseAtLocalPoint(body, cpv(-5000, -800), cpv(0, 0));
                        break;
                    }
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

    for (auto character : characters) {
        auto input = character->GetComponent<PlayerInput>();
        if (input) input->Update(elapsed);

        auto rigidbody = character->GetComponent<RigidBody>();
        if (rigidbody) rigidbody->Update();
    }

    camera.setCenter(camera.getCenter() * 0.9f + characters.back()->GetComponent<Location>()->position * 0.1f);
    //camera.setRotation(characters.back()->GetComponent<Location>()->rotation);


    cpSpaceStep(space, elapsed.asSeconds() * 2);

}

void Game::Draw() {
    window.clear(sf::Color::Black);
    window.setView(camera);

    for (auto &character : characters) {
        character->GetComponent<Sprite>()->Render(window);
    }

    sf::Vertex floor[] = {
        sf::Vertex(sf::Vector2f(0, 500)),
        sf::Vertex(sf::Vector2f(800, 500))
    };
    window.draw(floor, 2, sf::Lines);
    sf::Vertex leftwall[] = {
            sf::Vertex(sf::Vector2f(0, 0)),
            sf::Vertex(sf::Vector2f(0, 600))
    };
    window.draw(leftwall, 2, sf::Lines);

    window.setView(window.getDefaultView());

    window.draw(hello);

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
