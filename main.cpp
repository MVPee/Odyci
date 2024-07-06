# include "includes/Game.hpp"

int main(void) {

    Game game(800, 800, "Odyci");

    while (game.isRunning()) {
        game.event();
        game.update();
        game.display();
    }
    return 0;
}
