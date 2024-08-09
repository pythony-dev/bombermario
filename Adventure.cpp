
#include <windows.h>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Play.hpp"

    void Adventure(sf::RenderWindow *Window) {
    sf::Texture Texture[7];
    Texture[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Adventure.jpg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Adventure.jpg", RT_RCDATA)));
    Texture[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Choice_2.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Choice_2.png", RT_RCDATA)));
    Texture[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Medal_1.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Medal_1.png", RT_RCDATA)));
    Texture[3].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Medal_2.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Medal_2.png", RT_RCDATA)));
    Texture[4].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Medal_3.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Medal_3.png", RT_RCDATA)));
    Texture[5].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Medal_4.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Medal_4.png", RT_RCDATA)));
    Texture[6].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Switch_1.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Switch_1.png", RT_RCDATA)));
    sf::Sprite Adventure(Texture[0]), Choice(Texture[1]), Medal_1(Texture[2]), Medal_2(Texture[3]), Medal_3(Texture[4]), Medal_4(Texture[5]), Switch(Texture[6]);
    Choice.setPosition(148, 808);

    sf::Font Font;
    Font.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Adventure.ttf", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Adventure.ttf", RT_RCDATA)));

    sf::CircleShape Shape_1(1089, 60);
    Shape_1.setFillColor(sf::Color::Black);
    sf::RectangleShape Shape_2(sf::Vector2f(0, 0));
    Shape_2.setFillColor(sf::Color::Black);

    sf::Music Music;
    Music.setLoop(true);
    Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Adventure.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Adventure.ogg", RT_RCDATA)));

    sf::SoundBuffer SoundBuffer[4];
    SoundBuffer[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_5.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_5.wav", RT_RCDATA)));
    SoundBuffer[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_6.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_6.wav", RT_RCDATA)));
    SoundBuffer[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_7.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_7.wav", RT_RCDATA)));
    SoundBuffer[3].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_8.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_8.wav", RT_RCDATA)));
    sf::Sound Sound_1(SoundBuffer[0]), Sound_2(SoundBuffer[1]), Sound_3(SoundBuffer[2]), Sound_4(SoundBuffer[3]);

    sf::Event Event;

    int Player =0, Medal[60] ={0};

    std::ifstream Stream_1(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
    Stream_1.seekg(0, std::ios::end);

        if((int)Stream_1.tellg() ==164339) {
        Stream_1.seekg(0, std::ios::beg);
        char File[60] ={0};
        Stream_1 >> File;

            for(int Z =0; Z <60; Z ++) Medal[Z] =File[Z] -(File[Z] >='0' && File[Z] <='9' ? '0' : File[Z] >='A' && File[Z] <='F' ? 'A' -10 : File[Z]);
        }

    Stream_1.close();
    Music.play();

        while(Window->isOpen() && Shape_1.getRadius() !=1104) {
            if(Window->pollEvent(Event) && Event.type ==sf::Event::Closed) Window->close();

        int ID =((int)((Choice.getPosition().x -148) /600) *20 +Player *5 +(808 -Choice.getPosition().y) /180);

            if(Shape_2.getSize().x ==1920) {
            Music.stop();
            int NewMedal =Play(Window, ID +1);

                if(NewMedal !=Medal[ID]) {
                Medal[ID] |=NewMedal;

                std::fstream Stream_2(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
                Stream_2.seekg(0, std::ios::end);

                    if((int)Stream_2.tellg() ==164339) {
                    Stream_2.seekg(0, std::ios::beg);
                    char File[164339] ={0};

                        for(int Z =0; Z <164339; Z ++) Stream_2.get(File[Z]);

                    Stream_2.seekg(0, std::ios::beg);
                    File[ID] =Medal[ID] +(Medal[ID] >=0 && Medal[ID] <=9 ? '0' : Medal[ID] >=10 && Medal[ID] <=15 ? 'A' -10 : '0' -Medal[ID]);

                        for(int Z =0; Z <164339; Z ++) Stream_2.put(File[Z]);
                    }
                }

            Shape_2.setSize(sf::Vector2f(1922, 1082));
            Music.play();
            }

            else if(Shape_1.getRadius() ==1) Shape_1.setRadius(0);
            else if(Shape_2.getSize().x ==2) Shape_2.setSize(sf::Vector2f(0, 0));
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && (int)Choice.getPosition().x %600 ==148 && (int)Choice.getPosition().y %180 ==88 && (Medal[ID -1] & 0x1 || (Choice.getPosition().y ==808 && !Player)) && !Shape_1.getRadius() && !Shape_2.getSize().x) Shape_2.setSize(sf::Vector2f(32, 18));
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && !Sound_4.getStatus() && (int)Choice.getPosition().x %600 ==148 && (int)Choice.getPosition().y %180 ==88 && !Shape_1.getRadius() && !Shape_2.getSize().x) Sound_4.play();
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Escape || Event.key.code ==sf::Keyboard::BackSpace) && !Shape_1.getRadius() && !Shape_2.getSize().x) Shape_1.setRadius(16), Music.stop(), Sound_1.play();

            else if((int)Choice.getPosition().x %600 ==149) Choice.move(-1, 0);
            else if((int)Choice.getPosition().x %600 !=148) Choice.move((int)Choice.getPosition().x %2 ? -16 : 16, 0);
            else if(Choice.getPosition().y ==-75) Choice.move(0, 1156), Player ++, Sound_3.play();
            else if(Choice.getPosition().y ==1084) Choice.move(0, -1156), Player --, Sound_3.play();
            else if((int)Choice.getPosition().y %180 ==89) Choice.move(0, -1);
            else if((int)Choice.getPosition().y %180 !=88 || Choice.getPosition().y >808) Choice.move(0, (int)Choice.getPosition().y %2 ? -16 : 16);

            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Up && (Choice.getPosition().y !=88 || Player !=3) && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice.move(0, -3), Sound_2.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Down && (Choice.getPosition().y !=808 || Player !=0) && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice.move(0, 4), Sound_2.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Right && Choice.getPosition().x !=1348 && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice.move(8, 0), Sound_2.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Left && Choice.getPosition().x !=148 && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice.move(-7, 0), Sound_2.play();

        Window->clear(sf::Color::Black);
        Window->draw(Adventure);
        Window->draw(Choice);

            for(int X =0; X <3; X ++) {
                for(int Y =0; Y <5; Y ++) {
                sf::Text Text("Niveau " +std::to_string(X *20 +Player *5 +Y +1), Font, 32);

                    if(X *20 +Player *5 +Y <9) Text.move(259 +X *600, 798 -Y *180);
                    else if(X *20 +Player *5 +Y <99) Text.move(245 +X *600, 798 -Y *180);
                    else Text.move(232 +X *600, 798 -Y *180);

                    if(Medal[X *20 +Player *5 +Y -1] & 0x1 || (!Player && !Y)) Text.setColor(sf::Color::Black);
                    else Text.setColor(sf::Color(0, 0, 0, 63));

                Window->draw(Text);

                    if(Medal[X *20 +Player *5 +Y] & 0x1) Medal_1.setPosition(248 +X *600, 846 -Y *180), Window->draw(Medal_1);
                    if((Medal[X *20 +Player *5 +Y] & 0x2) >>1) Medal_2.setPosition(312 +X *600, 846 -Y *180), Window->draw(Medal_2);
                    if((Medal[X *20 +Player *5 +Y] & 0x4) >>2) Medal_3.setPosition(376 +X *600, 846 -Y *180), Window->draw(Medal_3);
                    if((Medal[X *20 +Player *5 +Y] & 0x8) >>3) Medal_4.setPosition(440 +X *600, 846 -Y *180), Window->draw(Medal_4);
                }
            }

            if(Choice.getPosition().y <88 || Choice.getPosition().y >808) {
                if((Choice.getPosition().y >29 && Choice.getPosition().y <88) || (Choice.getPosition().y >808 && Choice.getPosition().y <867)) Switch.setTextureRect(sf::IntRect(0, 0, 96, 96));
                else if((Choice.getPosition().y >-19 && Choice.getPosition().y <30) || (Choice.getPosition().y >866 && Choice.getPosition().y <915)) Switch.setTextureRect(sf::IntRect(96, 0, 96, 96));
                else if((Choice.getPosition().y >-67 && Choice.getPosition().y <-18) || (Choice.getPosition().y >914 && Choice.getPosition().y <963)) Switch.setTextureRect(sf::IntRect(192, 0, 96, 96));
                else if(Choice.getPosition().y <-66 || Choice.getPosition().y >962) Switch.setTextureRect(sf::IntRect(288, 0, 96, 96));

                for(int X =0; X <3; X ++) {
                    for(int Y =0; Y <5; Y ++) {
                        for(int Z =0; Z <5; Z ++) Switch.setPosition(148 +X *600 +82 *Z, 792 -Y *180), Window->draw(Switch);
                    }
                }
            }

            if(Shape_1.getRadius()) Shape_1.setRadius(Shape_1.getRadius() +((int)Shape_1.getRadius() %2 ? -16 : 16)), Shape_1.setPosition(960 -Shape_1.getRadius(), 540 -Shape_1.getRadius()), Window->draw(Shape_1);
            else if(Shape_2.getSize().x) Shape_2.setSize(sf::Vector2f(Shape_2.getSize().x +((int)Shape_2.getSize().x %32 ? -32 : 32), Shape_2.getSize().y +((int)Shape_2.getSize().x %32 ? -18 : 18))), Shape_2.setPosition(960 -Shape_2.getSize().x /2, 540 -Shape_2.getSize().y /2), Window->draw(Shape_2);

        Window->display();
        }
    }
