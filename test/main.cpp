#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define SPEED 3

int main(void) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "test", sf::Style::Close | sf::Style::Titlebar);
    sf::Event event;

    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::Sprite block;

    if (!texture.loadFromFile("../rsrcs/assets/image.png", sf::IntRect(0, 0, 8, 8))) {
        std::cerr << "Error loading texture" << std::endl;
        return -1;
    }
    sprite.setTexture(texture);
    sprite.scale(16, 16);
    sprite.setPosition(0, 0);

    block.setTexture(texture);
    block.scale(16, 16);
    block.setPosition(window.getSize().x/2 - block.getGlobalBounds().height/2, window.getSize().y/2 - block.getGlobalBounds().width/2);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Left)
                    moveLeft = true;
                if (event.key.code == sf::Keyboard::Right)
                    moveRight = true;
                if (event.key.code == sf::Keyboard::Down)
                    moveDown = true;
                if (event.key.code == sf::Keyboard::Up)
                    moveUp = true;
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Left)
                    moveLeft = false;
                if (event.key.code == sf::Keyboard::Right)
                    moveRight = false;
                if (event.key.code == sf::Keyboard::Down)
                    moveDown = false;
                if (event.key.code == sf::Keyboard::Up)
                    moveUp = false;
            }
        }

        // Update the sprite position
        sf::FloatRect nextPos = sprite.getGlobalBounds();
        bool canMoveUp = true, canMoveDown = true, canMoveLeft = true, canMoveRight = true;

        if (moveUp) {
            nextPos.top -= SPEED;
            if (nextPos.intersects(block.getGlobalBounds()) || sprite.getPosition().y - SPEED < 0) {
                canMoveUp = false;
            }
        }

        nextPos = sprite.getGlobalBounds(); // Reset nextPos for next check
        if (moveDown) {
            nextPos.top += SPEED;
            if (nextPos.intersects(block.getGlobalBounds()) || sprite.getPosition().y + sprite.getGlobalBounds().height + SPEED > window.getSize().y) {
                canMoveDown = false;
            }
        }

        nextPos = sprite.getGlobalBounds(); // Reset nextPos for next check
        if (moveLeft) {
            nextPos.left -= SPEED;
            if (nextPos.intersects(block.getGlobalBounds()) || sprite.getPosition().x - SPEED < 0) {
                canMoveLeft = false;
            }
        }

        nextPos = sprite.getGlobalBounds(); // Reset nextPos for next check
        if (moveRight) {
            nextPos.left += SPEED;
            if (nextPos.intersects(block.getGlobalBounds()) || sprite.getPosition().x + sprite.getGlobalBounds().width + SPEED > window.getSize().x) {
                canMoveRight = false;
            }
        }

        if (moveUp && canMoveUp) {
            sprite.move(0, -SPEED);
        }
        if (moveDown && canMoveDown) {
            sprite.move(0, SPEED);
        }
        if (moveLeft && canMoveLeft) {
            sprite.move(-SPEED, 0);
        }
        if (moveRight && canMoveRight) {
            sprite.move(SPEED, 0);
        }

        std::cout << "Y: " << sprite.getPosition().y + sprite.getGlobalBounds().height/2 << "\tX: " << sprite.getPosition().x + sprite.getGlobalBounds().width/2 << std::endl;

        window.clear();
        window.draw(block);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
