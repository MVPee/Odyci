#include "includes/Game.hpp"

int main(void) {
    Game game(1920, 1080, "Odyci");

    sf::Clock clock;
    const float timeStep = 1.0f / FPS; // Fixed update rate
    float accumulator = 0.0f;

    while (game.isRunning()) {
        // Measure elapsed time and add it to the accumulator
        sf::Time elapsed = clock.restart();
        accumulator += elapsed.asSeconds();

        // Handle events
        game.event();

        // Update game logic in fixed steps
        while (accumulator >= timeStep) {
            game.update(); // Fixed timestep update
            accumulator -= timeStep;
            std::cout << accumulator << std::endl;
        }

        // Render as often as possible
        game.display();
    }

    return 0;
}
