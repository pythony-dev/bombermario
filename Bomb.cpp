
#include <windows.h>
#include <cmath>

#include "Bomb.hpp"

    Bomb::Bomb(int Time, int X, int Y) {
    this->Texture.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Bomb.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Bomb.png", RT_RCDATA)));
    this->SoundBuffer.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Bomb.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Bomb.wav", RT_RCDATA)));
    this->Time =Time;
    this->X =X;
    this->Y =Y;
    }

    void Bomb::Draw(sf::RenderWindow *Window, Player Player, int Level[]) {
    this->Sprite.setTexture(this->Texture);
    this->Sprite.setPosition(this->X -Player.Get_X() +928, this->Y -Player.Get_Y() +508);

        if(this->Time ==1) this->Sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        else if(this->Time ==30) this->Sprite.setTextureRect(sf::IntRect(64, 0, 64, 64)), this->Sound.setBuffer(this->SoundBuffer), this->Sound.play();
        else if(this->Time ==37) this->Sprite.setTextureRect(sf::IntRect(128, 0, 64, 64));
        else if(this->Time ==45) this->Sprite.setTextureRect(sf::IntRect(192, 0, 64, 64));
        else if(this->Time ==52) this->Sprite.setTextureRect(sf::IntRect(256, 0, 64, 64));

    Window->draw(this->Sprite);

        if(this->Time >=30) {
        int Current =this->Y /64 *64 +this->X /64;

            if(Level[Current -1] %8 !=1) this->Sprite.move(-64, 0), Window->draw(this->Sprite), this->Sprite.move(64, 0);
            if(Level[Current +1] %8 !=1) this->Sprite.move(64, 0), Window->draw(this->Sprite), this->Sprite.move(-64, 0);
            if(Level[Current -64] %8 !=1) this->Sprite.move(0, -64), Window->draw(this->Sprite), this->Sprite.move(0, 64);
            if(Level[Current +64] %8 !=1) this->Sprite.move(0, 64), Window->draw(this->Sprite), this->Sprite.move(0, -64);
        }

    this->Time ++;
    }

    void Bomb::Destroy(int Level[], std::vector<Enemy> *Enemy, sf::Sound *Sound_1, sf::Sound *Sound_2, int *NewScore) {
    int Current =this->Y /64 *64 +this->X /64;

        if(NewScore !=NULL) {
            if(Level[Current] %8 ==2) *NewScore +=1;
            if(Level[Current -1] %8 ==2) *NewScore +=1;
            if(Level[Current +1] %8 ==2) *NewScore +=1;
            if(Level[Current -64] %8 ==2) *NewScore +=1;
            if(Level[Current +64] %8 ==2) *NewScore +=1;
        }

        if(Level[Current] %8 ==2) Level[Current] -=2, Sound_1->play();
        if(Level[Current -1] %8 ==2) Level[Current -1] -=2, Sound_1->play();
        if(Level[Current +1] %8 ==2) Level[Current +1] -=2, Sound_1->play();
        if(Level[Current -64] %8 ==2) Level[Current -64] -=2, Sound_1->play();
        if(Level[Current +64] %8 ==2) Level[Current +64] -=2, Sound_1->play();

        if(this->Time >=30) {
            for(int Z =0; Z <Enemy->size(); Z ++) {
                if(pow((*Enemy)[Z].Get_X() -this->X, 2) +pow((*Enemy)[Z].Get_Y() -this->Y, 2) <=4096) {
                Enemy->erase(Enemy->begin() +Z);

                    if(NewScore !=NULL) *NewScore +=20;

                Sound_2->play();
                }
            }
        }
    }

    const int Bomb::Get_Time() {
        return this->Time;
    }

    const int Bomb::Get_X() {
        return this->X;
    }

    const int Bomb::Get_Y() {
        return this->Y;
    }

    void Bomb::Set_XY(int X, int Y) {
    this->Time =1;
    this->X =X;
    this->Y =Y;
    }
