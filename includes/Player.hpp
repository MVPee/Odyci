#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Macro.hpp"

class Player
{
	private:
		sf::Vector2f	_pos;
		sf::Texture		_texture[4];
		sf::Sprite		_sprite;
		int				_jumping;
		bool			_flying;
		sf::Clock		_lastJump;
		int				_actualTexture;
		bool			_rotated;
	public:
		Player();
		~Player(void);

		sf::Vector2f getInitialPosition();
		int getJumping(void);
		void setJumping(int i);

		void setFlying(bool flying);
		void setRotated(bool rotated);
		bool isFlying(void);

		void jump(bool topCollision, bool spacePressed);
		void rotate(char c);
		void actualizeTexture(void);
		sf::Sprite& getSprite(void);
};


#endif /* ********************************************************** PLAYER_H */