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
			switch (this->_assets[i][j].c)
			{
				case '0':
					this->_assets[i][j].hitbox = false;
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(0, 16, 8, 8));
					break;
				case '1':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(0, 0, 8, 8));
					break;
				case '2':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/image.png", sf::IntRect(0, 8, 8, 8));
					break;
				case 'P':
					this->_assets[i][j].texture.loadFromFile("rsrcs/assets/spike.png");
					this->_assets[i][j].sprite.move(0, 3 * SCALE);
					this->_assets[i][j].kill = true;
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

bool Map::getHitbox(int y, int x) {
	return (this->_assets[y][x].hitbox);
}

bool Map::getKill(int y, int x) {
	return (this->_assets[y][x].kill);
}

sf::IntRect Map::getSize(void) {
	sf::IntRect rect;
	rect.height = this->_height;
	rect.width = this->_width;
	return (rect);
}

/* ************************************************************************** */