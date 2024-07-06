#include "../includes/Player.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Player::Player(std::string rsrcs) {
	this->_texture.loadFromFile(rsrcs);
	this->_sprite.setTexture(this->_texture);
	this->_sprite.setPosition(0, 0);
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