#ifndef MAP_HPP
# define MAP_HPP

# include "Macro.hpp"

typedef struct s_assets {
	sf::Sprite	sprite;
	sf::Texture texture;
	char		c;
	bool		hitbox;
	bool		kill;
}	t_assets;

class Map
{
	private:
		int			_width;
		int			_height;
		char		**_map;
		t_assets	**_assets;

		bool setMap(std::string srcs);
		void setAssets();
	public:
		Map(std::string srcs);
		~Map();

		sf::IntRect getSize(void);
		sf::Sprite &getSprite(int y, int x);
		bool getHitbox(int y, int x);
		bool getKill(int y, int x);

};

#endif /* ************************************************************* MAP_H */