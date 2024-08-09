
#ifndef Player_hpp
#define Player_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

    class Player {

        protected :

            sf::Texture Texture;
            sf::Sprite Sprite;

            sf::SoundBuffer SoundBuffer[2];
            sf::Sound Sound[2];

            bool Keyboard[4], Direction;
            int X, Y, Life;

        public :

            Player(int);
            void Move(int[], sf::Event);
            void Draw(sf::RenderWindow*, int =0, int =0);
            void Hit(bool =false);
            void WinLife();

            const int Get_X();
            const int Get_Y();
            const int Get_Lives();

            void Set_XY(int, int);
    };

#endif
