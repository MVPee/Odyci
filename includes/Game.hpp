#ifndef GAME_HPP
# define GAME_HPP

# include <iostream>
# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include <SFML/Window.hpp>
# include <SFML/Audio.hpp>
# include <SFML/Network.hpp>
# include "Map.hpp"

class Game {
    private:
        sf::RenderWindow    *_window;
        sf::VideoMode       _screen;
        sf::Event           _event;
        Map                 *_map;
    public:
        Game(int width, int height, std::string name);
        ~Game();

        bool isRunning();
        void update();
        void render();
};

#endif