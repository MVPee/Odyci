#include "../includes/Game.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Game::Game(int width, int height, std::string name) {
	this->_window = new sf::RenderWindow(sf::VideoMode(width, height), name, sf::Style::Default);
	this->_player = new Player();

	this->_key.WPressed = false;
	this->_key.SPressed = false;
	this->_key.DPressed	= false;
	this->_key.APressed = false;
	this->_key.spacePressed = false;
    this->_key.rightPressed = false;
    this->_key.leftPressed = false;

	this->_map = new Map(
                            "rsrcs/maps/sandbox.ody", \
                            *this->_player
                        );
    
	this->_window->setFramerateLimit(144);

    this->_fps.font.loadFromFile("rsrcs/fonts/SuperMario256.ttf");
    this->_fps.fpsText.setFont(this->_fps.font);
    this->_fps.fpsText.setCharacterSize(24);
    this->_fps.fpsText.setFillColor(sf::Color::White);
    this->_fps.fpsText.setPosition(10, 10);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Game::~Game() {
	delete this->_window;
	delete this->_player;
    if (this->_map)
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
                    this->_key.WPressed = true;
                    break;
                case sf::Keyboard::S:
                    this->_key.SPressed = true;
                    break;
                case sf::Keyboard::D:
                    this->_key.DPressed = true;
                    break;
                case sf::Keyboard::A:
                    this->_key.APressed = true;
                    break;
                case sf::Keyboard::Space:
                    this->_key.spacePressed = true;
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
                case sf::Keyboard::W:
                    this->_key.WPressed = false;
                    break;
                case sf::Keyboard::S:
                    this->_key.SPressed = false;
                    break;
                case sf::Keyboard::D:
                    this->_key.DPressed = false;
                    break;
                case sf::Keyboard::A:
                    this->_key.APressed = false;
                    break;
                case sf::Keyboard::Space:
                    this->_key.spacePressed = false;
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
 * @brief Check the collision of the wall's map with the player
 * @return true if collision otherwise false
*/
bool Game::checkCollision(int xSpeed, int ySpeed) {
    static int count = 0;
    count++;

    sf::FloatRect nextPos = this->_player->getSprite().getGlobalBounds();
    nextPos.left += xSpeed;
    nextPos.top += ySpeed;

    sf::FloatRect topPos = this->_player->getSprite().getGlobalBounds();
    topPos.top += ySpeed - 1;

    sf::FloatRect belowPos = this->_player->getSprite().getGlobalBounds();
    belowPos.top += ySpeed + 1;

    sf::FloatRect leftPos = this->_player->getSprite().getGlobalBounds();
    leftPos.left += xSpeed - 1;

    sf::FloatRect rightPos = this->_player->getSprite().getGlobalBounds();
    rightPos.left += xSpeed + 1;

    int height = this->_map->getSize().height;
    int width = this->_map->getSize().width;

    // if (nextPos.left < 0 || nextPos.top < 0 || nextPos.left + nextPos.width > width * (SCALE * 8) || nextPos.top + nextPos.height > height * (SCALE * 8)) {
    //     return false;
    // }

    bool isEventTriggered = false;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (this->_map->getKill(i, j)) {
                if (topPos.intersects(this->_map->getSprite(i, j).getGlobalBounds())) {
                    this->_player->getSprite().setPosition(this->_player->getInitialPosition().x, this->_player->getInitialPosition().y);
                    return false;
                }
                if (belowPos.intersects(this->_map->getSprite(i, j).getGlobalBounds())) {
                    this->_player->getSprite().setPosition(this->_player->getInitialPosition().x, this->_player->getInitialPosition().y);
                    return false;
                }
                if (leftPos.intersects(this->_map->getSprite(i, j).getGlobalBounds())) {
                    this->_player->getSprite().setPosition(this->_player->getInitialPosition().x, this->_player->getInitialPosition().y);
                    return false;
                }
                if (rightPos.intersects(this->_map->getSprite(i, j).getGlobalBounds())) {
                    this->_player->getSprite().setPosition(this->_player->getInitialPosition().x, this->_player->getInitialPosition().y);
                    return false;
                }
            }
            if (this->_map->getEvent(i, j)) {
                if (nextPos.intersects(this->_map->getSprite(i, j).getGlobalBounds())) {
                    this->_map->playEvent(this->_map->getEvent(i, j), count, *this->_player);
                    isEventTriggered = true;
                }
            }
            if (this->_map->getHitbox(i, j))
                if (nextPos.intersects(this->_map->getSprite(i, j).getGlobalBounds()))
                    return false;
        }
    }

    if (!isEventTriggered) {
        this->_map->resetText();
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
    //std::cout << "x " << this->_player->getSprite().getPosition().x << " y " << this->_player->getSprite().getPosition().y << std::endl;
}

void Game::checkFalling(void) {
	int temp;
	static int count = 0;

    temp = SPEED_FALLING;
    if (!this->_player->getJumping() && checkCollision(0, 1)) {
        count++;
        if (count < 10)
            this->_player->getSprite().move(0, 1);
        else if (checkCollision(0, SPEED_FALLING))
            this->_player->getSprite().move(0, SPEED_FALLING);
        else {
            while (!checkCollision(0, temp))
                temp--;
            this->_player->getSprite().move(0, temp);
            count = 0;
        }
    }
    else
        count = 0;
}

void Game::updateFps(void) {
    float fps = 1.f / this->_fps.fpsClock.restart().asSeconds();
    this->_fps.fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
}

/** 
 * @brief Update the window
*/
void Game::update(void) {
	updateCamera();
	checkFalling();
    updateFps();

    if (this->_key.DPressed && checkCollision(SPEED, 0)) {
        this->_player->getSprite().move(SPEED, 0);
		this->_player->rotate('R');
    }
	if (this->_key.APressed && checkCollision(-SPEED, 0)) {
        this->_player->getSprite().move(-SPEED, 0);
		this->_player->rotate('L');
    }

    this->_player->setFlying(false);
    if (((this->_key.spacePressed && !checkCollision(0, 1)) || this->_player->getJumping() > 0)) {
        this->_player->jump(checkCollision(0, -JUMP_SPEED), this->_key.spacePressed);
    } 
    else if (this->_key.spacePressed && checkCollision(0, -FLY_FALL_SPEED) && checkCollision(0, 1)) {
        this->_player->setFlying(true);
        this->_player->getSprite().move(0, -FLY_FALL_SPEED);
    }

    if (this->_key.rightPressed && checkCollision(-SPEED, 0)) {
        this->_map->nextMap(*this->_player);
    }
    if (this->_key.leftPressed && checkCollision(-SPEED, 0)) {
        this->_map->previousMap(*this->_player);
    }
}

/** 
 * @brief Draw in the window
*/
void Game::display(void) {
	this->_window->clear();

    this->_window->draw(this->_map->getBackground());

	for (int i = 0; i < this->_map->getSize().height; i++)
		for (int j = 0; j < this->_map->getSize().width; j++)
			this->_window->draw(this->_map->getSprite(i, j));

	this->_window->draw(this->_player->getSprite());

    this->_window->draw(this->_fps.fpsText);

    this->_window->draw(this->_map->getText());

	this->_window->display();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */