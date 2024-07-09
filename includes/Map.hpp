#ifndef MAP_HPP
# define MAP_HPP

# include "Macro.hpp"
# include "Player.hpp"

# define NO_EVENT 0
# define NEXT_MAP 1
# define PREVIOUS_MAP 2
# define TREE 3
# define GRAVITY 4

typedef struct s_text {
	sf::Font	font;
	sf::Text	text;
	bool		activate;
}	t_text;

typedef struct s_assets {
	sf::Sprite	sprite;
	sf::Texture texture;
	char		c;
	bool		hitbox;
	bool		kill;
	int			event;
}	t_assets;

class Map
{
	private:
		int			_width;
		int			_height;
		char		**_map;
		t_assets	**_assets;
		t_text		_text;

		sf::Texture	_backgroundTexture;
		sf::Sprite	_backgroundSprite;

		std::string	_nextMap;
		std::string _previousMap;

		sf::Clock	_switchMapClock;

		bool setMap(std::string srcs, Player &player, char c);
		void setAssets(void);
	public:
		Map(std::string srcs, Player &player);
		~Map();

		void switchMap(std::string src, Player &player, char c);

		void nextMap(Player &player);
		void previousMap(Player &player);

		void resetText(void);
		void playEvent(int event, int count, Player &player);

		sf::IntRect getSize(void);
		sf::Sprite &getSprite(int y, int x);
		sf::Sprite &getBackground();
		bool getHitbox(int y, int x);
		bool getKill(int y, int x);
		int getEvent(int y, int x);
		sf::Text &getText(void);
};

#endif /* ************************************************************* MAP_H */