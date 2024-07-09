#include "../includes/Map.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

void Map::setAssets(void) {
    static std::unordered_map<char, sf::IntRect> textureMap = {
        {'0', sf::IntRect(0, 16, 8, 8)},
        {'1', sf::IntRect(0, 0, 8, 8)},
        {'2', sf::IntRect(8, 0, 8, 8)},
        {'3', sf::IntRect(16, 0, 8, 8)},
        {'4', sf::IntRect(0, 8, 8, 8)},
        {'5', sf::IntRect(8, 8, 8, 8)},
        {'6', sf::IntRect(16, 8, 8, 8)},
        {'O', sf::IntRect(24, 0, 8, 8)},
        {'I', sf::IntRect(32, 0, 8, 8)},
        {'M', sf::IntRect(24, 8, 8, 8)},
        {'N', sf::IntRect(32, 8, 8, 8)},
        {'D', sf::IntRect(72, 75, 8, 5)},
        {'R', sf::IntRect(64, 72, 5, 8)},
        {'L', sf::IntRect(51, 72, 5, 8)},
        {'U', sf::IntRect(56, 72, 8, 5)},
        {'8', sf::IntRect(40, 0, 8, 8)},
        {'9', sf::IntRect(48, 0, 8, 8)},
        {'A', sf::IntRect(72, 0, 8, 24)},
        {'P', sf::IntRect(56, 0, 16, 16)},
        {'|', sf::IntRect(0, 72, 8, 8)},
		{'\\', sf::IntRect(0, 72, 8, 8)}
    };

    for (int i = 0; i < this->_height; i++) {
        for (int j = 0; j < this->_width; j++) {
            this->_assets[i][j].hitbox = true;
            this->_assets[i][j].c = this->_map[i][j];
            this->_assets[i][j].sprite.setScale(SCALE, SCALE);
            this->_assets[i][j].sprite.setPosition((j - 3) * (SCALE * 8), (i - 3) * (SCALE * 8));
            this->_assets[i][j].kill = false;
            this->_assets[i][j].event = NO_EVENT;

            if (textureMap.find(this->_assets[i][j].c) != textureMap.end()) {
                this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", textureMap[this->_assets[i][j].c]);
            }

            switch (this->_assets[i][j].c) {
                case 'D':
                    this->_assets[i][j].sprite.move(0, 3 * SCALE);
                    this->_assets[i][j].kill = true;
                    break;
                case 'R':
                case 'L':
                    if (this->_assets[i][j].c == 'L') {
                        this->_assets[i][j].sprite.move(3 * SCALE, 0);
                    }
                    this->_assets[i][j].kill = true;
                    break;
                case 'U':
                    this->_assets[i][j].kill = true;
                    break;
                case 'A':
                    this->_assets[i][j].sprite.move(0, 16 * -SCALE);
                    this->_assets[i][j].hitbox = false;
                    this->_assets[i][j].event = TREE;
                    break;
                case 'P':
                    this->_assets[i][j].sprite.move(4 * -SCALE, 8 * -SCALE);
                    this->_assets[i][j].hitbox = false;
                    break;
                case '|':
                    this->_assets[i][j].event = NEXT_MAP;
					break;
				case '\\':
                    this->_assets[i][j].event = PREVIOUS_MAP;
					break;
            }
            this->_assets[i][j].sprite.setTexture(this->_assets[i][j].texture);
        }
    }
}

