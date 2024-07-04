# include "../includes/Game.hpp"

Game::Game(int width, int height, std::string name) {

    _videoMode.width = width;
    _videoMode.height = height;
    _window = new sf::RenderWindow(_videoMode, name, sf::Style::Default);
    _window->setVerticalSyncEnabled(true);
}

Game::~Game(void) {
    delete _window;
}

bool Game::isRunning(void) {
    return (_window->isOpen());
}

void Game::update(void) {
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window->close();
        if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
            _window->close();
    }
}

void Game::render(void) {
    _window->clear();
    _window->display();
}