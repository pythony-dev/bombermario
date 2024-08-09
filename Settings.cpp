
#include <windows.h>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

    void Settings(sf::RenderWindow *Window) {
    sf::Texture Texture[3];
    Texture[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Settings.jpg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Settings.jpg", RT_RCDATA)));
    Texture[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Choice_6.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Choice_6.png", RT_RCDATA)));
    Texture[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Switch_3.png", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Switch_3.png", RT_RCDATA)));
    sf::Sprite Settings(Texture[0]), Choice(Texture[1]), Switch(Texture[2]);
    Choice.setPosition(474, 83);

    sf::Font Font;
    Font.loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Settings.ttf", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Settings.ttf", RT_RCDATA)));
    sf::Text Text("", Font, 32);
    Text.setColor(sf::Color::Black);

    sf::CircleShape Shape(1089, 60);
    Shape.setFillColor(sf::Color::Black);

    sf::Music Music;
    Music.setLoop(true);
    Music.openFromMemory(LoadResource(NULL, FindResource(NULL, L"Settings.ogg", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Settings.ogg", RT_RCDATA)));

    sf::SoundBuffer SoundBuffer[5];
    SoundBuffer[0].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_20.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_20.wav", RT_RCDATA)));
    SoundBuffer[1].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_21.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_21.wav", RT_RCDATA)));
    SoundBuffer[2].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_22.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_22.wav", RT_RCDATA)));
    SoundBuffer[3].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_23.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_23.wav", RT_RCDATA)));
    SoundBuffer[4].loadFromMemory(LoadResource(NULL, FindResource(NULL, L"Sound_24.wav", RT_RCDATA)), SizeofResource(NULL, FindResource(NULL, L"Sound_24.wav", RT_RCDATA)));
    sf::Sound Sound_1(SoundBuffer[0]), Sound_2(SoundBuffer[1]), Sound_3(SoundBuffer[2]), Sound_4(SoundBuffer[3]), Sound_5(SoundBuffer[4]);

    sf::Event Event;

    bool Player[3] ={true}, Reset =false;
    int Time =0;

    std::ifstream Stream_1(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
    Stream_1.seekg(0, std::ios::end);

        if((int)Stream_1.tellg() ==164339) {
        Stream_1.seekg(-1, std::ios::end);
        char File =0;
        Stream_1 >> File;

            for(int Z =0; Z <3; Z ++) Player[Z] =(File >>Z) %2;
        }

    Stream_1.close();
    Music.play();

        while(Window->isOpen() && Shape.getRadius() !=1104) {
            if(Window->pollEvent(Event) && Event.type ==sf::Event::Closed) Window->close();

            else if(Shape.getRadius() ==1) Shape.setRadius(0);
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Escape || Event.key.code ==sf::Keyboard::BackSpace) && !Shape.getRadius()) Shape.setRadius(16), Music.stop(), Sound_4.stop(), Sound_1.play();

            else if(Choice.getPosition().y ==78) Choice.move(0, 5);
            else if(Choice.getPosition().y ==323 || Choice.getPosition().y ==822) Choice.move(0, 9);
            else if(Choice.getPosition().y ==572) Choice.move(0, 10);
            else if(Choice.getPosition().y ==343) Choice.move(0, -11);
            else if(Choice.getPosition().y ==592) Choice.move(0, -10);
            else if((int)Choice.getPosition().y %249 !=83 && (int)Choice.getPosition().y %249 !=84) Choice.move(0, Choice.getPosition().y <582 ? Choice.getPosition().y <332 ==(int)Choice.getPosition().y %2 ? 16 : -16 : (int)Choice.getPosition().y %4 ==2 ? 16 : -16);

            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Down && ((int)Choice.getPosition().y %249 ==83 || (int)Choice.getPosition().y %249 ==84) && Choice.getPosition().y !=831 && !Shape.getRadius()) Choice.move(0, 16), Sound_2.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Up && ((int)Choice.getPosition().y %249 ==83 || (int)Choice.getPosition().y %249 ==84) && Choice.getPosition().y !=83 && !Shape.getRadius()) Choice.move(0, -15), Sound_2.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Right && !Player[0] && Choice.getPosition().y ==83 && !Shape.getRadius()) Player[0] =true, sf::Listener::setGlobalVolume(100);
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Left && Player[0] && Choice.getPosition().y ==83 && !Shape.getRadius()) Player[0] =false, sf::Listener::setGlobalVolume(0);
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Right && !Player[(int)Choice.getPosition().y /249] && ((int)Choice.getPosition().y %249 ==83 || (int)Choice.getPosition().y %249 ==84) && Choice.getPosition().y !=831 && !Shape.getRadius()) Player[(int)Choice.getPosition().y /249] =true, Sound_3.play();
            else if(Event.type ==sf::Event::KeyPressed && Event.key.code ==sf::Keyboard::Left && Player[(int)Choice.getPosition().y /249] && ((int)Choice.getPosition().y %249 ==83 || (int)Choice.getPosition().y %249 ==84) && Choice.getPosition().y !=831 && !Shape.getRadius()) Player[(int)Choice.getPosition().y /249] =false, Sound_3.play();

            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && Choice.getPosition().y ==831 && !Time && !Shape.getRadius()) Time =1, Sound_4.play();
            else if(Event.type ==sf::Event::KeyPressed && (Event.key.code ==sf::Keyboard::Space || Event.key.code ==sf::Keyboard::Return) && Choice.getPosition().y ==831 && Time >60 && !Shape.getRadius()) {
            char File[164339] ={0};

                for(int Z =0; Z <164339; Z ++) File[Z] =Z !=60 && Z %4106 !=97 && Z %4106 !=106 ? '0' : ' ';

            std::ofstream Stream_2(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");

                for(int Z =0; Z <164339; Z ++) Stream_2.put(File[Z]);

            Reset =true;
            Shape.setRadius(16);
            Music.stop();
            Sound_5.play();
            } else if(Time) Time ++;

        Window->clear(sf::Color::Black);
        Window->draw(Settings);
        Window->draw(Choice);

            for(int X =0; X <2; X ++) {
                for(int Y =0; Y <3; Y ++) {
                Text.setString(!Y ? X ? "Sons" : "Muet" : Y ==1 ? X ? "Vie en %" : "Vies x5" : X ? "3D" : "2D");
                Text.setCharacterSize(Player[Y] ==X ? 32 : 16);
                Text.setPosition(!Y ? Player[0] ? X ? 1024 : 818 : X ? 1060 : 818 : Y ==1 ? Player[1] ? X ? 994 : 796 : X ? 1052 : 798 : Player[2] ? X ? 1044 : 840 : X ? 1060 : 839, (Player[Y] ==X ? 146 : 157) +Y *249);
                Window->draw(Text);
                }
            }

        Text.setString(Time <31 ? "Effacer la sauvegarde" : "Confirmer l'effacement ?");
        Text.setCharacterSize(32);
        Text.setPosition(Time <31 ? 780 : 756, 894);
        Window->draw(Text);

            if(Time && Time <61) {
            Switch.setTextureRect(sf::IntRect((int)((Time <31 ? Time -1 : 60 -Time) /7.5) *64, 0, 64, 64));

                for(int Z =0; Z <8; Z ++) Switch.setPosition(704 +Z *64, 882), Window->draw(Switch);
            }

            if(Shape.getRadius()) Shape.setRadius(Shape.getRadius() +((int)Shape.getRadius() %2 ? -16 : 16)), Shape.setPosition(960 -Shape.getRadius(), 540 -Shape.getRadius()), Window->draw(Shape);

        Window->display();
        }

        if(Reset && Player[0] ==false) sf::Listener::setGlobalVolume(100);
        if(Reset) Player[0] =true, Player[1] =false, Player[2] =false;

    std::fstream Stream_2(std::string(getenv("HOMEPATH")) +"\\Saved Games\\BomberMario.sav");
    Stream_2.seekg(0, std::ios::end);

        if((int)Stream_2.tellg() ==164339) {
        Stream_2.seekg(0, std::ios::beg);
        char File[164339] ={0};

            for(int Z =0; Z <164339; Z ++) Stream_2.get(File[Z]);

        Stream_2.seekg(0, std::ios::beg);
        File[164338] ='0' +(Player[0] ? 1 : 0) +(Player[1] ? 2 : 0) +(Player[2] ? 4 : 0);

            for(int Z =0; Z <164339; Z ++) Stream_2.put(File[Z]);
        }
    }
