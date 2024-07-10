#include "includes/Game.hpp"

int main(void) {
    Game game(1920, 1080, "Odyci");

    sf::Clock clock;
    const float timeStep = 1.0f / FPS;
    float accumulator = 0.0f;

    while (game.isRunning()) {
        sf::Time elapsed = clock.restart();
        accumulator += elapsed.asSeconds();
        game.event();
        while (accumulator >= timeStep) {
            game.update();
            accumulator -= timeStep;
            std::cout << accumulator << std::endl;
        }
        game.display();
    }

    return 0;
}
