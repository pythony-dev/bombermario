
#include <windows.h>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Play.hpp"

    std::time_t Creating(sf::RenderWindow *Window, int ID) {
    sf::Texture Texture;
    Texture.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Creating.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Creating.png", RT_RCDATA)));
    sf::Sprite Sprite(Texture);

    sf::RectangleShape Shape_1(sf::Vector2f(1922, 1082)), Shape_3(sf::Vector2f(30, 30));
    Shape_1.setFillColor(sf::Color::Black);
    Shape_3.setFillColor(sf::Color(159, 159, 159, 191));
    sf::CircleShape Shape_2(0, 60);
    Shape_2.setFillColor(sf::Color::Black);

    sf::Music Music;
    Music.setLoop(true);
    Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Creating.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Creating.ogg", RT_RCDATA)));

    sf::SoundBuffer SoundBuffer[4];
    SoundBuffer[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_25.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_25.wav", RT_RCDATA)));
    SoundBuffer[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_26.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_26.wav", RT_RCDATA)));
    SoundBuffer[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_27.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_27.wav", RT_RCDATA)));
    SoundBuffer[3].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_28.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_28.wav", RT_RCDATA)));
    sf::Sound Sound_1(SoundBuffer[0]), Sound_2(SoundBuffer[1]), Sound_3(SoundBuffer[2]), Sound_4(SoundBuffer[3]);

    sf::Event Event;

    bool Player =false;
    int Level[4096] ={0}, Time =30;

    std::ifstream Stream_1(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
    Stream_1.seekg(0, std::ios::end);

        if((int)Stream_1.tellg() ==164339) {
        Stream_1.seekg(ID *4106 +107, std::ios::beg);
        char File[4096] ={0};
        Stream_1 >> File;

            for(int Z =0; Z <4096; Z ++) Level[Z] =File[Z] -(File[Z] >='0' && File[Z] <='9' ? '0' : File[Z] >='A' && File[Z] <='F' ? 'A' -10 : File[Z]);
        }

    Stream_1.close();
    Music.play();

        while(Window->isOpen() && Shape_1.getSize().x !=1920) {
            if(Window->pollEvent(Event) && Event.type ==sf::Event::Closed) Window->close();

            else if(Shape_2.getRadius() ==1104) Music.stop(), Play(Window, -ID -1), Shape_2.setRadius(1089), Music.play();
            else if(Shape_2.getRadius() ==1088 || Shape_1.getSize().x ==1888) {
            std::fstream Stream_2(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
            Stream_2.seekg(0, std::ios::end);

                if((int)Stream_2.tellg() ==164339) {
                Stream_2.seekg(0, std::ios::beg);
                char File[164339] ={0};

                    for(int Z =0; Z <164339; Z ++) Stream_2.get(File[Z]);

                Stream_2.seekg(0, std::ios::beg);

                    for(int Z =0; Z <8; Z ++) File[105 +ID *4106 -Z] =(std::time(0) >>Z *4) %16, File[105 +ID *4106 -Z] +=File[105 +ID *4106 -Z] >=0 && File[105 +ID *4106 -Z] <=9 ? '0' : File[105 +ID *4106 -Z] >=10 && File[105 +ID *4106 -Z] <=15 ? 'A' -10 : '0' -File[105 +ID *4106 -Z];
                    for(int Z =0; Z <4096; Z ++) File[107 +ID *4106 +Z] =Level[Z] +(Level[Z] >=0 && Level[Z] <=9 ? '0' : Level[Z] >=10 && Level[Z] <=15 ? 'A' -10 : '0' -Level[Z]);
                    for(int Z =0; Z <164339; Z ++) Stream_2.put(File[Z]);
                }
            }

            else if(Shape_1.getSize().x ==2) Shape_1.setSize(sf::Vector2f(0, 0));
            else if(Shape_2.getRadius() ==1) Shape_2.setRadius(0);
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && Time ==30 && !Shape_1.getSize().x && !Shape_2.getRadius()) {
            int Test[4096] ={0}, Start =0, Finish =0;

                for(int Z =0; Z <4096; Z ++) {
                Test[Z] =Level[Z];

                    if(Test[Z] ==3) Test[Z] =-1, Start ++;
                    else if(Level[Z] ==4) Finish ++;
                }

            bool Continue =true, Close =true, Terminable =false;

                while(Continue && Close && Start ==1 && Finish ==1) {
                Continue =false;

                    for(int Z =0; Z <4096; Z ++) {
                        if(Test[Z] ==-1 && Test[Z -1] !=-1 && Test[Z -1] !=1 && Test[Z -1] !=9) Test[Z -1] =-1, Continue =true;
                        if(Test[Z] ==-1 && Test[Z +1] !=-1 && Test[Z +1] !=1 && Test[Z +1] !=9) Test[Z +1] =-1, Continue =true;
                        if(Test[Z] ==-1 && Test[Z -64] !=-1 && Test[Z -64] !=1 && Test[Z -64] !=9) Test[Z -64] =-1, Continue =true;
                        if(Test[Z] ==-1 && Test[Z +64] !=-1 && Test[Z +64] !=1 && Test[Z +64] !=9) Test[Z +64] =-1, Continue =true;
                        if(Test[Z] ==-1 && (Z <64 || Z >4031 || Z %64 ==0 || Z %64 ==63)) Close =false;
                        if(Level[Z] ==4 && (Test[Z -1] ==-1 || Test[Z +1] ==-1 || Test[Z -64] ==-1 || Test[Z +64] ==-1)) Terminable =true;
                    }
                }

                if(Close && Terminable && Start ==1 && Finish ==1) Shape_2.setRadius(16);
                else Time =0, Sound_4.play();
            } else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Escape || Event.key.code ==sf::Keyboard::BackSpace) && !Shape_1.getSize().x && !Shape_2.getRadius()) Shape_1.setSize(sf::Vector2f(32, 18)), Music.stop(), Sound_1.play();

            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Right && Time >5 && !Shape_1.getSize().x && !Shape_2.getRadius() && Shape_3.getPosition().x !=1890) Shape_3.move(30, 0), Time =1, Sound_2.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Left && Time >5 && !Shape_1.getSize().x && !Shape_2.getRadius() && Shape_3.getPosition().x !=0) Shape_3.move(-30, 0), Time =1, Sound_2.play();
            else if(Shape_3.getPosition().y ==960 && !Player) Shape_3.move(0, -840), Player =true;
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Down && Time >5 && !Shape_1.getSize().x && !Shape_2.getRadius() && Shape_3.getPosition().y !=1050) Shape_3.move(0, 30), Time =1, Sound_2.play();
            else if(Shape_3.getPosition().y ==90 && Player) Shape_3.move(0, 840), Player =false;
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Up && Time >5 && !Shape_1.getSize().x && !Shape_2.getRadius() && Shape_3.getPosition().y !=0) Shape_3.move(0, -30), Time =1, Sound_2.play();
            else if(Time !=30) Time ++;

            if(Event.type ==sf::Event::KeyPressed) {
            int Choice_1 =Player *1792 +(int)(Shape_3.getPosition().y /30) *64 +Shape_3.getPosition().x /30, Choice_2 =Level[Choice_1];

                if(Event.key.code ==sf::Keyboard::A) Level[Choice_1] =0;
                else if(Event.key.code ==sf::Keyboard::Z) Level[Choice_1] =1;
                else if(Event.key.code ==sf::Keyboard::E) Level[Choice_1] =2;
                else if(Event.key.code ==sf::Keyboard::R) Level[Choice_1] =3;
                else if(Event.key.code ==sf::Keyboard::T) Level[Choice_1] =4;
                else if(Event.key.code ==sf::Keyboard::Y) Level[Choice_1] =5;
                else if(Event.key.code ==sf::Keyboard::U) Level[Choice_1] =6;
                else if(Event.key.code ==sf::Keyboard::I) Level[Choice_1] =7;
                else if(Event.key.code ==sf::Keyboard::Q) Level[Choice_1] =8;
                else if(Event.key.code ==sf::Keyboard::S) Level[Choice_1] =9;
                else if(Event.key.code ==sf::Keyboard::D) Level[Choice_1] =10;
                else if(Event.key.code ==sf::Keyboard::F) Level[Choice_1] =11;
                else if(Event.key.code ==sf::Keyboard::G) Level[Choice_1] =12;
                else if(Event.key.code ==sf::Keyboard::H) Level[Choice_1] =13;
                else if(Event.key.code ==sf::Keyboard::J) Level[Choice_1] =14;
                else if(Event.key.code ==sf::Keyboard::K) Level[Choice_1] =15;
                if(Level[Choice_1] !=Choice_2) Sound_2.stop(), Sound_3.play();
            }

        Window->clear(sf::Color::Black);

            for(int X =0; X <64; X ++) {
                for(int Y =0; Y <64; Y ++) Sprite.setPosition(X *30, Y *30), Sprite.setTextureRect(sf::IntRect(Level[Player *1792 +Y *64 +X] *30, 0, 30, 30)), Window->draw(Sprite);
            }

        Window->draw(Shape_3);

            if(Shape_1.getSize().x) Shape_1.setSize(sf::Vector2f(Shape_1.getSize().x +((int)Shape_1.getSize().x %32 ? -32 : 32), Shape_1.getSize().y +((int)Shape_1.getSize().x %32 ? -18 : 18))), Shape_1.setPosition(960 -Shape_1.getSize().x /2, 540 -Shape_1.getSize().y /2), Window->draw(Shape_1);
            else if(Shape_2.getRadius()) Shape_2.setRadius(Shape_2.getRadius() +((int)Shape_2.getRadius() %2 ? -16 : 16)), Shape_2.setPosition(960 -Shape_2.getRadius(), 540 -Shape_2.getRadius()), Window->draw(Shape_2);

        Window->display();
        }

    return std::time(0);
    }
