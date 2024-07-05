#ifndef MAP_HPP
# define GAME_HPP

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
        int             **_map;
        bool getSize(std::ifstream &file);
        void parsingMap(std::ifstream &file);
    public:
        Map(std::string file);
        ~Map(void);

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