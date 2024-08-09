
#include <windows.h>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Creating.hpp"

    void Editor(sf::RenderWindow *Window) {
    sf::Texture Texture[3];
    Texture[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Editor.jpg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Editor.jpg", RT_RCDATA)));
    Texture[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Choice_5.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Choice_5.png", RT_RCDATA)));
    Texture[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Switch_2.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Switch_2.png", RT_RCDATA)));
    sf::Sprite Editor(Texture[0]), Choice(Texture[1]), Switch(Texture[2]);
    Choice.move(65, 930);

    sf::Font Font;
    Font.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Editor.ttf", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Editor.ttf", RT_RCDATA)));
    sf::Text Text("", Font, 20);
    Text.setColor(sf::Color::Black);

    sf::CircleShape Shape_1(1089, 60);
    Shape_1.setFillColor(sf::Color::Black);
    sf::RectangleShape Shape_2(sf::Vector2f(0, 0));
    Shape_2.setFillColor(sf::Color::Black);

    sf::Music Music;
    Music.setLoop(true);
    Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Editor.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Editor.ogg", RT_RCDATA)));

    sf::SoundBuffer SoundBuffer[3];
    SoundBuffer[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_17.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_17.wav", RT_RCDATA)));
    SoundBuffer[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_18.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_18.wav", RT_RCDATA)));
    SoundBuffer[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_19.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_19.wav", RT_RCDATA)));
    sf::Sound Sound_1(SoundBuffer[0]), Sound_2(SoundBuffer[1]), Sound_3(SoundBuffer[2]);

    sf::Event Event;

    bool Player =false;
    char Date[40][23] ={0};

    std::ifstream Stream(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
    Stream.seekg(0, std::ios::end);

        if((int)Stream.tellg() ==164339) {
            for(int Z1 =0; Z1 <40; Z1 ++) {
            Stream.seekg(Z1 *4106 +98, std::ios::beg);
            char File[8] ={0};
            std::time_t Timestamp =0;
            Stream >> File;

                for(int Z2 =0; Z2 <8; Z2 ++) Timestamp +=(File[Z2] -(File[Z2] >='0' && File[Z2] <='9' ? 48 : File[Z2] >='A' && File[Z2] <='F' ? 55 : File[Z2])) <<(15 -Z2) *4;

            strftime(Date[Z1], sizeof(Date[Z1]), "%d/%m/%y\n\n%H:%M:%S", localtime(&Timestamp));
            }
        }

    Stream.close();
    Music.play();

        while(Window->isOpen() && Shape_1.getRadius() !=1104) {
            if(Window->pollEvent(Event) && Event.type ==sf::Event::Closed) Window->close();

            else if(Shape_2.getSize().x ==1920) {
            Music.stop();
            int ID =(int)Choice.getPosition().x /373 *8 +Player *4 -(int)Choice.getPosition().y /259 +3;

            std::time_t Timestamp =Creating(Window, ID);
            strftime(Date[ID], sizeof(Date[ID]), "%d/%m/%y\n\n%H:%M:%S", localtime(&Timestamp));

            Shape_2.setSize(sf::Vector2f(1922, 1082));
            Music.play();
            }

            else if(Shape_1.getRadius() ==1) Shape_1.setRadius(0);
            else if(Shape_2.getSize().x ==2) Shape_2.setSize(sf::Vector2f(0, 0));
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && (int)Choice.getPosition().x %373 ==65 && (int)Choice.getPosition().y %259 ==153 && !Shape_1.getRadius() && !Shape_2.getSize().x) Shape_2.setSize(sf::Vector2f(32, 18));
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Escape || Event.key.code ==sf::Keyboard::BackSpace) && !Shape_1.getRadius() && !Shape_2.getSize().x) Shape_1.setRadius(16), Music.stop(), Sound_1.play();

            else if((int)Choice.getPosition().x %373 ==60) Choice.move(5, 0);
            else if((int)Choice.getPosition().x %373 ==70) Choice.move(-5, 0);
            else if((int)Choice.getPosition().x %373 !=65) Choice.move((int)Choice.getPosition().x %373 >65 ==(int)Choice.getPosition().x %373 %2 ? 16 : -16, 0);
            else if((int)Choice.getPosition().y %259 ==150) Choice.move(0, 3);
            else if((int)Choice.getPosition().y %259 ==156) Choice.move(0, -3);
            else if(Choice.getPosition().y ==-71) Choice.move(0, 1222), Player =true, Sound_3.play();
            else if(Choice.getPosition().y ==1154) Choice.move(0, -1238), Player =false, Sound_3.play();
            else if((int)Choice.getPosition().y %259 !=153) Choice.move(0, (int)Choice.getPosition().y %259 >153 ==(int)Choice.getPosition().y %259 %2 ? 16 : -16);

            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Up && (Choice.getPosition().y !=153 || !Player) && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice.move(0, -16), Sound_2.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Down && (Choice.getPosition().y !=930 || Player) && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice.move(0, 16), Sound_2.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Right && Choice.getPosition().x !=1557 && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice.move(16, 0), Sound_2.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Left && Choice.getPosition().x !=65 && !Shape_1.getRadius() && !Shape_2.getSize().x) Choice.move(-16, 0), Sound_2.play();

        Window->clear(sf::Color::Black);
        Window->draw(Editor);

            for(int X =0; X <5; X ++) {
                for(int Y =0; Y <4; Y ++) {
                Text.setString("Niveau " +std::to_string(X *8 +Player *4 -Y +4));

                    if(Date[X *8 +Player *4 -Y +3][6] <'7') Text.setString(Text.getString() +"\n\n\n" +Date[X *8 +Player *4 -Y +3]);

                Text.setPosition(X *373 +149, Y *259 +85);
                Window->draw(Text);
                }
            }

        Window->draw(Choice);

            if(Choice.getPosition().y <153 || Choice.getPosition().y >930) {
                if((Choice.getPosition().y >96 && Choice.getPosition().y <153) || (Choice.getPosition().y >930 && Choice.getPosition().y <987)) Switch.setTextureRect(sf::IntRect(0, 0, 64, 64));
                else if((Choice.getPosition().y >40 && Choice.getPosition().y <97) || (Choice.getPosition().y >986 && Choice.getPosition().y <1043)) Switch.setTextureRect(sf::IntRect(64, 0, 64, 64));
                else if((Choice.getPosition().y >-16 && Choice.getPosition().y <41) || (Choice.getPosition().y >1042 && Choice.getPosition().y <1099)) Switch.setTextureRect(sf::IntRect(128, 0, 64, 64));
                else if(Choice.getPosition().y <-15 || Choice.getPosition().y >1098) Switch.setTextureRect(sf::IntRect(192, 0, 64, 64));

                for(int X_1 =0; X_1 <5; X_1 ++) {
                    for(int Y_1 =0; Y_1 <4; Y_1 ++) {
                        for(int X_2 =0; X_2 <4; X_2 ++) {
                            for(int Y_2 =0; Y_2 <3; Y_2 ++) Switch.setPosition(81 +X_1 *373 +X_2 *67 +(X_2 >1 ? 1 : 0), 59 +Y_1 *259 +Y_2 *61), Window->draw(Switch);
                        }
                    }
                }
            }

            if(Shape_1.getRadius()) Shape_1.setRadius(Shape_1.getRadius() +((int)Shape_1.getRadius() %2 ? -16 : 16)), Shape_1.setPosition(960 -Shape_1.getRadius(), 540 -Shape_1.getRadius()), Window->draw(Shape_1);
            else if(Shape_2.getSize().x) Shape_2.setSize(sf::Vector2f(Shape_2.getSize().x +((int)Shape_2.getSize().x %32 ? -32 : 32), Shape_2.getSize().y +((int)Shape_2.getSize().x %32 ? -18 : 18))), Shape_2.setPosition(960 -Shape_2.getSize().x /2, 540 -Shape_2.getSize().y /2), Window->draw(Shape_2);

        Window->display();
        }
    }
