#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Macro.hpp"

class Player
{
	private:
		sf::Texture	_texture[2];
		sf::Sprite	_sprite;
		int			_jumping;
		int			_actualTexture;
	public:
		Player();
		~Player(void);

		int getJumping(void);
		void setJumping(int i);
		void jump(bool topCollision, bool spacePressed);
		void switchTexture(int key);
		sf::Sprite& getSprite(void);
};


#endif /* ********************************************************** PLAYER_H */