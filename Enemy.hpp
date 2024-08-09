
#ifndef Enemy_hpp
#define Enemy_hpp

#include <SFML/Graphics.hpp>

#include "Player.hpp"

    class Enemy {

        protected :

            sf::Texture Texture;
            sf::Sprite Sprite;

            bool Type;
            int X, Y, Direction, Speed;

        public :

            Enemy(bool, int, int, int);
            void Draw(sf::RenderWindow*, int[], Player*);

            const int Get_X();
            const int Get_Y();
    };

#endif
