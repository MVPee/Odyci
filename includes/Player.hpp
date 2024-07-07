#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Macro.hpp"

class Player
{
	private:
		sf::Texture	_texture;
		sf::Sprite	_sprite;
	public:
		Player(std::string srcs);
		~Player(void);

		sf::Sprite& getSprite();
};


#endif /* ********************************************************** PLAYER_H */