#ifndef MAP_HPP
# define MAP_HPP

# include "Macro.hpp"

# define NO_EVENT 0
# define NEXT_MAP 1
# define PREVIOUS_MAP 2
# define WELCOME 3

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

		bool setMap(std::string srcs);
		void setAssets();
	public:
		Map(std::string srcs);
		~Map();

		void printText(int i, int j);

		sf::IntRect getSize(void);
		sf::Sprite &getSprite(int y, int x);
		sf::Sprite &getBackground();
		bool getHitbox(int y, int x);
		bool getKill(int y, int x);
		bool getEvent(int y, int x);
		sf::Text &getText(void);

};

#endif /* ************************************************************* MAP_H */