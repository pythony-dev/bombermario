
#include <windows.h>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Adventure.hpp"
#include "Endless.hpp"
#include "Editor.hpp"
#include "Settings.hpp"

    int main(int argc, char *argv[]) {
    sf::Http Http("http://www.anthony-khelil.fr");
    sf::Http::Request Request("/BomberMario/Application/Start.php?Version=Windows_1.2");
    Http.sendRequest(Request);

    std::srand((unsigned int)std::time(NULL));

    sf::Image Image;
    Image.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Icon.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Icon.png", RT_RCDATA)));

    sf::RenderWindow Window(sf::VideoMode(1920, 1080), "BomberMario");
    Window.setIcon(64, 64, Image.getPixelsPtr());
    Window.setVerticalSyncEnabled(true);
    Window.setFramerateLimit(60);

    sf::Texture Texture[3];
    Texture[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Background_1.jpg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Background_1.jpg", RT_RCDATA)));
    Texture[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Menu_1.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Menu_1.png", RT_RCDATA)));
    Texture[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Choice_1.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Choice_1.png", RT_RCDATA)));
    sf::Sprite Background(Texture[0]), Menu(Texture[1]), Choice(Texture[2]);
    Menu.setPosition(448, -855);
    Choice.setPosition(320, -855);

    sf::CircleShape Shape(0, 60);
    Shape.setFillColor(sf::Color::Black);

    sf::Music Music;
    Music.setLoop(true);
    Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Main.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Main.ogg", RT_RCDATA)));

    sf::SoundBuffer SoundBuffer[4];
    SoundBuffer[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_1.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_1.wav", RT_RCDATA)));
    SoundBuffer[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_2.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_2.wav", RT_RCDATA)));
    SoundBuffer[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_3.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_3.wav", RT_RCDATA)));
    SoundBuffer[3].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_4.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_4.wav", RT_RCDATA)));
    sf::Sound Sound_1(SoundBuffer[0]), Sound_2(SoundBuffer[1]), Sound_3(SoundBuffer[2]), Sound_4(SoundBuffer[3]);

    sf::Event Event;

    std::ifstream Stream_1(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
    Stream_1.seekg(0, std::ios::end);

        if((int)Stream_1.tellg() ==164339) {
        Stream_1.seekg(-1, std::ios::end);
        char File =0;
        Stream_1 >> File;

            if(!(File %2)) sf::Listener::setGlobalVolume(0);
        } else {
        char File[164339] ={0};

            for(int Z =0; Z <164339; Z ++) File[Z] =Z !=60 && Z %4106 !=97 && Z %4106 !=106 ? '0' : ' ';

        File[164338] ='1';
        std::ofstream Stream_2(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");

            for(int Z =0; Z <164339; Z ++) Stream_2.put(File[Z]);
        }

    Stream_1.close();
    Music.play();

        while(Window.isOpen()) {
            if((Window.pollEvent(Event) && Event.type ==sf::Event::Closed) || (Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Escape || Event.key.code ==sf::Keyboard::BackSpace) && Menu.getPosition().y ==-855)) Window.close();
            else if(Shape.getRadius() ==1104) {
                if(Choice.getPosition().y ==113) Adventure(&Window);
                else if(Choice.getPosition().y ==355) Endless(&Window);
                else if(Choice.getPosition().y ==597) Editor(&Window);
                else if(Choice.getPosition().y ==839) Settings(&Window);
                
                Music.play();
                Shape.setRadius(1089);
            }

            else if(Shape.getRadius() ==1) Shape.setRadius(0);
            else if(Menu.getPosition().y ==-854) Menu.move(0, -1), Choice.move(0, -1);
            else if(Menu.getPosition().y >-855 && Menu.getPosition().y <113) Menu.move(0, (int)Menu.getPosition().y %2 ? 16 : -16), Choice.move(0, (int)Menu.getPosition().y %2 ? 16 : -16);
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && Menu.getPosition().y ==-855) Menu.move(0, 8), Choice.move(0, 8), Sound_1.play();
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && Menu.getPosition().y ==113 && (int)Choice.getPosition().y %242 ==113 && !Shape.getRadius()) Shape.setRadius(Shape.getRadius() +16), Music.stop(), Sound_4.play();
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Escape || Event.key.code ==sf::Keyboard::BackSpace) && Menu.getPosition().y ==113 && !Shape.getRadius()) Menu.move(0, -7), Choice.move(0, -7), Sound_2.play();

            else if((int)(Choice.getPosition().y -Menu.getPosition().y) %242 ==1) Choice.move(0, -1);
            else if((int)(Choice.getPosition().y -Menu.getPosition().y) %242) Choice.move(0, (int)(Choice.getPosition().y -Menu.getPosition().y) %2 ? -16 : 16);
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Down && Menu.getPosition().y ==113 && (int)Choice.getPosition().y %242 ==113 && Choice.getPosition().y <839 && !Shape.getRadius()) Choice.move(0, 2), Sound_3.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Up && Menu.getPosition().y ==113 && (int)Choice.getPosition().y %242 ==113 && Choice.getPosition().y >113 && !Shape.getRadius()) Choice.move(0, -1), Sound_3.play();

        Window.clear(sf::Color::Black);
        Window.draw(Background);
        Window.draw(Menu);
        Window.draw(Choice);

            if(Shape.getRadius() >0) Shape.setRadius(Shape.getRadius() +((int)Shape.getRadius() %2 ? -16 : 16)), Shape.setPosition(960 -Shape.getRadius(), 540 -Shape.getRadius()), Window.draw(Shape);

        Window.display();
        }

    return EXIT_SUCCESS;
    }
