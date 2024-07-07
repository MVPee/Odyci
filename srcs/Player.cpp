#include "../includes/Player.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Player::Player(std::string srcs) {
	this->_texture.loadFromFile(srcs);
	this->_sprite.setTexture(this->_texture);
	this->_sprite.setPosition(32, 64 + 16);
	this->_sprite.setScale(SCALE, SCALE);
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

sf::Sprite& Player::getSprite() {
    return this->_sprite;
}

/* ************************************************************************** */