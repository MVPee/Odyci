# include "../includes/MySprite.hpp"
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

MySprite::MySprite() {}

MySprite::MySprite(char c, bool hitbox, int y, int x) {
    if (hitbox)
        this->_hitbox = true;
    if (c == '0')
        this->_hitbox = false;
    this->_texture = new sf::Texture();
    setTexture(c);
    this->_sprite.setTexture(*this->_texture);
    this->_sprite.scale(4, 4);
    this->_sprite.setPosition(x * 32, y * 32);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

MySprite::~MySprite(void) {
    //delete this->_texture;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void MySprite::setTexture(char c) {

    // X, Y, HEIGHT, WIDTH
    switch(c)
    {
        case '0':
            this->_texture->loadFromFile("rsrcs/assets/image.png", sf::IntRect(0, 16, 8, 8));
            break;
        case '1':
            this->_texture->loadFromFile("rsrcs/assets/image.png", sf::IntRect(16, 0, 8, 8));
            break;
        case '2':
            this->_texture->loadFromFile("rsrcs/assets/image.png", sf::IntRect(0, 8, 8, 8));
            break;
    }
}

sf::Sprite MySprite::getSprite(void) {
    return (this->_sprite);
}

sf::Texture *MySprite::getTexture(void) {
    return (this->_texture);
}

/*
** --------------------------------- EXCEPTIONS -------------------------------
*/
