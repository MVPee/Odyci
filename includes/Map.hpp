#ifndef MAP_HPP
# define GAME_HPP

# include "MySprite.hpp"
# include <iostream>
# include <fstream>
# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include <SFML/Window.hpp>
# include <SFML/Audio.hpp>
# include <SFML/Network.hpp>

class Map {
    private:
        std::ifstream   *_file;
        int             _height;
        int             _width;
        char            **_map;
        MySprite          **_sprites;
        bool getSize(std::ifstream &file);
        void parsingMap(std::ifstream &file);
    public:
        Map(std::string file);
        ~Map(void);

        int getHeight(void);
        int getWidth(void);

        MySprite **getMySprites(void);
        sf::Sprite getMySprite(int y, int x);

        class MapOpenFailed : public std::exception {
			public:
				const char *what() const throw();
		};

        class MapIsNotARectangle : public std::exception
		{
			public:
				const char *what() const throw();
		};
};

#endif