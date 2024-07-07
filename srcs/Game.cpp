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

	this->_map = new Map("rsrcs/maps/sandbox.ody");

	this->_window->setFramerateLimit(60);
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

bool Game::check_collision(int xSpeed, int ySpeed) {
	sf::FloatRect nextPos = this->_player->getSprite().getGlobalBounds();
	nextPos.left += xSpeed;
	nextPos.top += ySpeed;

	int height = this->_map->getSize().height;
    int width = this->_map->getSize().width;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (this->_map->getHitbox(i, j))
				if (nextPos.intersects(this->_map->getSprite(i, j).getGlobalBounds()))
					return (false);
	return (true);
}

/** 
 * @brief Update the window
*/
void Game::update() {
    if (this->_key.rightPressed && check_collision(SPEED, 0)) {
        this->_player->getSprite().move(SPEED, 0);
    }
	if (this->_key.leftPressed && check_collision(-SPEED, 0)) {
        this->_player->getSprite().move(-SPEED, 0);
    }
	if (this->_key.downPressed && check_collision(0, SPEED)) {
        this->_player->getSprite().move(0, SPEED);
    }
	if (this->_key.upPressed && check_collision(0, -SPEED)) {
        this->_player->getSprite().move(0, -SPEED);
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