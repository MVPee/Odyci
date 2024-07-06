#include "../includes/Game.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Game::Game(int width, int height, std::string name) {
	this->_window = new sf::RenderWindow(sf::VideoMode(width, height), name, sf::Style::Default);
	this->_player = new Player("rsrcs/assets/player.png");

	this->_key.upPressed = false;
	this->_key.downPressed = false;
	this->_key.rightPressed	= false;
	this->_key.leftPressed = false;

	this->_window->setFramerateLimit(60);
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Game::~Game() {
	delete this->_window;
	delete this->_player;
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
				case sf::Keyboard::Up:
					this->_key.upPressed = true;
					break;
				case sf::Keyboard::Down:
					this->_key.downPressed = true;
					break;
				case sf::Keyboard::Right:
					this->_key.rightPressed = true;
					break;
				case sf::Keyboard::Left:
					this->_key.leftPressed = true;
					break;
			}
		}
		if (this->_event.type == sf::Event::KeyReleased) {
			switch (this->_event.key.code) {
				case sf::Keyboard::Up:
					this->_key.upPressed = false;
					break;
				case sf::Keyboard::Down:
					this->_key.downPressed = false;
					break;
				case sf::Keyboard::Right:
					this->_key.rightPressed = false;
					break;
				case sf::Keyboard::Left:
					this->_key.leftPressed = false;
					break;
			}
		}
	}
}

/** 
 * @brief Update the window
*/
void Game::update() {
    if (this->_key.rightPressed) {
        this->_player->getSprite().move(SPEED, 0);
    }
	if (this->_key.leftPressed) {
        this->_player->getSprite().move(-SPEED, 0);
    }
	if (this->_key.upPressed) {
        this->_player->getSprite().move(0, -SPEED);
    }
	if (this->_key.downPressed) {
        this->_player->getSprite().move(0, SPEED);
    }
}

/** 
 * @brief Draw in the window
*/
void Game::display(void) {
	this->_window->clear();
	
	this->_window->draw(this->_player->getSprite());
	
	this->_window->display();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */