#ifndef GAME_HPP
# define GAME_HPP

# include "Macro.hpp"
# include "Player.hpp"
# include "Map.hpp"

typedef struct s_fps {
	sf::Clock	clock;
	sf::Clock	fpsClock;
	sf::Font	font;
	sf::Text	fpsText;
}	t_fps;

typedef struct s_key {
	bool WPressed;
	bool SPressed;
	bool DPressed;
	bool APressed;
	bool spacePressed;
	bool rightPressed;
	bool leftPressed;
}	t_key;

class Game {
	private:
		sf::RenderWindow	*_window;
		sf::Event			_event;
		t_key				_key;
		t_fps				_fps;
		Player				*_player;
		Map					*_map;

		bool checkCollision(int x, int y);
		void updateCamera(void);
		void checkFalling(void);
	public:

		Game(int width, int height, std::string name);
		~Game();

		void updateFps(float elapsedTime);
		bool isRunning(void);

		void event(void);
		void update(void);
		void display(void);
};

#endif /* ************************************************************ GAME_H */