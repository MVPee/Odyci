#include "../includes/Map.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

void Map::setAssets(void) {
	this->_assets = new t_assets*[this->_height];
	for (int i = 0; i < this->_height; i++) {
		this->_assets[i] = new t_assets[this->_width];
		for (int j = 0; j < this->_width; j++) {
			this->_assets[i][j].hitbox = true;
			this->_assets[i][j].c = this->_map[i][j];
			this->_assets[i][j].sprite.scale(SCALE, SCALE);
			this->_assets[i][j].sprite.setPosition(j * (SCALE * 8), i * (SCALE * 8));
			this->_assets[i][j].kill = false;
			this->_assets[i][j].event = NO_EVENT;
			switch (this->_assets[i][j].c)
			{
				//DIRT
				case '0':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(0, 16, 8, 8));
					break;
				case '1':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(0, 0, 8, 8));
					break;
				case '2':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(8, 0, 8, 8));
					break;
				case '3':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(16, 0, 8, 8));
					break;
				//UNDERDIRT
				case '4':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(0, 8, 8, 8));
					break;
				case '5':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(8, 8, 8, 8));
					break;
				case '6':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(16, 8, 8, 8));
					break;

				//STONE
				case 'O':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(24, 0, 8, 8));
					break;
				case 'I':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(32, 0, 8, 8));
					break;
				case 'M':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(24, 8, 8, 8));
					break;
				case 'N':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(32, 8, 8, 8));
					break;

				//SPIKE
				case 'D':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(72, 75, 8, 5));
					this->_assets[i][j].sprite.move(0, 3 * SCALE);
					this->_assets[i][j].kill = true;
					break;
				case 'R':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(64, 72, 5, 8));
					this->_assets[i][j].kill = true;
					break;
				case 'L':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(51, 72, 5, 8));
					this->_assets[i][j].sprite.move(3 * SCALE, 0);
					this->_assets[i][j].kill = true;
					break;
				case 'U':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(56, 72, 8, 5));
					this->_assets[i][j].kill = true;
					break;
				
				//FOUNDATION
				case '8':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(40, 0, 8, 8));
					break;
				case '9':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(48, 0, 8, 8));
					break;

				//TREE
				case 'A':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(72, 0, 8, 24));
					this->_assets[i][j].sprite.move(0, 16 * -SCALE);
					this->_assets[i][j].hitbox = false;
					this->_assets[i][j].event = WELCOME;
					break;

				//SIGN
				case 'P':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(56, 0, 16, 16));
					this->_assets[i][j].sprite.move(4 * -SCALE, 8 * -SCALE);
					this->_assets[i][j].hitbox = false;
					break;
			}
			this->_assets[i][j].sprite.setTexture(this->_assets[i][j].texture);
		}
	}
}

Map::Map(std::string srcs) {
	this->_width = 0;
	this->_height = 0;
	
	if (setMap(srcs))
		return ;
	setAssets();
	this->_backgroundTexture.loadFromFile("rsrcs/backgrounds/background2.png");
	this->_backgroundSprite.setTexture(_backgroundTexture);

	this->_text.font.loadFromFile("rsrcs/fonts/SuperMario256.ttf");
	this->_text.text.setFont(this->_text.font);
	this->_text.text.setCharacterSize(50);
	this->_text.text.setFillColor(sf::Color::White);
	this->_text.text.setPosition(20, 20);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Map::~Map() {
	for (int i = 0; i < this->_height + 1; i++)
		delete[] this->_map[i];
	delete [] this->_map; 

	for (int i = 0; i < this->_height; i++)
		delete[] this->_assets[i];
	delete[] this->_assets;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

void Map::playEvent(char c, int count, sf::Sprite &player) {
	float offsetX = 0.0;
	float offsetY = 0.0;
	printText(c);
	if (count % 5) {
		offsetX = (std::rand() % 3 - 1) * 1.0f;
		offsetY = (std::rand() % 3 - 1) * 1.0f;
	}
	int textWidth = this->_text.text.getGlobalBounds().width;
	int textHeight = this->_text.text.getGlobalBounds().height;
	int playerCenter = player.getGlobalBounds().width/2;
	this->_text.text.setPosition((player.getPosition().x - textWidth/2 + playerCenter) + offsetX, (player.getPosition().y + -textHeight * 2) + offsetY);
}

void Map::printText(int event) {
    switch (event) {
        case WELCOME:
            this->_text.text.setString("This is a tree...");
            break;
        default:
            this->_text.text.setString("");
            break;
    }
}

bool Map::setMap(std::string srcs) {
	std::ifstream file;
	std::string line;

	file.open(srcs);
	if (!file.is_open())
		return (true);

	while(std::getline(file, line)) {
		this->_height++;
		if (line.length() > this->_width)
			this->_width = line.length();
	}

	this->_map = new char*[this->_height + 1];
	this->_map[this->_height] = NULL;
	for (int i = 0; i < this->_height; i++) {
		this->_map[i] = new char[this->_width + 1];
		this->_map[i][this->_width] = '\0';
		std::memset(this->_map[i], '0', this->_width);
	}

	file.clear();
	file.seekg(0, std::ios::beg);

	int i = 0;
	while(std::getline(file, line)) {
		for (int j = 0; j < this->_width; j++)
			this->_map[i][j] = line[j];
		i++;
	}
	file.close();
	return (false);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

sf::Sprite &Map::getSprite(int y, int x) {
	return (this->_assets[y][x].sprite);
}

sf::Sprite &Map::getBackground() {
	return (this->_backgroundSprite);
}

bool Map::getHitbox(int y, int x) {
	return (this->_assets[y][x].hitbox);
}

bool Map::getKill(int y, int x) {
	return (this->_assets[y][x].kill);
}

int Map::getEvent(int y, int x) {
	return (this->_assets[y][x].event);
}

sf::IntRect Map::getSize(void) {
	sf::IntRect rect;
	rect.height = this->_height;
	rect.width = this->_width;
	return (rect);
}

sf::Text &Map::getText() {
	return (this->_text.text);
}

/* ************************************************************************** */