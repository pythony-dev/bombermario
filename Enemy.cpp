
#include <windows.h>
#include <cmath>

#include "Enemy.hpp"

    static bool CantMove(int Level, bool Type) {
        return (!Type || Level !=10) && Level <13 && Level !=8;
    }

    Enemy::Enemy(bool Type, int X, int Y, int Speed) {
    this->Type =Type;

        if(!this->Type) this->Texture.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Enemy_1.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Enemy_1.png", RT_RCDATA)));
        else this->Texture.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Enemy_2.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Enemy_2.png", RT_RCDATA)));

    this->X =X;
    this->Y =Y;
    this->Direction =-1;
    this->Speed =Speed <=1 ? 2 : Speed ==2 ? 4 : 8;
    }

    void Enemy::Draw(sf::RenderWindow *Window, int Level[], Player *Player) {
    int Direction =this->Direction;

        if(!(this->X %64) && !(this->Y %64)) this->Direction =-1;

        while(this->Direction ==-1) {
        this->Direction =rand() %6 +1;

            if(this->Direction ==5) this->Direction =this->X >Player->Get_X() ? 2 : 1;
            else if(this->Direction ==6) this->Direction =this->Y >Player->Get_Y() ? 4 : 3;

        int Current =this->Y /64 *64 +this->X /64;

            if(CantMove(Level[Current +1], this->Type) && CantMove(Level[Current -1], this->Type) && CantMove(Level[Current +64], this->Type) && CantMove(Level[Current -64], this->Type)) this->Direction =0;
            else if(CantMove(Level[Current -1], this->Type) && CantMove(Level[Current +64], this->Type) && CantMove(Level[Current -64], this->Type)) this->Direction =1;
            else if(CantMove(Level[Current +1], this->Type) && CantMove(Level[Current +64], this->Type) && CantMove(Level[Current -64], this->Type)) this->Direction =2;
            else if(CantMove(Level[Current +1], this->Type) && CantMove(Level[Current -1], this->Type) && CantMove(Level[Current -64], this->Type)) this->Direction =3;
            else if(CantMove(Level[Current +1], this->Type) && CantMove(Level[Current -1], this->Type) && CantMove(Level[Current +64], this->Type)) this->Direction =4;
            else if(this->Direction -(Direction %2 ? 1 : -1) ==Direction || CantMove(Level[Current +(this->Direction ==1 ? 1 : this->Direction ==2 ? -1 : this->Direction ==3 ? +64 : -64)], this->Type)) this->Direction =-1;
        }

        if(this->Direction ==1) this->X +=this->Speed;
        else if(this->Direction ==2) this->X -=this->Speed;
        else if(this->Direction ==3) this->Y +=this->Speed;
        else if(this->Direction ==4) this->Y -=this->Speed;

        if(!(Player->Get_Lives() %120) && pow(Player->Get_X() -this->X, 2) +pow(Player->Get_Y() -this->Y, 2) <1024) Player->Hit();

    this->Sprite.setTexture(this->Texture);
    this->Sprite.setPosition(this->X -Player->Get_X() +928, this->Y -Player->Get_Y() +508);

    int X =!(this->X %64) || this->X %256 <64 ? 0 : this->X %256 <128 ? 64 : this->X %256 <192 ? 128 : 192;
    int Y =!(this->Y %64) || this->Y %256 <64 ? 0 : this->Y %256 <128 ? 64 : this->Y %256 <192 ? 128 : 192;

        if(this->Direction %2) this->Sprite.setTextureRect(sf::IntRect(X +Y, 0, 64, 64));
        else this->Sprite.setTextureRect(sf::IntRect(X +Y +64, 0, -64, 64));

    Window->draw(this->Sprite);
    }

    const int Enemy::Get_X() {
        return this->X;
    }

    const int Enemy::Get_Y() {
        return this->Y;
    }
