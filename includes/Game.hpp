#ifndef GAME_HPP
# define GAME_HPP

# include "Macro.hpp"
# include "Player.hpp"
# include "Map.hpp"

typedef struct s_key {
	bool upPressed;
	bool downPressed;
	bool rightPressed;
	bool leftPressed;
}	t_key;

class Game {
	private:
		sf::RenderWindow	*_window;
		sf::Event			_event;
		t_key				_key;
		Player				*_player;
		Map					*_map;

		bool check_collision(int x, int y);
	public:

		Game(int width, int height, std::string name);
		~Game();

		bool isRunning(void);

		void event(void);
		void update(void);
		void display(void);
};

#endif /* ************************************************************ GAME_H */