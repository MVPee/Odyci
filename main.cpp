# include <iostream>
# include "includes/Game.hpp"

int main()
{
    Game game(800, 600, "Odyci");

    while (game.isRunning()) {
        game.update();
        game.render();
    }

    return 0;
}
