# include "includes/Game.hpp"

int main(void) {

    Game game(1920, 1080, "Odyci");

    while (game.isRunning()) {
        game.event();
        game.update();
        game.display();
    }
    return 0;
}
