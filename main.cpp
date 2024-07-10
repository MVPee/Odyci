#include "includes/Game.hpp"

int main(void) {
    Game game(1920, 1080, "Odyci");

    sf::Clock clock;
    const float timeStep = 1.0f / FPS;
    float accumulator = 0.0f;

    sf::Clock fpsClock;
    float fpsTimeAccumulator = 0.0f;

    while (game.isRunning()) {
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        accumulator += deltaTime;
        fpsTimeAccumulator += deltaTime;

        // Handle events
        game.event();

        while (accumulator >= timeStep) {
            game.update();
            accumulator -= timeStep;
        }

        // Update FPS counter
        float fpsElapsedTime = fpsClock.restart().asSeconds();
        game.updateFps(fpsElapsedTime);
        fpsTimeAccumulator = 0.0f;

        // Render
        game.display();
    }

    return 0;
}
