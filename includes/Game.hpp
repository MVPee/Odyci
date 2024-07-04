#ifndef GAME_HPP
# define GAME_HPP

# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include <SFML/Window.hpp>
# include <SFML/Audio.hpp>
# include <SFML/Network.hpp>

class Game {
    private:
        sf::RenderWindow    *_window;
        sf::VideoMode       _videoMode;
        sf::Event           _event;
    public:
        Game(int width, int height, std::string name);
        ~Game();

        bool isRunning();
        void update();
        void render();
};

#endif