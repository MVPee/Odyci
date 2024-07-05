#ifndef MYSPRITE_HPP
# define MYSPRITE_HPP

# include <iostream>
# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include <SFML/Window.hpp>
# include <SFML/Audio.hpp>
# include <SFML/Network.hpp>

class MySprite {
    private:
        bool        _hitbox = false;
        sf::Texture *_texture;
        sf::Sprite  _sprite;
    public:
        MySprite(void);
        MySprite(char c, bool hitbox, int y, int x);
        ~MySprite(void);

        void setTexture(char c);

        sf::Sprite getSprite(void);
        sf::Texture *getTexture(void);
};

#endif