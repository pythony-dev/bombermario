
#ifndef Bomb_hpp
#define Bomb_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.hpp"
#include "Enemy.hpp"

    class Bomb {

        protected :

            sf::Texture Texture;
            sf::Sprite Sprite;

            sf::SoundBuffer SoundBuffer;
            sf::Sound Sound;

            int Time, X, Y;

        public :

            Bomb(int, int =0, int =0);
            void Draw(sf::RenderWindow*, Player, int[]);
            void Destroy(int[], std::vector<Enemy>*, sf::Sound*, sf::Sound*, int*);

            const int Get_Time();
            const int Get_X();
            const int Get_Y();

            void Set_XY(int, int);
    };

#endif
