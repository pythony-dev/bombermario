
#include <windows.h>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Play.hpp"

    void Endless(sf::RenderWindow *Window) {
    sf::Texture Texture[5];
    Texture[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Endless.jpg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Endless.jpg", RT_RCDATA)));
    Texture[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Menu_2.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Menu_2.png", RT_RCDATA)));
    Texture[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Choice_3.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Choice_3.png", RT_RCDATA)));
    Texture[3].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Choice_4.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Choice_4.png", RT_RCDATA)));
    Texture[4].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Menu_3.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Menu_3.png", RT_RCDATA)));
    sf::Sprite Endless(Texture[0]), Menu_1(Texture[1]), Choice_1(Texture[2]), Choice_2(Texture[3]), Menu_2(Texture[4]);
    Menu_1.setPosition(0, -1080);
    Choice_1.setPosition(521, 643);
    Choice_2.setPosition(510, -357);
    Menu_2.setPosition(960, 540);

    sf::Font Font;
    Font.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Endless.ttf", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Endless.ttf", RT_RCDATA)));
    sf::Text Text_1("", Font, 24), Text_2("", Font, 48);
    Text_1.setColor(sf::Color::Black);
    Text_2.setColor(sf::Color::Black);

    sf::CircleShape Shape_1(1089, 60);
    Shape_1.setFillColor(sf::Color::Black);
    sf::RectangleShape Shape_2(sf::Vector2f(0, 0));
    Shape_2.setFillColor(sf::Color::Black);

    sf::Music Music;
    Music.setLoop(true);
    Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Endless.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Endless.ogg", RT_RCDATA)));

    sf::SoundBuffer SoundBuffer[8];
    SoundBuffer[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_9.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_9.wav", RT_RCDATA)));
    SoundBuffer[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_10.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_10.wav", RT_RCDATA)));
    SoundBuffer[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_11.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_11.wav", RT_RCDATA)));
    SoundBuffer[3].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_12.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_12.wav", RT_RCDATA)));
    SoundBuffer[4].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_13.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_13.wav", RT_RCDATA)));
    SoundBuffer[5].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_14.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_14.wav", RT_RCDATA)));
    SoundBuffer[6].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_15.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_15.wav", RT_RCDATA)));
    SoundBuffer[7].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_16.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_16.wav", RT_RCDATA)));
    sf::Sound Sound_1(SoundBuffer[0]), Sound_2(SoundBuffer[1]), Sound_3(SoundBuffer[2]), Sound_4(SoundBuffer[3]), Sound_5(SoundBuffer[4]), Sound_6(SoundBuffer[5]), Sound_7(SoundBuffer[6]), Sound_8(SoundBuffer[7]);

    sf::Event Event;

    int Level[6] ={0}, Score[6] ={0}, Session =0, Player =1, Wait =0, Current =0;

    std::ifstream Stream_1(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
    Stream_1.seekg(0, std::ios::end);

        if((int)Stream_1.tellg() ==164339) {
        Stream_1.seekg(61, std::ios::beg);
        char File[36] ={0};
        Stream_1 >> File;

            for(int Z =0; Z <36; Z ++) File[Z] -=File[Z] >='0' && File[Z] <='9' ? 48 : File[Z] >='A' && File[Z] <='F' ? 55 : File[Z];
            for(int Z =0; Z <6; Z ++) Level[Z] =File[Z *6] *16 +File[Z *6 +1], Score[Z] =File[Z *6 +2] *4096 +File[Z *6 +3] *256 +File[Z *6 +4] *16 +File[Z *6 +5];
        }

    Stream_1.close();
    Music.play();

        while(Window->isOpen() && Shape_1.getRadius() !=1104) {
            if(Window->pollEvent(Event) && Event.type ==sf::Event::Closed) Window->close();

            else if(Shape_2.getSize().x ==1920) {
            Music.stop();
            int ID =Choice_1.getPosition().x /480 +(Choice_1.getPosition().y ==643 ? 0 : 3) -1, NewLevel =0, NewScore =0;

                while(Play(Window, (int)(Choice_1.getPosition().x /480) *20 +std::rand() %20 -19, Session, Player, &NewLevel, &NewScore));

                if(Menu_1.getPosition().y !=-1080) Menu_2.setPosition(960, 540), Menu_1.setPosition(0, -1080), Choice_1.move(0, -1080), Choice_2.move(0, -1080);

                if(NewLevel >Level[ID] || (NewLevel ==Level[ID] && NewScore >Score[ID])) {
                Level[ID] =NewLevel, Score[ID] =NewScore;

                std::fstream Stream_2(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
                Stream_2.seekg(0, std::ios::end);

                    if((int)Stream_2.tellg() ==164339) {
                    Stream_2.seekg(0, std::ios::beg);
                    char File[164339] ={0};

                        for(int Z =0; Z <164339; Z ++) Stream_2.get(File[Z]);

                    Stream_2.seekg(0, std::ios::beg);

                        for(int Z =0; Z <6; Z ++) File[66 +ID *6 -Z] =(Z <4 ? Score[ID] >>Z *4 : Level[ID] >>(Z -4) *4) %16, File[66 +ID *6 -Z] +=(File[66 +ID *6 -Z] >=0 && File[66 +ID *6 -Z] <=9 ? '0' : File[66 +ID *6 -Z] >=10 && File[66 +ID *6 -Z] <=15 ? 'A' -10 : '0' -File[66 +ID *6 -Z]);
                        for(int Z =0; Z <164339; Z ++) Stream_2.put(File[Z]);
                    }
                }

            Shape_2.setSize(sf::Vector2f(1922, 1082));
            Music.play();
            Session =0;
            }

            else if(Menu_1.getPosition().y ==-1080) {
                if(Shape_1.getRadius() ==1) Shape_1.setRadius(0);
                else if(Shape_2.getSize().x ==2) Shape_2.setSize(sf::Vector2f(0, 0));
                else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && Choice_1.getPosition().y ==238 && (int)Choice_1.getPosition().x %480 ==41 && !Shape_1.getRadius() && !Shape_2.getSize().x) Menu_1.move(0, 16), Choice_1.move(0, 16), Choice_2.move(0, 16), Sound_3.play();
                else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && Choice_1.getPosition().y ==643 && (int)Choice_1.getPosition().x %480 ==41 && !Shape_1.getRadius() && !Shape_2.getSize().x) Shape_2.setSize(sf::Vector2f(32, 18));
                else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Escape || Event.key.code ==sf::Keyboard::BackSpace) && !Shape_1.getRadius() && !Shape_2.getSize().x) Shape_1.setRadius(16), Music.stop(), Sound_1.play();

                else if((int)Choice_1.getPosition().x %480 ==42) Choice_1.move(-1, 0);
                else if((int)Choice_1.getPosition().x %480 !=41) Choice_1.move((int)Choice_1.getPosition().x %2 ? 16 : -16, 0);
                else if(Choice_1.getPosition().y ==244) Choice_1.move(0, -6);
                else if(Choice_1.getPosition().y ==638) Choice_1.move(0, 5);
                else if((int)Choice_1.getPosition().y %405 !=238) Choice_1.move(0, (int)Choice_1.getPosition().y %4 ? 16 : -16);

                else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Right && Choice_1.getPosition().x !=1481 && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice_1.move(16, 0), Sound_2.play();
                else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Left && Choice_1.getPosition().x !=521 && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice_1.move(-15, 0), Sound_2.play();
                else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Up && Choice_1.getPosition().y ==643 && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice_1.move(0, -15), Sound_2.play();
                else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Down && Choice_1.getPosition().y ==238 && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice_1.move(0, 16), Sound_2.play();
            }

            else if(!Menu_1.getPosition().y) {
                if(Menu_2.getPosition().x ==481) Menu_2.move(-1, -1);
                else if(Menu_2.getPosition().x !=480 && Menu_2.getPosition().x !=960) Menu_2.move((int)Menu_2.getPosition().x %2 ? -8 : 8, (int)Menu_2.getPosition().x %2 ? -8 : 8);

                else if(Menu_2.getPosition().x ==480) {
                    if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Escape || Event.key.code ==sf::Keyboard::BackSpace)) Session =0, Current =0, Menu_2.move(8, 8), Sound_7.play();

                    else if(Current ==4) {
                    Current =0;

                        for(int Z =3; Z !=-1; Z --) Session +=(Text_2.getString()[65 +Z] -(Text_2.getString()[65 +Z] >='0' && Text_2.getString()[65 +Z] <='9' ? 48 : 55)) *(Z ==3 ? 1 : Z ==2 ? 16 : Z ==1 ? 256 : 4096);

                    sf::Http Http("http://www.pythony.dev");
                    sf::Http::Request Request("/BomberMario/Application/CreatePlayer.php?Session=" +std::to_string(Session));
                    sf::Http::Response Response =Http.sendRequest(Request);

                        if(Response.getStatus() ==sf::Http::Response::Ok && std::atoi(Response.getBody().c_str()) >1 && std::atoi(Response.getBody().c_str()) <5) Player =std::atoi(Response.getBody().c_str()), Text_2.setString(Text_2.getString().substring(2, 67) +"\n\n\n  2 joueurs actuellement en ligne.\n\n         En attente du meneur...");
                        else Text_2.setString(Text_2.getString().substring(0, 65) +"0000\n\n\n         Identifiant incorrecte !"), Session =0;
                    }

                    else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && Choice_2.getPosition().y ==261 && Text_2.getString()[144] !='1' && !Shape_2.getSize().x) {
                    sf::Http Http("http://www.pythony.dev");
                    sf::Http::Request Request("/BomberMario/Application/StartSession.php?Session=" +std::to_string(Session));
                    sf::Http::Response Response =Http.sendRequest(Request);
                    }

                    else if(Session && Wait >59 && !Shape_2.getSize().x) {
                    Wait =0;
                    sf::Http Http("http://www.pythony.dev");
                    sf::Http::Request Request("/BomberMario/Application/GetStart.php?Session=" +std::to_string(Session) +"&Player=" +std::to_string(Player));
                    sf::Http::Response Response =Http.sendRequest(Request);

                        if(Response.getStatus() ==sf::Http::Response::Ok && Response.getBody()[0] =='1') Shape_2.setSize(sf::Vector2f(32, 18));
                        else if(Response.getStatus() ==sf::Http::Response::Ok && Response.getBody()[0] =='0' && Response.getBody()[1] >'1' && Response.getBody()[1] <'5') {
                        std::string String =Text_2.getString();

                            if(Choice_2.getPosition().y ==261 && String[144] =='1' && Response.getBody()[1] !='1') String.erase(143, 1), String.insert(151, "s");

                        String[Choice_2.getPosition().y ==723 ? 72 : 143] =Response.getBody()[1];
                        Text_2.setString(String);
                        } else if(Response.getBody()[1] !='1') Session =0, Current =0, Menu_2.move(8, 8), Sound_7.play();
                    }

                    else if(Choice_2.getPosition().y ==723) {
                    std::string String =Text_2.getString();

                        if(Current !=4 && Event.type ==sf::Event::KeyPressed) {
                            if(Event.key.code ==sf::Keyboard::Num0) String[65 +Current] ='0', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::Num1) String[65 +Current] ='1', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::Num2) String[65 +Current] ='2', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::Num3) String[65 +Current] ='3', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::Num4) String[65 +Current] ='4', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::Num5) String[65 +Current] ='5', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::Num6) String[65 +Current] ='6', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::Num7) String[65 +Current] ='7', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::Num8) String[65 +Current] ='8', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::Num9) String[65 +Current] ='9', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::A) String[65 +Current] ='A', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::B) String[65 +Current] ='B', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::C) String[65 +Current] ='C', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::D) String[65 +Current] ='D', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::E) String[65 +Current] ='E', Current ++, Sound_8.play();
                            else if(Event.key.code ==sf::Keyboard::F) String[65 +Current] ='F', Current ++, Sound_8.play();
                        }

                    Text_2.setString(String);
                    }
                }

                else {
                    if(Event.type ==sf::Event::KeyPressed &&  (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && (int)Choice_2.getPosition().y %462 ==261) Menu_2.move(-7, -7), Sound_6.play();
                    else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Escape || Event.key.code ==sf::Keyboard::BackSpace)) Menu_1.move(0, -15), Choice_1.move(0, -15), Choice_2.move(0, -15), Sound_4.play();
                    else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Up && Choice_2.getPosition().y ==723) Choice_2.move(0, -15), Sound_5.play();
                    else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Down && Choice_2.getPosition().y ==261) Choice_2.move(0, 16), Sound_5.play();
                }

                if(Menu_2.getPosition().x ==953 && Choice_2.getPosition().y ==723) Text_2.setString("\n\n\n Entrez un identifiant de session :\n\n\n                        0000");

                else if(Menu_2.getPosition().x ==953 && Choice_2.getPosition().y ==261) {
                sf::Http Http("http://www.pythony.dev");
                sf::Http::Request Request("/BomberMario/Application/CreateSession.php?Level=" +std::to_string((int)(Choice_1.getPosition().x /480) *20 +std::rand() %20 -19));
                sf::Http::Response Response =Http.sendRequest(Request);

                    if(Response.getStatus() ==sf::Http::Response::Ok && std::atoi(Response.getBody().c_str()) >0 && std::atoi(Response.getBody().c_str()) <65536) {
                    Session =std::atoi(Response.getBody().c_str()), Player =1;
                    std::string Hexadecimal;

                        for(int Z =0; Z <4; Z ++) Hexadecimal.push_back((Session >>(3 -Z) *4) %16), Hexadecimal[Z] =Hexadecimal[Z] <10 ? Hexadecimal[Z] +48 : Hexadecimal[Z] +55;

                    Text_2.setString("Voici votre identifiant de session :\n\n\n                        " +Hexadecimal +"\n\n\n       Partagez-le avec vos amis \n            pour jouer en ligne. \n\n\n   1 joueur actuellement en ligne.");
                    } else Text_2.setString("\n\n\n\n          Erreur de connexion !\n\n    Veuillez relancer une session.");
                }

                if(Menu_2.getScale().x !=1 -(Menu_2.getPosition().x -480) /480) Menu_2.setScale(1 -(Menu_2.getPosition().x -480) /480, 1 -(Menu_2.getPosition().x -480) /480), Text_2.setPosition((int)960 -398 *Menu_2.getScale().x, (int)540 -273 *Menu_2.getScale().x), Text_2.setScale(Menu_2.getScale());
            }

            else {
                if(Menu_1.getPosition().y ==8) Menu_1.move(0, -8), Choice_1.move(0, -8), Choice_2.move(0, -8);
                else if(Menu_1.getPosition().y ==-1071) Menu_1.move(0, -9), Choice_1.move(0, -9), Choice_2.move(0, -9);
                else if((int)Menu_1.getPosition().y %1080) Menu_1.move(0, (int)Menu_1.getPosition().y %2 ? -16 : 16), Choice_1.move(0, (int)Menu_1.getPosition().y %2 ? -16 : 16), Choice_2.move(0, (int)Menu_1.getPosition().y %2 ? -16 : 16);
            }

            if(Choice_2.getPosition().y -Menu_1.getPosition().y ==276) Choice_2.move(0, -15);
            else if(Choice_2.getPosition().y -Menu_1.getPosition().y ==709) Choice_2.move(0, 14);
            else if((int)(Choice_2.getPosition().y -Menu_1.getPosition().y) %462 !=261) Choice_2.move(0, (int)(Choice_2.getPosition().y -Menu_1.getPosition().y) %2 ? 16 : -16);

        Window->clear(sf::Color::Black);
        Window->draw(Endless);
        Window->draw(Menu_1);

            for(int X =0; X <3; X ++) {
                for(int Y =0; Y <2; Y ++) {
                Text_1.setString("Niveau : " +std::to_string(Level[3 -Y *3 +X]));
                Text_1.setPosition(622 +X *480 -(int)(std::to_string(Level[3 -Y *3 +X]).length() *7.25), 1348 +Y *405 +Menu_1.getPosition().y);
                Window->draw(Text_1);
                Text_1.setString("Score : " + std::to_string(Score[3 -Y *3 +X]));
                Text_1.setPosition(630 +X *480 -(int)(std::to_string(Score[3 -Y *3 +X]).length() *7.25), 1396 +Y *405 +Menu_1.getPosition().y);
                Window->draw(Text_1);
                }
            }

            if(Menu_1.getPosition().y) Window->draw(Choice_1);
            if(Menu_1.getPosition().y !=-1080) Window->draw(Choice_2);
            if(Menu_2.getPosition().x <960) Window->draw(Menu_2), Window->draw(Text_2);

            if(Shape_1.getRadius()) Shape_1.setRadius(Shape_1.getRadius() +((int)Shape_1.getRadius() %2 ? -16 : 16)), Shape_1.setPosition(960 -Shape_1.getRadius(), 540 -Shape_1.getRadius()), Window->draw(Shape_1);
            else if(Shape_2.getSize().x) Shape_2.setSize(sf::Vector2f(Shape_2.getSize().x +((int)Shape_2.getSize().x %32 ? -32 : 32), Shape_2.getSize().y +((int)Shape_2.getSize().x %32 ? -18 : 18))), Shape_2.setPosition(960 -Shape_2.getSize().x /2, 540 -Shape_2.getSize().y /2), Window->draw(Shape_2);

        Window->display();
        Wait ++;
        }
    }
