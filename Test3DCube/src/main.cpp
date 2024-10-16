#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Vect3D.h"
#include "Text/Text.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "3D Rotating Cube", sf::Style::Close | sf::Style::Resize);

    std::vector<Vec3D> cubeVertices = {
        {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}, // Back face
        {-1, -1, 1},  {1, -1, 1},  {1, 1, 1},  {-1, 1, 1}   // Front face
    };

    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Back face edges
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Front face edges
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Side edges
    };

    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;

    sf::Color colors[] = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::White, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Yellow};
    sf::Color color = sf::Color::White;

    bool canPressButton = true;
    sf::Clock buttonCooldown;
    float cooldownTime = 0.3f;

    Text text1, text2;
    text1.init("Arrows -> for rotate the cube", 20.f, 0.f);
    text2.init("C -> Change color to the cube", 20.f, 30.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) angleY -= 0.00008f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) angleY += 0.00008f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) angleX += 0.00008f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) angleX -= 0.00008f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            if (canPressButton) {
                int rand_value = rand() % 7;
                color = colors[rand_value];

                canPressButton = false;
                buttonCooldown.restart();
            }
        }
        if (!canPressButton) {
            float elapsedTime = buttonCooldown.getElapsedTime().asSeconds();
            if (elapsedTime >= cooldownTime) {
                canPressButton = true;
            }
        }

        window.clear(sf::Color::Black);

        std::vector<sf::Vector2f> projectedVertices;
        for (const Vec3D& vertex : cubeVertices) {
            Vec3D rotated = rotateX(vertex, angleX);
            rotated = rotateY(rotated, angleY);
            rotated = rotateZ(rotated, angleZ);

            sf::Vector2f projected = project(rotated, window.getSize().x, window.getSize().y, 500, 4);
            projectedVertices.push_back(projected);
        }

        for (const auto& edge : edges) {
            sf::Vertex line[] = {
                sf::Vertex(projectedVertices[edge.first], color),
                sf::Vertex(projectedVertices[edge.second], color)
            };
            window.draw(line, 2, sf::Lines);
        }

        window.draw(text1.getText());
        window.draw(text2.getText());
        window.display();
    }

    return 0;
}
