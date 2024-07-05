# include "../includes/Game.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Game::Game(int width, int height, std::string name) {

    this->_screen.width = width;
    this->_screen.height = height;
    this->_window = new sf::RenderWindow(_screen, name, sf::Style::Default);
    this->_window->setVerticalSyncEnabled(true);
    try {
        this->_map = new Map("rsrcs/maps/sandbox.ody");
    }
    catch (std::exception &e){
        std::cerr << e.what() << std::endl;
        this->_window->close();
    }
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Game::~Game(void) {
    delete this->_window;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool Game::isRunning(void) {
    return (this->_window->isOpen());
}

void Game::update(void) {
    while (this->_window->pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window->close();
        if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Escape)
            this->_window->close();
    }
}

void Game::render(void) {
    this->_window->clear();

    for (int y = 0; y < this->_map->getHeight(); ++y) {
        for (int x = 0; x < this->_map->getWidth(); ++x) {
            this->_window->draw((this->_map->getMySprite(y, x)));
        }
    }

    this->_window->display();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/