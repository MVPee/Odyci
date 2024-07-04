#ifndef GAME_HPP
# define GAME_HPP

# include <iostream>
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
        sf::Sprite          _sprite;
        sf::Texture         _texture;
    public:
        Game(int width, int height, std::string name);
        ~Game();

        bool isRunning();
        void update();
        void render();
};

#endif