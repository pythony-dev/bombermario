
#include <windows.h>
#include <fstream>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Loading.hpp"

#include "Player.hpp"
#include "Bomb.hpp"
#include "Enemy.hpp"

    void GetItems(int Session, int ID, Player Players[], sf::Vector2i *Bomb, bool *Continue) {
    bool PlayerBomb[4] ={false};

        while(*Continue) {
        sf::Http Http("http://www.pythony.dev");
        sf::Http::Request Request("/BomberMario/Application/GetItems.php?Session=" +std::to_string(Session));
        sf::Http::Response Response =Http.sendRequest(Request);
        std::string Items =Response.getBody();

        bool IsBomb[4] ={false};

            if(Response.getStatus() ==sf::Http::Response::Ok && std::atoi(Response.getBody().c_str()) >0) {
                while(Items.size() >0 && Items.size() >Items.find(" ")) {
                int Z =std::atoi(Items.c_str());
                Items =Items.substr(Items.find(" ") +1);

                    if(Items.size() >0 && Items.size() >Items.find(" ")) {
                    int X =std::atoi(Items.c_str());
                    Items =Items.substr(Items.find(" ") +1);

                        if(Items.size() >0 && Items.size() >Items.find(" ")) {
                        int Y =std::atoi(Items.c_str());
                        Items =Items.substr(Items.find(" ") +1);

                            for(int Z2 =0; Z2 <4; Z2 ++) {

                                if(Z -1 ==Z2 && Z !=ID) Players[Z -1].Set_XY(X, Y);
                                else if(Z -5 ==Z2 && ID -1 !=Z2 && !PlayerBomb[Z2]) *Bomb ={X, Y}, PlayerBomb[Z2] =true, IsBomb[Z2] =true;
                                else if(Z -5 ==Z2) IsBomb[Z2] =true;
                            }
                        }
                    }
                }

                for(int Z =0; Z <4; Z ++) if(!IsBomb[Z]) PlayerBomb[Z] =false;

            }

        sf::sleep(sf::seconds(1));
        }
    }

    void GetLevel(int Session, int *Level, bool *Continue) {
        while(*Continue) {
        sf::Http Http("http://www.pythony.dev");
        sf::Http::Request Request("/BomberMario/Application/GetLevel.php?Session=" +std::to_string(Session));
        sf::Http::Response Response =Http.sendRequest(Request);

            if(Response.getStatus() ==sf::Http::Response::Ok && std::atoi(Response.getBody().c_str()) >0 && std::atoi(Response.getBody().c_str()) <61 && std::atoi(Response.getBody().c_str()) !=*Level) *Level =0;

        sf::sleep(sf::seconds(1));
        }
    }

    void SetPlayer(int Session, int ID, Player *Player, bool *Continue) {
        while(*Continue) {
        sf::Http Http("http://www.pythony.dev");
        sf::Http::Request Request("/BomberMario/Application/SetPlayer.php?Session=" +std::to_string(Session) +"&Player=" +std::to_string(ID) +"&X=" +std::to_string(Player->Get_X()) +"&Y=" +std::to_string(Player->Get_Y()));
        Http.sendRequest(Request);
        sf::sleep(sf::seconds(1));
        }
    }

    void SetBomb(int Session, int ID, int X, int Y) {
    sf::Http Http("http://www.pythony.dev");
    sf::Http::Request Request("/BomberMario/Application/CreateBomb.php?Session=" +std::to_string(Session) +"&Player=" +std::to_string(ID) +"&X=" +std::to_string(X) +"&Y=" +std::to_string(Y));
    Http.sendRequest(Request);
    }

    void RemoveBomb(int Session, int ID) {
    sf::Http Http("http://www.pythony.dev");
    sf::Http::Request Request("/BomberMario/Application/RemoveBomb.php?Session=" +std::to_string(Session) +"&Player=" +std::to_string(ID));
    Http.sendRequest(Request);
    }

    int Play(sf::RenderWindow *Window, int LevelID, int Session, int PlayerID, int *NewLevel, int *NewScore) {
    sf::Vector2i ThreadBomb(0, 0);

    bool Mode[2] ={false};

    std::ifstream Stream_1(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
    Stream_1.seekg(0, std::ios::end);

        if((int)Stream_1.tellg() ==164339) {
        Stream_1.seekg(-1, std::ios::end);
        char File =0;
        Stream_1 >> File;
        File -=File >='0' && File <='7' ? '0' : File;
        Mode[0] =(File >>1) %2;
        Mode[1] =(File >>2) %2;
        }

    Stream_1.close();

    sf::Texture Texture[6];

        if((LevelID +19) /20 ==1 || LevelID <=0) Texture[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Tileset_1.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Tileset_1.png", RT_RCDATA)));
        else if((LevelID +19) /20 ==2) Texture[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Tileset_2.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Tileset_2.png", RT_RCDATA)));
        else Texture[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Tileset_3.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Tileset_3.png", RT_RCDATA)));

        if(!Mode[0]) Texture[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Background_1.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Background_1.png", RT_RCDATA)));
        else Texture[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Background_2.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Background_2.png", RT_RCDATA)));

    Texture[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Fireworks_1.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Fireworks_1.png", RT_RCDATA)));
    Texture[3].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Fireworks_2.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Fireworks_2.png", RT_RCDATA)));
    Texture[4].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Fireworks_3.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Fireworks_3.png", RT_RCDATA)));
    Texture[5].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Fireworks_4.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Fireworks_4.png", RT_RCDATA)));
    sf::Sprite Tileset(Texture[0]), Background(Texture[1]), Fireworks_1(Texture[2]), Fireworks_2(Texture[3]), Fireworks_3(Texture[4]), Fireworks_4(Texture[5]);
    Background.setPosition(0, 984);

    sf::Font Font;
    Font.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Background.ttf", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Background.ttf", RT_RCDATA)));
    sf::Text Text("", Font, 64);
    Text.setColor(LevelID <41 ? sf::Color::Black : sf::Color(127, 127, 127));

    sf::RectangleShape Shape(sf::Vector2f(1922, 1082));
    Shape.setFillColor(sf::Color::Black);

    sf::Music Music;
    Music.setLoop(true);

        if(rand() %5 ==4) Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Level_1.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Level_1.ogg", RT_RCDATA)));
        else if(rand() %4 ==3) Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Level_2.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Level_2.ogg", RT_RCDATA)));
        else if(rand() %3 ==2) Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Level_3.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Level_3.ogg", RT_RCDATA)));
        else if(rand() %2 ==1) Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Level_4.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Level_4.ogg", RT_RCDATA)));
        else Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Level_5.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Level_5.ogg", RT_RCDATA)));

    sf::SoundBuffer SoundBuffer[6];
    SoundBuffer[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Block.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Block.wav", RT_RCDATA)));
    SoundBuffer[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Enemy.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Enemy.wav", RT_RCDATA)));
    SoundBuffer[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Lives.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Lives.wav", RT_RCDATA)));
    SoundBuffer[3].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Stock.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Stock.wav", RT_RCDATA)));
    SoundBuffer[4].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Gem.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Gem.wav", RT_RCDATA)));
    SoundBuffer[5].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Fireworks.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Fireworks.wav", RT_RCDATA)));
    sf::Sound Sound_1(SoundBuffer[0]), Sound_2(SoundBuffer[1]), Sound_3(SoundBuffer[2]), Sound_4(SoundBuffer[3]), Sound_5(SoundBuffer[4]), Sound_6(SoundBuffer[5]);

    sf::Event Event;

    Player Players[4] ={1, 2, 3, 4};
    std::vector<Bomb> Bombs;
    std::vector<Enemy> Ennemis;

        while(Bombs.size() <10) Bombs.push_back(0);

    bool Continue =true;
    int Level[4096] ={0}, GemsCounter =0,  Gems =0, Fireworks =0;

        if(Session >0) {
        sf::Http Http("http://www.pythony.dev");
        sf::Http::Request Request("/BomberMario/Application/GetLevel.php?Session=" +std::to_string(Session));
        sf::Http::Response Response =Http.sendRequest(Request);

            if(Response.getStatus() ==sf::Http::Response::Ok && std::atoi(Response.getBody().c_str()) >0 && std::atoi(Response.getBody().c_str()) <61 && Response.getBody().size() -1 >Response.getBody().find(" ")) {
            std::string Level =Response.getBody();
            LevelID =std::atoi(Level.c_str());
            Level =Level.substr(Level.find(" ") +1);

                if(std::atoi(Level.c_str()) <4) Players[3].Hit(true);
                if(std::atoi(Level.c_str()) <3) Players[2].Hit(true);
            } else return 0;

        std::thread ThreadGetItems(GetItems, Session, PlayerID, Players, &ThreadBomb, &Continue), ThreadGetLevel(GetLevel, Session, &LevelID, &Continue), ThreadSetPlayer(SetPlayer, Session, PlayerID, &Players[PlayerID -1], &Continue);
        ThreadGetItems.detach();
        ThreadGetLevel.detach();
        ThreadSetPlayer.detach();
        } else Players[3].Hit(true), Players[2].Hit(true), Players[1].Hit(true);

        if(LevelID >0) Loading(Level, LevelID);
        else {
        std::ifstream Stream_2(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
        Stream_2.seekg(0, std::ios::end);

            if((int)Stream_2.tellg() ==164339) {
            Stream_2.seekg(abs(LevelID) *4106 -3999, std::ios::beg);
            char File[4096] ={0};

                for(int Z =0; Z <4096; Z ++) File[Z] =Stream_2.get();
                for(int Z =0; Z <4096; Z ++) Level[Z] =File[Z] -(File[Z] >='0' && File[Z] <='9' ? '0' : File[Z] >='A' && File[Z] <='F' ? 'A' -10 : File[Z]);
            } else return 0;
        }

        for(int Z =0; Z <4096; Z ++) {

            if(Level[Z] %8 ==7) GemsCounter ++;
            else if(Level[Z] ==11 || Level[Z] ==12) Ennemis.push_back(Enemy(Level[Z] ==12, Z %64 *64, Z /64 *64, LevelID >0 ? (LevelID +19) /20 : 2)), Level[Z] =8;
            else if(Level[Z] ==3) Players[0].Set_XY(Z %64 *64, Z /64 *64), Level[Z] =0;
        }

        if(Session >0) for(int Z =1; Z <4; Z ++) Players[Z].Set_XY(Players[0].Get_X(), Players[0].Get_Y());

        if(NewScore !=NULL) *NewScore +=50, (*NewLevel) ++;

    Music.play();

        while(Window->isOpen() && Shape.getSize().x !=1920 && LevelID !=0) {
            if(Window->pollEvent(Event) && Event.type ==sf::Event::Closed) Window->close();

        int Current =Players[PlayerID -1].Get_Y() /64 *64 +Players[PlayerID -1].Get_X() /64;

            if(Players[PlayerID -1].Get_Lives() ==-60 && !Shape.getSize().x) Shape.setSize(sf::Vector2f(32, 18));
            else if(Players[PlayerID -1].Get_Lives() ==118) Music.stop();
            else if(Shape.getSize().x ==2) Shape.setSize(sf::Vector2f(0, 0));
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && Bombs.size() >0 && !Bombs[0].Get_Time() && !Fireworks && Players[PlayerID -1].Get_Lives() >=120 && !Shape.getSize().x) {
            Bombs[0].Set_XY(Players[PlayerID -1].Get_X(), Players[PlayerID -1].Get_Y());

                if(Session >0) {
                std::thread ThreadSetBomb(&SetBomb, Session, PlayerID, Bombs[0].Get_X(), Bombs[0].Get_Y());
                ThreadSetBomb.detach();
                }
            }

            else if(Level[Current] %8 ==5) {
            Level[Current] -=5;
            Players[PlayerID -1].WinLife();
            Sound_3.play();

                if(NewScore !=NULL) *NewScore +=5;
            } else if(Level[Current] %8 ==6) {
                if(Bombs.size() <10) Sound_4.play();

                while(Bombs.size() <10) Bombs.push_back(0);
            } else if(Level[Current] %8 ==7) {
            Level[Current] -=7;
            Gems ++;
            Sound_5.play();

                if(NewScore !=NULL) *NewScore +=10;
            }

            for(int Z =0; Z <Bombs.size(); Z ++) {
                if(Bombs[Z].Get_Time() ==60) {
                Bombs.erase(Bombs.begin() +Z);

                    if(Session >0) {
                    std::thread ThreadRemoveBomb(&RemoveBomb, Session, PlayerID);
                    ThreadRemoveBomb.detach();
                    }
                } else if(Bombs[Z].Get_Time() >=30) Bombs[Z].Destroy(Level, &Ennemis, &Sound_1, &Sound_2, NewScore);
            }

            if(ThreadBomb.x !=0 && ThreadBomb.y !=0) Bombs.push_back(Bomb(1, ThreadBomb.x, ThreadBomb.y)), ThreadBomb ={0, 0};

        Window->clear(sf::Color::Black);

            for(int X =0; X <32; X ++) {
                for(int Y =0; Y <18; Y ++) {
                int Z =Current +Y *64 +X -527;
                bool IsLevel =X *64 +Players[PlayerID -1].Get_X() >956 && X *64 +Players[PlayerID -1].Get_X() <5056 && Z >=0 && Z <=4095;

                Tileset.setTextureRect(sf::IntRect(IsLevel && (Level[Z] !=4 || Gems *2 >=GemsCounter) ? Level[Z] *64 : 0, 0, 64, 64));
                Tileset.setPosition(X *64 -Players[PlayerID -1].Get_X() %64 -32, Y *64 -Players[PlayerID -1].Get_Y() %64 -4 +(!Mode[1] || (Level[Z] %8 !=1 && Level[Z] %8 !=2) || !IsLevel ? 0 : 32));
                Tileset.setScale(1, !Mode[1] || (Level[Z] %8 !=1 && Level[Z] %8 !=2) || !IsLevel ? 1 : .5);
                Window->draw(Tileset);
                }
            }

            for(int Z =0; Z <Bombs.size(); Z ++) if(Bombs[Z].Get_Time() >0) Bombs[Z].Draw(Window, Players[PlayerID -1], Level);

            for(int Z =0; Z <Ennemis.size(); Z ++) Ennemis[Z].Draw(Window, Level, &Players[PlayerID -1]);

            for(int Z =0; Z <4; Z ++) if(Players[Z].Get_Lives() !=-60) Players[Z].Draw(Window, PlayerID -1 !=Z ? Players[PlayerID -1].Get_X() : 0, PlayerID -1 !=Z ? Players[PlayerID -1].Get_Y() : 0);

            if(Mode[1]) {
            Tileset.setScale(1, 1);

                for(int X =0; X <32; X ++) {
                    for(int Y =0; Y <18; Y ++) {
                    int Z =Current +Y *64 +X -527;

                        if((Level[Z] %8 ==1 || Level[Z] %8 ==2) && X *64 +Players[PlayerID -1].Get_X() >956 && X *64 +Players[PlayerID -1].Get_X() <5056 && Z >=0 && Z <=4095) {
                        Tileset.setTextureRect(sf::IntRect(Level[Z] *64, 0, 64, 64));
                        Tileset.setPosition(X *64 -Players[PlayerID -1].Get_X() %64 -32, Y *64 -Players[PlayerID -1].Get_Y() %64 -36);
                        Window->draw(Tileset);
                        }
                    }
                }
            }

            if(!Mode[0]) {
            Window->draw(Background);

            int BombCounter =0;

                for(int Z =0; Z <Bombs.size(); Z ++) if(!Bombs[Z].Get_Time()) BombCounter ++;

            Text.setString("x " +std::to_string(BombCounter));
            Text.setPosition(318, 984);
            Window->draw(Text);

            Text.setString("x " +std::to_string(Gems));
            Text.setPosition(958, 984);
            Window->draw(Text);

            Text.setString("x " +(Players[PlayerID -1].Get_Lives() >=120 ? std::to_string(Players[PlayerID -1].Get_Lives() /120) : "0"));
            Text.setPosition(1598, 984);
            Window->draw(Text);
            } else {
            Background.setTextureRect(sf::IntRect(0, 0, 32, 32));

            int BombCounter =0;

                for(int Z =0; Z <Bombs.size(); Z ++) if(!Bombs[Z].Get_Time()) BombCounter ++;
                for(int Z =0; Z <BombCounter; Z ++) Background.setPosition(160 +Z *32, 1016), Window->draw(Background);

            Background.setTextureRect(sf::IntRect(32, 0, 32, 32));

                if(Gems <=10) for(int Z =0; Z <Gems; Z ++) Background.setPosition(800 +Z *32, 1016), Window->draw(Background);
                else Background.setPosition(800, 1016), Window->draw(Background), Text.setPosition(851, 984), Text.setString("x " +std::to_string(Gems)), Window->draw(Text);

            Background.setTextureRect(sf::IntRect(64, 0, 32, 32));

                if(Players[PlayerID -1].Get_Lives() >=120) for(int Z =0; Z <Players[PlayerID -1].Get_Lives() /120; Z ++) Background.setPosition(1440 +Z *32, 1016), Window->draw(Background);
            }

            if(NewScore !=NULL) Text.setPosition(557, 0), Text.setString("Niveau : " +std::to_string(*NewLevel) + " - Score : " +std::to_string(*NewScore)), Window->draw(Text);

            if(Level[Current] ==4 && Gems *2 >=GemsCounter && !(Players[PlayerID -1].Get_X() %64) && !(Players[PlayerID -1].Get_Y() %64)) {

                if(!Fireworks) Music.stop(), Sound_6.play();
                else if(Fireworks ==180) Shape.setSize(sf::Vector2f(32, 18));

                if(Fireworks %15 >=11) Fireworks_1.setTextureRect(sf::IntRect(768, 0, 256, 256)), Fireworks_2.setTextureRect(Fireworks_1.getTextureRect()), Fireworks_3.setTextureRect(Fireworks_1.getTextureRect()), Fireworks_4.setTextureRect(Fireworks_1.getTextureRect());
                else if(Fireworks %15 >=7) Fireworks_1.setTextureRect(sf::IntRect(512, 0, 256, 256)), Fireworks_2.setTextureRect(Fireworks_1.getTextureRect()), Fireworks_3.setTextureRect(Fireworks_1.getTextureRect()), Fireworks_4.setTextureRect(Fireworks_1.getTextureRect());
                else if(Fireworks %15 >=3) Fireworks_1.setTextureRect(sf::IntRect(256, 0, 256, 256)), Fireworks_2.setTextureRect(Fireworks_1.getTextureRect()), Fireworks_3.setTextureRect(Fireworks_1.getTextureRect()), Fireworks_4.setTextureRect(Fireworks_1.getTextureRect());
                else Fireworks_1.setTextureRect(sf::IntRect(0, 0, 256, 256)), Fireworks_2.setTextureRect(Fireworks_1.getTextureRect()), Fireworks_3.setTextureRect(Fireworks_1.getTextureRect()), Fireworks_4.setTextureRect(Fireworks_1.getTextureRect());

                if(!(Fireworks %15)) Fireworks_1.setPosition(rand() %1664, rand() %824), Fireworks_2.setPosition(rand() %1664, rand() %824), Fireworks_3.setPosition(rand() %1664, rand() %824), Fireworks_4.setPosition(rand() %1664, rand() %824);

            Window->draw(Fireworks_1);
            Window->draw(Fireworks_2);
            Window->draw(Fireworks_3);
            Window->draw(Fireworks_4);
            Fireworks ++;
            } else if(!Shape.getSize().x) Players[PlayerID -1].Move(Level, Event);

            if(Shape.getSize().x) Shape.setSize(sf::Vector2f(Shape.getSize().x +((int)Shape.getSize().x %32 ? -32 : 32), Shape.getSize().y +((int)Shape.getSize().x %32 ? -18 : 18))), Shape.setPosition(960 -Shape.getSize().x /2, 540 -Shape.getSize().y /2), Window->draw(Shape);

        Window->display();
        }

        if(!Window->isOpen()) return false;
        else if(LevelID >0 && NewScore ==NULL) {
        int Medal =1;

            if(!Ennemis.size()) Medal +=2;
            if(GemsCounter ==Gems) Medal +=4;
            if(Medal ==7 && Players[0].Get_Lives() ==600) Medal =15;

        return Players[0].Get_Lives() >=120 ? Medal : 0;
        }

        else if(Session >0) {
        Continue =false;

            if(Players[PlayerID -1].Get_Lives() >=120) {
            sf::Http Http("http://www.pythony.dev");
            sf::Http::Request Request("/BomberMario/Application/GetLevel.php?Session=" +std::to_string(Session));
            sf::Http::Response Response =Http.sendRequest(Request);

                if(Response.getStatus() ==sf::Http::Response::Ok && std::atoi(Response.getBody().c_str()) >0 && std::atoi(Response.getBody().c_str()) <61 && std::atoi(Response.getBody().c_str()) ==LevelID) {
                int NextLevel =LevelID;

                    while(NextLevel ==LevelID) NextLevel =LevelID /20 *20 +rand() %20 +1;

                sf::Http Http("http://www.pythony.dev");
                sf::Http::Request Request("/BomberMario/Application/SetLevel.php?Session=" +std::to_string(Session) +"&Level=" +std::to_string(NextLevel));
                Http.sendRequest(Request);
                }
            }
        }

    return Players[PlayerID -1].Get_Lives() >=120;
    }
