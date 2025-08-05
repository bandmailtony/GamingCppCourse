#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

struct MovingObject {
    sf::RectangleShape rect;
    sf::Vector2f velocity;
};

// AABB collision detection
bool checkCollision(const sf::RectangleShape& a, const sf::RectangleShape& b) {
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    const int wWidth = 800;
    const int wHeight = 600;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Collisions & Boundaries");
    window.setFramerateLimit(60);

    // === PLAYER ===
    sf::CircleShape player(25);
    player.setFillColor(sf::Color::Green);
    player.setPosition(300.f, 300.f);
    sf::Vector2f playerVelocity(0.f, 0.f);

    // === AUTONOMOUS RECTANGLES ===
    std::vector<MovingObject> movers;
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 3; ++y) {
            MovingObject obj;
            obj.rect.setSize(sf::Vector2f(30.f, 30.f));
            obj.rect.setFillColor(sf::Color(100, 150, 200));
            obj.rect.setPosition(x * 100.f + 50, y * 100.f + 50);
            float speedX = (std::rand() % 100 - 50) / 5.f;
            float speedY = (std::rand() % 100 - 50) / 5.f;
            obj.velocity = sf::Vector2f(speedX, speedY);
            movers.push_back(obj);
        }
    }

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        // === EVENTS ===
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // === PLAYER MOVEMENT ===
        float speed = 200.0f;
        playerVelocity = {0.f, 0.f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) playerVelocity.y -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) playerVelocity.y += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) playerVelocity.x -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) playerVelocity.x += speed;

        player.move(playerVelocity * dt);

        // Clamp player to window bounds
        sf::Vector2f pPos = player.getPosition();
        float radius = player.getRadius();
        if (pPos.x < 0) player.setPosition(0, pPos.y);
        if (pPos.y < 0) player.setPosition(pPos.x, 0);
        if (pPos.x + radius * 2 > wWidth) player.setPosition(wWidth - radius * 2, pPos.y);
        if (pPos.y + radius * 2 > wHeight) player.setPosition(pPos.x, wHeight - radius * 2);

        // === UPDATE MOVERS ===
        for (auto& obj : movers) {
            obj.rect.move(obj.velocity * dt);

            sf::Vector2f pos = obj.rect.getPosition();
            sf::Vector2f size = obj.rect.getSize();

            // Bounce off window edges
            if (pos.x < 0 || pos.x + size.x > wWidth) {
                obj.velocity.x *= -1;
                // Snap inside window
                if (pos.x < 0) obj.rect.setPosition(0, pos.y);
                if (pos.x + size.x > wWidth) obj.rect.setPosition(wWidth - size.x, pos.y);
            }
            if (pos.y < 0 || pos.y + size.y > wHeight) {
                obj.velocity.y *= -1;
                // Snap inside window
                if (pos.y < 0) obj.rect.setPosition(pos.x, 0);
                if (pos.y + size.y > wHeight) obj.rect.setPosition(pos.x, wHeight - size.y);
            }
        }

        // === COLLISIONS BETWEEN MOVERS ===
        for (size_t i = 0; i < movers.size(); ++i) {
            for (size_t j = i + 1; j < movers.size(); ++j) {
                if (checkCollision(movers[i].rect, movers[j].rect)) {
                    sf::Vector2f dir = movers[j].rect.getPosition() - movers[i].rect.getPosition();
                    float dx = dir.x;
                    float dy = dir.y;

                    sf::FloatRect a = movers[i].rect.getGlobalBounds();
                    sf::FloatRect b = movers[j].rect.getGlobalBounds();

                    float overlapX = (a.width / 2 + b.width / 2) - std::abs(dx);
                    float overlapY = (a.height / 2 + b.height / 2) - std::abs(dy);

                    if (overlapX < overlapY) {
                        float push = (overlapX / 2.0f + 0.5f) * (dx < 0 ? -1.f : 1.f);
                        movers[i].rect.move(push, 0.f);
                        movers[j].rect.move(-push, 0.f);

                        movers[i].velocity.x *= -1;
                        movers[j].velocity.x *= -1;
                    } else {
                        float push = (overlapY / 2.0f + 0.5f) * (dy < 0 ? -1.f : 1.f);
                        movers[i].rect.move(0.f, push);
                        movers[j].rect.move(0.f, -push);

                        movers[i].velocity.y *= -1;
                        movers[j].velocity.y *= -1;
                    }
                }
            }
        }

        // === PLAYER COLLISION WITH MOVERS (Optional: just log it for now) ===
        for (auto& obj : movers) {
            if (player.getGlobalBounds().intersects(obj.rect.getGlobalBounds())) {
                std::cout << "Player collided with an object!" << std::endl;
            }
        }

        // === DRAW ===
        window.clear();
        for (auto& obj : movers)
            window.draw(obj.rect);
        window.draw(player);
        window.display();
    }

    return 0;
}
