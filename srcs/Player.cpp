#include "../includes/Player.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Player::Player() {
	this->_pos.x = 128;
	this->_pos.y = 128 - 16;
	this->_texture[0].loadFromFile("rsrcs/assets/player2.png");
	this->_texture[1].loadFromFile("rsrcs/assets/player1.png");
	this->_sprite.setTexture(this->_texture[0]);
	this->_sprite.setPosition(128, 128 - 16);
	this->_sprite.setScale(SCALE/3*2, SCALE/3*2);
	this->_jumping = 0;
	this->_actualTexture = 0;
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

void Player::switchTexture(int key) {
	if (key == 0 && this->_actualTexture != 0) {
		this->_sprite.setTexture(this->_texture[1]);
		this->_actualTexture = 0;
	}
	else if (key == 1 && this->_actualTexture != 1) {
		this->_sprite.setTexture(this->_texture[0]);
		this->_actualTexture = 1;
	}
}

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

sf::Vector2f Player::getInitialPosition(void) {
	return (this->_pos);
}

void Player::jump(bool topCollision, bool spacePressed) {
	static int count = 0;

	if (this->_lastJump.getElapsedTime().asSeconds() < TIME_BEETWEEN_JUMP && !this->_jumping) {
		return ;
	}
    if (!topCollision) {
        this->_jumping = 0;
		count = 0;
        return;
    }
	if (!spacePressed)
		count++;
    if (this->_jumping < JUMPING_HEIGHT && count <= 2) {
        this->_jumping += 1;
        this->_sprite.move(0, -JUMP_SPEED);
    }
	else {
		count = 0;
        this->_jumping = 0;
	}
	if (this->_jumping == 1)
		this->_lastJump.restart();
}

/* ************************************************************************** */