Map::Map(std::string srcs, Player &player) {
    this->_width = 0;
    this->_height = 0;

	this->_switchMapClock.restart();
    if (!setMap(srcs, player, 'N')) {
        setAssets();
        this->_backgroundSprite.setTexture(_backgroundTexture);

        this->_text.font.loadFromFile("rsrcs/fonts/SuperMario256.ttf");
        this->_text.text.setFont(this->_text.font);
        this->_text.text.setCharacterSize(50);
        this->_text.text.setFillColor(sf::Color::White);
        this->_text.text.setPosition(20, 20);

        player.getSprite().setPosition(player.getPos().x, player.getPos().y);
    }
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Map::~Map() {
    if (this->_map) {
        for (int i = 0; i < this->_height; i++)
            delete[] this->_map[i];
        delete[] this->_map;
    }

    if (this->_assets) {
        for (int i = 0; i < this->_height; i++)
            delete[] this->_assets[i];
        delete[] this->_assets;
    }
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Map::switchMap(std::string srcs, Player &player, char c) {
	this->_switchMapClock.restart();
    if (this->_map) {
        for (int i = 0; i < this->_height; i++)
            delete[] this->_map[i];
        delete[] this->_map;
    }

    if (this->_assets) {
        for (int i = 0; i < this->_height; i++)
            delete[] this->_assets[i];
        delete[] this->_assets;
    }

    if (!setMap(srcs, player, c)) {
        setAssets();
        this->_backgroundSprite.setTexture(_backgroundTexture);
        player.getSprite().setPosition(player.getPos().x, player.getPos().y);
    }
}

void Map::nextMap(Player &player) {
	if (this->_switchMapClock.getElapsedTime().asSeconds() > 0.5)
		switchMap(this->_nextMap, player, 'N');
}

void Map::previousMap(Player &player) {
	if (this->_switchMapClock.getElapsedTime().asSeconds() > 0.5)
		switchMap(this->_previousMap, player, 'P');
}

void Map::playEvent(int event, int count, Player &player) {
    float offsetX = 0.0;
    float offsetY = 0.0;
    if (count % 5) {
        offsetX = (std::rand() % 3 - 1) * 1.0f;
        offsetY = (std::rand() % 3 - 1) * 1.0f;
    }
    int textWidth;
    int textHeight;
    int playerCenter = player.getSprite().getGlobalBounds().width / 2;

    switch (event) {
        case TREE:
            this->_text.text.setString("This is a tree...");
            textWidth = this->_text.text.getGlobalBounds().width;
            textHeight = this->_text.text.getGlobalBounds().height;
            this->_text.text.setPosition((player.getSprite().getPosition().x - textWidth / 2 + playerCenter) + offsetX, (player.getSprite().getPosition().y + -textHeight * 2) + offsetY);
            break;
		case NEXT_MAP:
            nextMap(player);
            break;
		case PREVIOUS_MAP:
            previousMap(player);
            break;
    }
}

void Map::resetText(void) {
    this->_text.text.setString("");
}

bool Map::setMap(std::string srcs, Player &player, char c) {
    std::ifstream file(srcs);
    std::string line;

	int playerY;
	int playerX;

    if (!file.is_open())
        return true;

	if (c == 'N') {
		std::getline(file, line);
		playerX = std::stoi(line);
		std::getline(file, line);
		playerY = std::stoi(line);
		std::getline(file, line);
		std::getline(file, line);
	}
	else if (c == 'P') {
		std::getline(file, line);
		std::getline(file, line);
		std::getline(file, line);
		std::cout << line << std::endl;
		playerX = std::stoi(line);
		std::getline(file, line);
		std::cout << line << std::endl;
		playerY = std::stoi(line);
	}
	std::getline(file, line);
    this->_previousMap = line;
	std::getline(file, line);
    this->_nextMap = line;
	std::getline(file, line);
	this->_backgroundTexture.loadFromFile(line);
	std::getline(file, line);

	player.setPos(playerX, playerY);

    this->_height = 0;
    this->_width = 0;

    std::vector<std::string> lines;

    while (std::getline(file, line)) {
        lines.push_back(line);
        this->_height++;
        if (line.length() > this->_width) {
            this->_width = line.length();
        }
    }

    file.close();

    this->_map = new char* [this->_height];
    for (int i = 0; i < this->_height; i++) {
        this->_map[i] = new char[this->_width + 1];
        std::memcpy(this->_map[i], lines[i].c_str(), lines[i].length());
        this->_map[i][this->_width] = '\0';
    }

    this->_assets = new t_assets* [this->_height];
    for (int i = 0; i < this->_height; i++) {
        this->_assets[i] = new t_assets[this->_width];
    }

    return false;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

sf::Sprite& Map::getSprite(int y, int x) {
    return this->_assets[y][x].sprite;
}

sf::Sprite& Map::getBackground() {
    return this->_backgroundSprite;
}

bool Map::getHitbox(int y, int x) {
    return this->_assets[y][x].hitbox;
}

bool Map::getKill(int y, int x) {
    return this->_assets[y][x].kill;
}

int Map::getEvent(int y, int x) {
    return this->_assets[y][x].event;
}

sf::IntRect Map::getSize(void) {
    return sf::IntRect(0, 0, this->_width, this->_height);
}

sf::Text& Map::getText() {
    return this->_text.text;
}

/* ************************************************************************** */
