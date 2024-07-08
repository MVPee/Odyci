#ifndef GAME_HPP
# define GAME_HPP

# include "Macro.hpp"
# include "Player.hpp"
# include "Map.hpp"

typedef struct s_fps {
	sf::Clock _clock;
	sf::Clock _fpsClock;
	sf::Font _font;
	sf::Text _fpsText;
}	t_fps;

typedef struct s_key {
	bool upPressed;
	bool downPressed;
	bool rightPressed;
	bool leftPressed;
	bool spacePressed;
}	t_key;

class Game {
	private:
		sf::RenderWindow	*_window;
		sf::Event			_event;
		t_key				_key;
		t_fps				_fps;
		Player				*_player;
		Map					*_map;

		bool check_collision(int x, int y);
		void updateCamera(void);
		void checkFalling(void);
		void updateFps(void);
	public:

		Game(int width, int height, std::string name);
		~Game();

		bool isRunning(void);

		void event(void);
		void update(void);
		void display(void);
};

#endif /* ************************************************************ GAME_H */