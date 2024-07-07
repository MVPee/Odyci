#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Macro.hpp"

class Player
{
	private:
		sf::Texture	_texture;
		sf::Sprite	_sprite;
		int			_jumping;
	public:
		Player(std::string srcs);
		~Player(void);

		int getJumping(void);
		void setJumping(int i);
		void jump(int jumpSpeed, bool topCollision, bool spacePressed);
		sf::Sprite& getSprite(void);
};


#endif /* ********************************************************** PLAYER_H */