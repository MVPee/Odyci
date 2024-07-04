# include "../includes/Game.hpp"

Game::Game(int width, int height, std::string name) {

    this->_videoMode.width = width;
    this->_videoMode.height = height;
    this->_window = new sf::RenderWindow(_videoMode, name, sf::Style::Default);
    this->_window->setVerticalSyncEnabled(true);
}

Game::~Game(void) {
    delete this->_window;
}

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
    this->_window->display();
}