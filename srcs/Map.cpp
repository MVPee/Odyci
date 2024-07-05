# include "../includes/Map.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Map::Map(std::string file) {
    

    this->_height = 0;
    this->_width = -1;
    this->_file = new std::ifstream(file);

    if (!this->_file->is_open())
        throw MapOpenFailed();

    if (getSize(*this->_file))
        throw MapIsNotARectangle();

    this->_map = new int*[this->_height];
    for (int i = 0; i < this->_height; i++)
        this->_map[i] = new int[this->_width];

    this->_file->clear();
    this->_file->seekg(0, std::ios::beg);

    parsingMap(*this->_file);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Map::~Map(void) {
    if (this->_file->is_open())
        this->_file->close();
    if (this->_file)
        delete this->_file;
    if (this->_map) {
        for (int i = 0; i < this->_height; i++)
            delete[] this->_map[i];
        delete[] this->_map;
    }
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool Map::getSize(std::ifstream &file) {
    std::string line;

    while (std::getline(file, line)) {
        this->_height++;
        if (this->_width == -1)
            this->_width = line.length();
        else if (this->_width != line.length()) {
            std::cerr << "Map is not a rectangle" << std::endl;
            return (true);
        }
    }
    return (false);
}

void Map::parsingMap(std::ifstream &file) {
    std::string line;
    int y;

    y = -1;
    while (std::getline(file, line)) {
        y++;
        for(int x = 0; x < line.length(); x++)
            this->_map[y][x] = line[x] - '0';
    }
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/*
** --------------------------------- EXCEPTIONS -------------------------------
*/

const char *Map::MapOpenFailed::what() const throw() {
    return ("Map open failed.");
}

const char *Map::MapIsNotARectangle::what() const throw() {
    return ("Map is not a rectangle.");
}