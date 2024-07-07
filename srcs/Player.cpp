#include "../includes/Player.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Player::Player(std::string srcs) {
	this->_texture.loadFromFile(srcs);
	this->_sprite.setTexture(this->_texture);
	this->_sprite.setPosition(128, 128 - 16);
	this->_sprite.setScale(SCALE, SCALE);
	this->_jumping = 0;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Player::~Player(void) {
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

sf::Sprite& Player::getSprite(void) {
    return this->_sprite;
}

int Player::getJumping(void) {
	return (this->_jumping);
}

void Player::setJumping(int i) {
	this->_jumping = i;
}

void Player::jump(int jumpSpeed, bool topCollision, bool spacePressed) {
	static int count = 0;
    if (!topCollision) {
        this->_jumping = 0;
		count = 0;
        return;
    }
	if (!spacePressed)
		count++;
    if (this->_jumping < JUMPING_HEIGHT && count <= 2) {
        this->_jumping += 1;
        this->_sprite.move(0, -jumpSpeed + this->_jumping);
    } 
	else {
		count = 0;
        this->_jumping = 0;
	}
}

/* ************************************************************************** */