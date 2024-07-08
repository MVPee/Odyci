#include "../includes/Game.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Game::Game(int width, int height, std::string name) {
	this->_window = new sf::RenderWindow(sf::VideoMode(width, height), name, sf::Style::Default);
	this->_player = new Player();

	this->_key.upPressed = false;
	this->_key.downPressed = false;
	this->_key.rightPressed	= false;
	this->_key.leftPressed = false;
	this->_key.spacePressed = false;

	this->_map = new Map("rsrcs/maps/sandbox.ody");

	this->_window->setFramerateLimit(144);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Game::~Game() {
	delete this->_window;
	delete this->_player;
	delete this->_map;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

bool Game::isRunning(void) {
	return (this->_window->isOpen());
}

/** 
 * @brief Listener of the keyboard input in the window
*/
void Game::event(void) {
    while (this->_window->pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window->close();
        if (this->_event.type == sf::Event::KeyPressed) {
            switch (this->_event.key.code) {
                case sf::Keyboard::Escape:
                    this->_window->close();
                    break;
                case sf::Keyboard::W:
                    this->_key.upPressed = true;
                    break;
                case sf::Keyboard::S:
                    this->_key.downPressed = true;
                    break;
                case sf::Keyboard::D:
                    this->_key.rightPressed = true;
                    break;
                case sf::Keyboard::A:
                    this->_key.leftPressed = true;
                    break;
                case sf::Keyboard::Space:
                    this->_key.spacePressed = true;
                    break;
            }
        }
        if (this->_event.type == sf::Event::KeyReleased) {
            switch (this->_event.key.code) {
                case sf::Keyboard::W:
                    this->_key.upPressed = false;
                    break;
                case sf::Keyboard::S:
                    this->_key.downPressed = false;
                    break;
                case sf::Keyboard::D:
                    this->_key.rightPressed = false;
                    break;
                case sf::Keyboard::A:
                    this->_key.leftPressed = false;
                    break;
                case sf::Keyboard::Space:
                    this->_key.spacePressed = false;
                    break;
            }
        }
    }
}


/** 
 * @brief Check the collision of the wall's map with the player
 * @return true if collision otherwise false
*/
bool Game::check_collision(int xSpeed, int ySpeed) {
    sf::FloatRect nextPos = this->_player->getSprite().getGlobalBounds();
    nextPos.left += xSpeed;
    nextPos.top += ySpeed;

	sf::FloatRect belowPos = this->_player->getSprite().getGlobalBounds();
    belowPos.top += ySpeed + 1;

    int height = this->_map->getSize().height;
    int width = this->_map->getSize().width;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (this->_map->getHitbox(i, j))
                if (nextPos.intersects(this->_map->getSprite(i, j).getGlobalBounds()))
                    return false;
			if (this->_map->getKill(i, j))
                if (belowPos.intersects(this->_map->getSprite(i, j).getGlobalBounds()))
                    this->_player->getSprite().setPosition(this->_player->getInitialPosition().x, this->_player->getInitialPosition().y);
		}
	}
            

    return true;
}


/** 
 * @brief Update the camera in the middle of the screen
*/
void Game::updateCamera(void) {
    // int screenX = this->_window->getSize().x / 2;
    // int screenY = this->_window->getSize().y / 2;

    // int playerX = this->_player->getSprite().getPosition().x;
    // int playerY = this->_player->getSprite().getPosition().y;

    // int moveX = (screenX - playerX)/10;
    // int moveY = (screenY - playerY)/10;

    // this->_player->getSprite().move(moveX, moveY);
    // for (int i = 0; i < this->_map->getSize().height; i++) {
    //     for (int j = 0; j < this->_map->getSize().width; j++) {
    //         this->_map->getSprite(i, j).move(moveX, moveY);
    //     }
    // }
}

void Game::checkFalling(void) {
	int temp;
	static int count = 0;

	temp = SPEED_FALLING;
	if (!this->_player->getJumping() && check_collision(0, 1)) {
		count++;
        if (count < 10)
			this->_player->getSprite().move(0, 1);
		else if (check_collision(0, SPEED_FALLING))
			this->_player->getSprite().move(0, SPEED_FALLING);
		else {
			while (!check_collision(0, temp))
				temp--;
			this->_player->getSprite().move(0, temp);
			count = 0;
		}
	}
	else
		count = 0;
}

/** 
 * @brief Update the window
*/
void Game::update(void) {
	updateCamera();
	checkFalling();

    if (this->_key.rightPressed && check_collision(SPEED, 0)) {
        this->_player->getSprite().move(SPEED, 0);
		this->_player->switchTexture(1);
    }
	if (this->_key.leftPressed && check_collision(-SPEED, 0)) {
        this->_player->getSprite().move(-SPEED, 0);
		this->_player->switchTexture(0);
    }
	// if (this->_key.downPressed && check_collision(0, SPEED)) {
    //     this->_player->getSprite().move(0, SPEED);
    // }
	// if (this->_key.upPressed && check_collision(0, -SPEED)) {
    //     this->_player->getSprite().move(0, -SPEED);
    // }

	if (((this->_key.spacePressed && !check_collision(0, 1)) || this->_player->getJumping() > 0)) {
		this->_player->jump(check_collision(0, -JUMP_SPEED), this->_key.spacePressed);
	}
}

/** 
 * @brief Draw in the window
*/
void Game::display(void) {
	this->_window->clear();

	for (int i = 0; i < this->_map->getSize().height; i++)
		for (int j = 0; j < this->_map->getSize().width; j++)
			this->_window->draw(this->_map->getSprite(i, j));

	this->_window->draw(this->_player->getSprite());

	this->_window->display();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */