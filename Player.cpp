
#include <windows.h>

#include "Player.hpp"

    Player::Player(int ID) {
        if(ID ==1) this->Texture.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Player_1.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Player_1.png", RT_RCDATA)));
        else if(ID ==2) this->Texture.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Player_2.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Player_2.png", RT_RCDATA)));
        else if(ID ==3) this->Texture.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Player_3.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Player_3.png", RT_RCDATA)));
        else this->Texture.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Player_4.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Player_4.png", RT_RCDATA)));

    this->Sprite.setTexture(this->Texture);
    this->Sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    this->Sprite.setPosition(928, 508);
    this->SoundBuffer[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Hit.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Hit.wav", RT_RCDATA)));
    this->Sound[0].setBuffer(this->SoundBuffer[0]);
    this->SoundBuffer[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"GameOver.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"GameOver.wav", RT_RCDATA)));
    this->Sound[1].setBuffer(this->SoundBuffer[1]);

        for(int Z =0; Z <4; Z ++) this->Keyboard[Z] =false;

    this->Direction =true;
    this->X =0;
    this->Y =0;
    this->Life =600;
    }

    void Player::Move(int Level[], sf::Event Event) {
        if(this->Life >=120) {
        int Current =this->Y /64 *64 +this->X /64;

            if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Up) this->Keyboard[0] =1;
            else if(Event.type ==sf::Event::KeyReleased && Event.key.code ==sf::Keyboard::Up) this->Keyboard[0] =0;
            if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Down) this->Keyboard[1] =1;
            else if(Event.type ==sf::Event::KeyReleased && Event.key.code ==sf::Keyboard::Down) this->Keyboard[1] =0;
            if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Right) this->Keyboard[2] =1;
            else if(Event.type ==sf::Event::KeyReleased && Event.key.code ==sf::Keyboard::Right) this->Keyboard[2] =0;
            if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Left) this->Keyboard[3] =1;
            else if(Event.type ==sf::Event::KeyReleased && Event.key.code ==sf::Keyboard::Left) this->Keyboard[3] =0;

            if(this->X %64 ==1) this->X --;
            else if(this->X %64) this->X +=this->X %2 ? -8 : 8, this->Sprite.setTextureRect(sf::IntRect((!(this->X %64) || this->X %256 <64 ? 0 : this->X %256 <128 ? 64 : this->X %256 <192 ? 128 : 192) +(this->Direction ? 0 : 64), 0, this->Direction ? 64 : -64, 64));
            else if(this->Keyboard[2] && !(this->Y %64) && Level[Current +1] %8 !=1 && Level[Current +1] %8 !=2) this->X +=8, this->Direction =true;
            else if(this->Keyboard[3] && !(this->Y %64) && Level[Current -1] %8 !=1 && Level[Current -1] %8 !=2) this->X -=7, this->Direction =false;
            else if(this->Y %64 ==1) this->Y --;
            else if(this->Y %64) this->Y +=this->Y %2 ? -8 : 8, this->Sprite.setTextureRect(sf::IntRect((!(this->Y %64) || this->Y %256 <64 ? 0 : this->Y %256 <128 ? 64 : this->Y %256 <192 ? 128 : 192) +(this->Direction ? 0 : 64), 0, this->Direction ? 64 : -64, 64));
            else if(this->Keyboard[0] && !(this->X %64) && Level[Current -64] %8 !=1 && Level[Current -64] %8 !=2) this->Y -=7;
            else if(this->Keyboard[1] && !(this->X %64) && Level[Current +64] %8 !=1 && Level[Current +64] %8 !=2) this->Y +=8;
            else this->Sprite.setTextureRect(sf::IntRect(this->Direction ? 0 : 64, 0, this->Direction ? 64 : -64, 64));
        }
    }

    void Player::Draw(sf::RenderWindow *Window, int X, int Y) {
        if(this->Life ==119) this->Sprite.setTextureRect(sf::IntRect(256, 0, 64, 64)), this->Sound[1].play();
        if((this->Life %120 || this->Life <120) && this->Life !=-60) this->Life --;

        if(X && Y) this->Sprite.move(this->X -X, this->Y -Y);
        if(this->Life %4 <2 && this->Life !=-60) Window->draw(this->Sprite);
        if(X && Y) this->Sprite.move(X -this->X, Y -this->Y);
    }

    void Player::Hit(bool Death) {
        if(Death) this->Life =-60;
        else if(!(this->Life %120) && this->Life >=120) {
        this->Life --;
        this->Sound[0].play();
        }
    }

    void Player::WinLife() {
        if(this->Life <600) this->Life +=120;
    }

    const int Player::Get_X() {
        return this->X;
    }

    const int Player::Get_Y() {
        return this->Y;
    }

    const int Player::Get_Lives() {
        return this->Life;
    }

    void Player::Set_XY(int X, int Y) {
    this->X =X;
    this->Y =Y;
    }
