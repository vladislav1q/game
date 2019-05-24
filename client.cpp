#include "background.h"
#include "init.h"
#include "draw.h"
#include "thread"
#include "pages.h"
#include "wave.h"
#include "shadows.h"
#include "endGame.h"
#include <SFML/Network.hpp>
#include "network.h"

#pragma once

Mutex mutex;
int aim;
bool MusicPlay = false;

class Server{
public:
    Server(UdpSocket &socket, IpAddress ipServer, unsigned short portServer,
           std::vector<Weapon> &bullets, std::vector<Bomb> &bombs, std::vector<Feature> &items,
           Organism &player1,  Organism &player2, std::vector<Organism> &zombies, std::vector<Organism> &zombies1,
           std::vector<Organism> &zombies2, std::vector<Organism> &zombies3, std::vector<Organism> &dogs) :
            socket(socket),
            ipServer(ipServer),
            portServer(portServer),
            bullets(bullets),
            bombs(bombs),
            items(items),
            player1(player1),
            player2(player2),
            zombies(zombies),
            zombies1(zombies1),
            zombies2(zombies2),
            zombies3(zombies3),
            dogs(dogs){};

    UdpSocket &socket;
    IpAddress ipServer;
    unsigned short portServer;
    std::vector<Weapon> &bullets;
    std::vector<Bomb> &bombs;
    std::vector<Feature> &items;
    Organism &player1;
    Organism &player2;
    std::vector<Organism> &zombies;
    std::vector<Organism> &zombies1;
    std::vector<Organism> &zombies2;
    std::vector<Organism> &zombies3;
    std::vector<Organism> &dogs;
};

class ServerInfo{
public:
    ServerInfo(IpAddress ipServer, unsigned short portServer, UdpSocket &socket) :
    ipServer(ipServer), portServer(portServer), socket(socket){};

    IpAddress ipServer;
    unsigned short portServer;
    UdpSocket &socket;
};

void getFromServer(Server &A);
void sendMusic(ServerInfo serverInfo);
void getMusic(ServerInfo serverInfo);

//class MyCustomSoundRecorder : public sf::SoundRecorder{
//public:
//    static const Int16* MySamples;
//    static std::size_t MySamplesCount;
//protected:
//    virtual bool OnProcessSamples(const sf::Int16* Samples, std::size_t SamplesCount) override {
//        MySamples = Samples;
//        MySamplesCount = SamplesCount;
//        return true;
//    }
//
//};

class CustomRecorder : public sf::SoundRecorder
{
public:
    static const Int16* MySamples;
    static std::size_t MySamplesCount;
protected:
     bool onProcessSamples(const Int16* samples, std::size_t sampleCount) override
     {
         MySamples = samples;
         MySamplesCount = sampleCount;
         return true;
     }
};

class NoiseCancellor : public sf::SoundRecorder {
    bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
};

bool NoiseCancellor::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
    Int16* cancelSamples = new sf::Int16[sampleCount];

    for (size_t i = 0; i < sampleCount; ++i) {
        cancelSamples[i] = samples[i];
    }

    sf::SoundBuffer cancelBuffer;
    cancelBuffer.loadFromSamples(cancelSamples, sizeof(cancelSamples) * sampleCount, 1, getSampleRate());

    sf::Sound cancelSound(cancelBuffer);
    cancelSound.play();

    return true;
}



void runClient(WindowSent windowSent, unsigned short portServer, unsigned short portClient, sf::IpAddress ipServer){

    sizeWindow.x = 500;
    sizeWindow.y = 500;

    UdpSocket socket;
    Packet packet;

    unsigned int portServerMusic = portServer + 1;
    unsigned int portClientMusic = portClient + 1;
    UdpSocket socketMusic;

    if(socketMusic.bind(portClientMusic) != Socket::Done)
        return;
    if (socket.bind(portClient) != sf::Socket::Done)
        return;

    if (socket.send(packet, ipServer, portServer) != sf::Socket::Done)
        return;
    std::cout << "Message sent to the server: " << std::endl;

    if (socket.receive(packet, ipServer, portServer) != sf::Socket::Done)
        return;
    std::cout << "Message received from " << ipServer << std::endl;

    srand(time(NULL));
    musicAll.music[numberMusicGame].play();
    hard = windowSent.hard;

    float resolution = windowSent.mode.height / windowSent.mode.width;
    float thickness = 0.05;

    View gameView(sf::FloatRect(0, 0, windowSent.mode.width, windowSent.mode.height));
//    View minimapView;
//    FloatRect rect(1-minimapSize - thickness, 1-minimapSize - thickness, minimapSize, minimapSize);
//    minimapView.setViewport(rect);

    std::vector<Weapon> bullets;
    std::vector<Bomb> bombs;
    std::vector<Organism> zombies;
    std::vector<Organism> zombies1;
    std::vector<Organism> zombies2;
    std::vector<Organism> zombies3;
    std::vector<Organism> dogs;
    std::vector<Corpse> dead;
    std::vector<Feature> items;
    std::vector<Opaque> houses;
    std::vector<ConvexShape> trapezes;

    setTextures();
    initBackground();

    //Create PlayerSprite
    spritePlayer.setTexture(texturePlayerPaths[0]);
    //Create ZombieSprite
    spriteZombie.setTexture(textureZombiePathsWalkFullHealth[0]);
    //Create Zombie1Sprite
    spriteZombie1.setTexture(textureZombie1PathsWalkFullHealth[0]);
    spriteZombie1.setScale(3, 3);
    //Create Zombie2Sprite
    spriteZombie2.setTexture(textureZombie2PathsWalkFullHealth[0]);
    spriteZombie2.setScale(1.5, 1.5);
    //Create Zombie3prite
    spriteZombie3.setTexture(textureZombie3PathsWalkFullHealth[0]);
    spriteZombie3.setScale(1.5, 1.5);
    //Create DogSprite
    spriteDog.setTexture(textureDogPathsWalkFullHealth[0]);
    //Create BulletSprite
    textureBullet1.loadFromFile(pathToDirectory + "pngForGame/bullet1.png");
    spriteBullet1.setTexture(textureBullet1);
    textureBullet2.loadFromFile(pathToDirectory + "pngForGame/bullet2.png");
    spriteBullet2.setTexture(textureBullet2);
    //Create BombSprite
    textureBomb1.loadFromFile(pathToDirectory + "pngForGame/bomb1.png");
    spriteBomb1.setTexture(textureBomb1);
    textureBomb2.loadFromFile(pathToDirectory + "pngForGame/bomb2.png");
    spriteBomb2.setTexture(textureBomb2);
    //Create items Textures
    textureHeart.loadFromFile(pathToDirectory + "pngForGame/heart.png");
    textureShield.loadFromFile(pathToDirectory + "pngForGame/shield.png");
    textureBullet.loadFromFile(pathToDirectory + "pngForGame/bullets.png");
    textureBomb.loadFromFile(pathToDirectory + "pngForGame/bombs.png");
    //Create MouseSprite
    Sprite spriteCursor(textureCursor0);
    setCursor(windowSent.window, spriteCursor);
    //Create Location Texture
    textureLocation.loadFromFile(pathToDirectory + "pngForGame/location.png");
    Sprite location(textureLocation);
    location.setOrigin(location.getTexture()->getSize().x / 2.0, location.getTexture()->getSize().y);
    location.setScale(0.8, 0.8);
    //Create shadow
    Texture textureShadow;
    textureShadow.loadFromFile(pathToDirectory + "pngForGame/shadow.png");
    Sprite spriteShadow(textureShadow);
    spriteShadow.setOrigin(spriteShadow.getTexture()->getSize().x / 2, spriteShadow.getTexture()->getSize().y / 2);
    spriteShadow.setColor(Color(255, 255, 255, 180));
    spriteShadow.setScale(0.5, 0.5);
    //create corpseTexture
    textureCorpse.loadFromFile(corpsePath);
    //create bars
    Bar lifeBar(pathToDirectory + "pngForGame/heart.png", pathToDirectory + "fonts/font.ttf", Color(255, 0, 0, 255), 0.3);
    TimeBar timeBar(pathToDirectory + "fonts/font.ttf");
    Bar shieldBar(pathToDirectory + "pngForGame/shield.png", pathToDirectory + "fonts/font.ttf", Color(131, 131, 157, 255), 0.09);
    Bar bulletBar(pathToDirectory + "pngForGame/bullets.png", pathToDirectory + "fonts/font.ttf", Color(255, 204, 0, 255), 0.17);
    Bar bombBar(pathToDirectory + "pngForGame/bombs.png", pathToDirectory + "fonts/font.ttf", Color(25, 51, 77, 255), 0.07);
    Bar bubbleBar(pathToDirectory + "pngForGame/bubble.png", pathToDirectory + "fonts/font.ttf", Color(51, 255, 255, 255), 0.08);
    bubbleBar.value = fullBubbles;
    //Init Player
    texturePlayerInWater.loadFromFile(pathToDirectory + "pngForGame/playerInWater.png");

    packet.clear();
    std::cout << "Client is waiting for map: " << std::endl;
    for(int i = 0; i < sizeWindow.x; i++){
        socket.receive(packet, ipServer, portServer);
        unpackMap(packet, i);
        packet.clear();
    }
    std::cout << "Map unpacked by client: " << std::endl;

    Organism player1 = initPlayer();
    Organism player2 = initPlayer();


//    MinimapThread minimapThread;
//    Thread thread(&setMinimap, &minimapThread);
//    thread.launch();


    std::cout << "Client is waiting for trees: " << std::endl;
    socket.receive(packet, ipServer, portServer);
    unpackTrees(packet);
    packet.clear();
    std::cout << "Trees are unpacked by client: " << std::endl;

    std::cout << "Client is waiting for houses: " << std::endl;
    socket.receive(packet, ipServer, portServer);
    unpackHouses(packet, houses);
    packet.clear();
    std::cout << "Houses are unpacked by client: " << std::endl;

    std::cout << "Client is waiting for players: " << std::endl;
    socket.receive(packet, ipServer, portServer);
    unpackPlayers(packet, player1, player2);
    //unpack(packet, bullets, bombs, items, zombies, zombies1, zombies2, zombies3, dogs, houses, player1, player2);
    packet.clear();
    std::cout << "Players are unpacked by client: " << std::endl;

    aim = player1.aim;

    spriteShadow.setPosition(player1.organism.getPosition());
    gameView.setCenter(player1.organism.getPosition());

    Clock clock;
    Clock clockPause;
    Clock clock6;

    float timeBuffer6 = 0;
    float timeBuffer7 = 0;
    float timeBuffer8 = 0;
    float timeBuffer9 = 0;
    float timeBuffer10 = 0;
    float timeBufferBombInit = 0;
    float timebufferMinimapInit = 0;
    float timeBufferMinimap = 0;

    bool minimap = false;
    Time time,time6, timePause;
    timePause = clock6.restart();

    Draw2 A(windowSent.window, gameView, zombies, zombies1, zombies2, zombies3, dogs, dead, bullets, bombs, items, trapezes,
           player1, player2, lifeBar, bubbleBar, shieldBar, bulletBar, bombBar, timeBar, spriteCursor, spriteShadow);

    Server B(socket, ipServer, portServer, bullets, bombs, items, player1, player2,
             zombies, zombies1, zombies2, zombies3, dogs);
    Thread thread2(getFromServer, B);
    thread2.launch();

    ServerInfo serverInfo(ipServer, portServerMusic, socketMusic);

    Thread threadSendMusic(sendMusic, serverInfo);
    threadSendMusic.launch();

    Thread threadGetMusic(getMusic, serverInfo);
    threadGetMusic.launch();

//    sleep(seconds(60));
//    return;

    while (windowSent.window.isOpen())
    {
        windowSent.window.setView(gameView);

        Event event;

        time = clock.restart();
        time6 = clock6.getElapsedTime();

        timeBuffer6 += time.asSeconds();
        timeBuffer7 += time.asSeconds();
        timeBuffer8 += time.asSeconds();
        timeBuffer9 += time.asSeconds();
        timeBuffer10 += time.asSeconds();
        timeBufferBombInit += time.asSeconds();
        timeBufferMinimap += time.asSeconds();
        timebufferMinimapInit += time.asSeconds();

//        std::cout << time.asSeconds()<< std::endl;
//        time6 = clock6.getElapsedTime();
//        std::cout << " 1: "<< time6.asSeconds();

        updateMusic(timeBuffer6, timeBuffer7, player1, gameView, zombies, zombies1, zombies2, zombies3, dogs);

//        time6 = clock6.getElapsedTime();
//        std::cout << " 2: "<<time6.asSeconds();

        //mutex.lock();

        moveAllEnemies2(zombies, zombies1, zombies2, zombies3, dogs, player1, time);
        moveAllEnemies2(zombies, zombies1, zombies2, zombies3, dogs, player2, time);

//        time6 = clock6.getElapsedTime();
//        std::cout <<" 3: "<< time6.asSeconds();

        updateBomb(bombs, time);

        strikeAllWeaponClient(bullets, zombies, zombies1, zombies2,
                        zombies3, dogs, dead, items);

        strikeAllBombClient(bombs, zombies, zombies1, zombies2, zombies3,
                      dogs, dead, items);

        deleteWeapon(bullets, time);

        deleteBomb(bombs);

        player1.rotate(Vector2f(windowSent.window.mapPixelToCoords(sf::Mouse::getPosition(windowSent.window)).x,
                                windowSent.window.mapPixelToCoords(sf::Mouse::getPosition(windowSent.window)).y));

//        time6 = clock6.getElapsedTime();
//        std::cout << " 4: "<< time6.asSeconds();

        movePlayers(player1, player2, zombies, zombies1, zombies2, zombies3, dogs, time, bubbleBar);

//        time6 = clock6.getElapsedTime();
//        std::cout << " 5: " << time6.asSeconds();

        updateFeatures2(items, player1, player2, time, bulletBar, bombBar);

        rotateEnemies2(zombies, zombies1, zombies2, zombies3, dogs, player1);
        rotateEnemies2(zombies, zombies1, zombies2, zombies3, dogs, player2);

        int j = 0;
        for(auto &i : bullets){
            if(!i.move(time))
                bullets.erase(bullets.begin() + j);
            else
                j++;
        }

        j = 0;
        for(auto &i : dead){
            i.update(time);
            if(i.isDisappeared())
                dead.erase(dead.begin() + j);
            else
                j++;
        }

        j = 0;
        for(auto &i : items){
            i.update(time);
            if(i.isDisappeared())
                items.erase(items.begin() + j);
            else
                j++;
        }

        //mutex.unlock();

        setShadow(houses, trapezes, player1.organism.getPosition());
        spriteShadow.setPosition(player1.organism.getPosition());

        updateCursor(windowSent.window, spriteCursor);
        gameViewUpdate(gameView, windowSent.window, player1, time);

        timeBar.update(gameView, time6 - timePause);


        if(Keyboard::isKeyPressed(Keyboard::Tab) && timebufferMinimapInit > 0.2){
            timebufferMinimapInit = 0;
            if(minimap)
                minimap = false;
            else
                minimap = true;
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
//            thread.terminate();
            thread2.terminate();
            threadGetMusic.terminate();
            threadSendMusic.terminate();
            musicAll.stop();
            soundsAll.stop();
            clearAll(zombies, zombies1, zombies2, zombies3, dogs, bullets, bombs, dead, items, houses, trapezes);
            musicAll.music[numberMusicGame].pause();

            return;
        }

        if(Keyboard::isKeyPressed(Keyboard::LShift)){
            MusicPlay = true;
        } else
            MusicPlay = false;

        if(timeBuffer10 > 0.02){
            timeBuffer10 = 0;
            SendPlayer sendPlayer(player1.organism.getPosition(), player1.direction, player1.health, player1.organism.getRotation(), player1.aim);
            packet << SendType(packetType::player) << sendPlayer;
        }


        while (windowSent.window.pollEvent(event))
        {
            if (event.type == Event::Closed){
//                thread.terminate();
                thread2.terminate();
                threadGetMusic.terminate();
                threadSendMusic.terminate();

                musicAll.stop();
                soundsAll.stop();

                windowSent.window.close();
            }

            if (event.type == event.MouseButtonReleased)
                spriteCursor.setTexture(textureCursor0);
            if (event.type == event.MouseButtonPressed)
                spriteCursor.setTexture(textureCursor1);

            if (event.type == Event::MouseWheelScrolled){
                if(timeBufferBombInit > 0.2 && bombBar.value > 0){
                    timeBufferBombInit = 0;
                    Bomb bomb = initBomb(windowSent.window, spriteBomb1, bombDamage);
                    if(background[(int)(bomb.weapon.getPosition().x / sizeTile)][(int)(bomb.weapon.getPosition().y / sizeTile)].crossEnemy &&
                       background[(int)(bomb.weapon.getPosition().x / sizeTile)][(int)(bomb.weapon.getPosition().y / sizeTile)].type != 18){
                        bombBar.value--;
                        bombs.push_back(bomb);

                        SendBomb sendBomb(bomb.weapon.getPosition());
                        packet << SendType(packetType::bomb) << sendBomb;
                    }
                }
            }

            if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left){
                soundsAll.sound[0].play();
                Weapon bullet = initBullet(windowSent.window, spriteBullet2, player1, pistolDamage, 0);
                mutex.lock();
                bullets.push_back(bullet);
                mutex.unlock();
                SendBullet sendBullet(bullet.weapon.getPosition(), bullet.direction, bullet.damage, bullet.weapon.getRotation());
                packet << SendType(packetType::bullet) << sendBullet;
            }

            if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right && bulletBar.value > 0){
                soundsAll.sound[1].play();
                bulletBar.value--;

                Weapon bullet = initBullet(windowSent.window, spriteBullet1, player1, shotgunDamage, shotgunAngle);
                mutex.lock();
                bullets.push_back(bullet);
                mutex.unlock();
                SendBullet sendBullet1(bullet.weapon.getPosition(), bullet.direction, bullet.damage, bullet.weapon.getRotation());
                packet << SendType(packetType::bullet) << sendBullet1;

                bullet = initBullet(windowSent.window, spriteBullet1, player1, shotgunDamage, -shotgunAngle);
                mutex.lock();
                bullets.push_back(bullet);
                mutex.unlock();
                SendBullet sendBullet2(bullet.weapon.getPosition(), bullet.direction, bullet.damage, bullet.weapon.getRotation());
                packet << SendType(packetType::bullet) << sendBullet2;

                bullet = initBullet(windowSent.window, spriteBullet1, player1, shotgunDamage, 2*shotgunAngle);
                mutex.lock();
                bullets.push_back(bullet);
                mutex.unlock();
                SendBullet sendBullet3(bullet.weapon.getPosition(), bullet.direction, bullet.damage, bullet.weapon.getRotation());
                packet << SendType(packetType::bullet) << sendBullet3;

                bullet = initBullet(windowSent.window, spriteBullet1, player1, shotgunDamage, -2*shotgunAngle);
                mutex.lock();
                bullets.push_back(bullet);
                mutex.unlock();
                SendBullet sendBullet4(bullet.weapon.getPosition(), bullet.direction, bullet.damage, bullet.weapon.getRotation());
                packet << SendType(packetType::bullet) << sendBullet4;

                bullet = initBullet(windowSent.window, spriteBullet1, player1, shotgunDamage, 3*shotgunAngle);
                mutex.lock();
                bullets.push_back(bullet);
                mutex.unlock();
                SendBullet sendBullet5(bullet.weapon.getPosition(), bullet.direction, bullet.damage, bullet.weapon.getRotation());
                packet << SendType(packetType::bullet) << sendBullet5;

                bullet = initBullet(windowSent.window, spriteBullet1, player1, shotgunDamage, -3*shotgunAngle);
                mutex.lock();
                bullets.push_back(bullet);
                mutex.unlock();
                SendBullet sendBullet6(bullet.weapon.getPosition(), bullet.direction, bullet.damage, bullet.weapon.getRotation());
                packet << SendType(packetType::bullet) << sendBullet6;

                bullet = initBullet(windowSent.window, spriteBullet1, player1, shotgunDamage, 0);
                mutex.lock();
                bullets.push_back(bullet);
                mutex.unlock();
                SendBullet sendBullet7(bullet.weapon.getPosition(), bullet.direction, bullet.damage, bullet.weapon.getRotation());
                packet << SendType(packetType::bullet) << sendBullet7;
            }
        }

        if(packet.getData() != nullptr){
            packet << SendType(packetType::end);
            socket.send(packet, ipServer, portServer);
            packet.clear();
        }

//        time6 = clock6.getElapsedTime();
//        std::cout << " 6: " << time6.asSeconds();

        drawGameview2(A);

//        time6 = clock6.getElapsedTime();
//        std::cout << " 7: " << time6.asSeconds();


        //minimap Update & Draw
        //drawMinimap(windowSent.window, gameView, minimapView, minimap, player1, location, minimapThread.sprite, thickness);

        windowSent.window.display();

//        time6 = clock6.getElapsedTime();
//        std::cout << " 8: " << time6.asSeconds();
//        std::cout << "End"<< std::endl;


        if(player1.health <= 0){
//            thread.terminate();
            thread2.terminate();
            threadGetMusic.terminate();
            threadSendMusic.terminate();
            clearAll(zombies, zombies1, zombies2, zombies3, dogs, bullets, bombs, dead, items, houses, trapezes);
            musicAll.stop();
            soundsAll.stop();
            endGame(windowSent.window, gameView, time6 - timePause, spriteCursor);

            return;
        }
    }
}

void sendMusic(ServerInfo serverInfo){
    Packet packet;
    SoundBufferRecorder recorder;

    Clock clock;
    Time time = clock.getElapsedTime();


    while(true) {
        //timeBuffer += clock.restart().asSeconds();
        if (MusicPlay && aim == 1) {

            time = clock.restart();
            std::cout << "dt = " << time.asMicroseconds() << "   " << std::endl;

            recorder.start();


            time = clock.getElapsedTime();
            std::cout << time.asMicroseconds() << "   ";

            sleep(seconds(0.2));

            time = clock.getElapsedTime();
            std::cout << time.asMicroseconds() << "   ";

            recorder.stop();

            time = clock.getElapsedTime();
            std::cout << time.asMicroseconds() << "   ";

            const SoundBuffer &buffer = recorder.getBuffer();

            SendMusic sendMusic(buffer.getSamples(), buffer.getSampleCount(), buffer.getChannelCount(),
                                buffer.getSampleRate());
            packet << sendMusic;
            serverInfo.socket.send(packet, serverInfo.ipServer, serverInfo.portServer);
            packet.clear();

            time = clock.getElapsedTime();
            std::cout << time.asMicroseconds() << "   ";
        }
    }

//    Packet packet;
//    CustomRecorder recorder;
//
//    Uint64 sampleCount = 0;
//    bool record = false;
//
//    while(true){
//        //timeBuffer += clock.restart().asSeconds();
//        if(Keyboard::isKeyPressed(Keyboard::LShift) && aim == 1){
//
//            if(!record){
//                recorder.start();
//                record == true;
//            }
//
//            sleep(seconds(0.01));
//
//            SendMusic sendMusic(recorder.MySamples + sampleCount, recorder.MySamplesCount - sampleCount, recorder.getChannelCount(), recorder.getSampleRate());
//            packet << sendMusic;
//            serverInfo.socket.send(packet, serverInfo.ipServer, serverInfo.portServer);
//            packet.clear();
//            sampleCount = recorder.MySamplesCount;
//
//        } else{
//            sampleCount = 0;
//            record = false;
//            recorder.stop();
//        }
//    }
}

void getMusic(ServerInfo serverInfo){

    Packet packet;
    Sound sound;

    while(true){
        serverInfo.socket.receive(packet, serverInfo.ipServer, serverInfo.portServer);

//        std::cout << "Music received by client" << std::endl;
        SendMusic sendMusic;
        packet >> sendMusic;

        SoundBuffer soundBuffer;
        soundBuffer.loadFromSamples(sendMusic.samples, sendMusic.samplesCount, sendMusic.channelCount, sendMusic.sampleRate);
        //sound.stop();
        sound.setBuffer(soundBuffer);
        sound.play();
        double delay = sendMusic.samplesCount * 10000 / sendMusic.sampleRate;
        delay /= 10000;
        sleep(seconds(delay));
    }
}

void getFromServer(Server &A) {
    Packet packet;

    SendType type;
    SendPlayer sendPlayer;
    SendBomb sendBomb;
    SendBullet sendBullet;
    SendEnemy sendEnemy;
    SendFeature sendFeature;

    while (true) {
        A.socket.receive(packet, A.ipServer, A.portServer);

        while (true) {
            packet >> type;

            if (type.type == packetType::end)
                break;

            switch (type.type) {
                case packetType::player: {
                    packet >> sendPlayer;

                    mutex.lock();
                    A.player2.organism.setRotation(sendPlayer.rotation);
                    A.player2.direction = sendPlayer.direction;
                    A.player2.health = sendPlayer.health;
                    A.player2.organism.setPosition(sendPlayer.position);
                    mutex.unlock();

                    break;
                }
                case packetType::bomb: {
                    packet >> sendBomb;

                    Bomb bomb;
                    bomb.weapon = spriteBomb1;
                    bomb.weapon.setScale(0.3, 0.3);
                    bomb.weapon.setOrigin(bomb.weapon.getTexture()->getSize().x * bomb.weapon.getScale().x,
                                          bomb.weapon.getTexture()->getSize().y * bomb.weapon.getScale().y);
                    bomb.weapon.setPosition(sendBomb.position);
                    bomb.timeBuffer = 0;
                    bomb.timeExplode = 0;
                    bomb.damage = bombDamage;
                    bomb.textureNumber = 1;

                    mutex.lock();
                    A.bombs.push_back(bomb);
                    mutex.unlock();
                    break;
                }
                case packetType::bullet: {
                    packet >> sendBullet;

                    Weapon bullet;
                    bullet.direction = sendBullet.direction;
                    bullet.speed = speedBullet;
                    bullet.damage = sendBullet.damage;
                    if (bullet.damage == shotgunDamage)
                        bullet.weapon = spriteBullet1;
                    else
                        bullet.weapon = spriteBullet2;
                    bullet.weapon.setPosition(sendBullet.position);
                    bullet.weapon.setRotation(sendBullet.rotation);

                    mutex.lock();
                    A.bullets.push_back(bullet);
                    mutex.unlock();

                    break;
                }
                case packetType::feature:{
                    packet >> sendFeature;

                    switch (sendFeature.type){
                        case 1:{
                            Feature feature;
                            feature.feature.setTexture(textureHeart);
                            feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
                            feature.feature.setScale(0.17, 0.17);
                            feature.feature.setPosition(sendFeature.position);
                            feature.type = 1;
                            feature.value = 100;
                            feature.timeBuffer = 0;

                            mutex.lock();
                            A.items.push_back(feature);
                            mutex.unlock();
                            break;
                        }
                        case 2:{
                            Feature feature;
                            feature.feature.setTexture(textureShield);
                            feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
                            feature.feature.setScale(0.04, 0.04);
                            feature.feature.setPosition(sendFeature.position);
                            feature.type = 2;
                            feature.value = 100;
                            feature.timeBuffer = 0;

                            mutex.lock();
                            A.items.push_back(feature);
                            mutex.unlock();
                            break;
                        }
                        case 3:{
                            Feature feature;
                            feature.feature.setTexture(textureBullet);
                            feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
                            feature.feature.setScale(0.1, 0.1);
                            feature.feature.setPosition(sendFeature.position);
                            feature.type = 3;
                            feature.value = numberBulletsCage;
                            feature.timeBuffer = 0;

                            mutex.lock();
                            A.items.push_back(feature);
                            mutex.unlock();
                            break;
                        }
                        case 4:{
                            Feature feature;
                            feature.feature.setTexture(textureBomb);
                            feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
                            feature.feature.setScale(0.035, 0.035);
                            feature.feature.setPosition(sendFeature.position);
                            feature.type = 4;
                            feature.value = numberBombsCage;
                            feature.timeBuffer = 0;

                            mutex.lock();
                            A.items.push_back(feature);
                            mutex.unlock();
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                case packetType::enemy: {
                    packet >> sendEnemy;

                    switch (sendEnemy.type) {
                        case 1: {
                            Organism zombie(zombieFullHealth, 100, zombieSpeed, speedDrawZombie, zombieDamage, true,
                                            textureZombiePathsWalkFullHealth, textureZombiePathsWalkHalfHealth,
                                            textureZombiePathsWalkSmallHealth, numberZombiePathsWalk, 0.001,
                                            textureZombiePathsAttackFullHealth, textureZombiePathsAttackHalfHealth,
                                            textureZombiePathsAttackSmallHealth, numberZombiePathsAttack, 0.001,
                                            spriteZombie);

                            zombie.organism.setPosition(sendEnemy.position);
                            Vector2u enemySize = zombie.organism.getTexture()->getSize();
                            zombie.organism.setOrigin((float) enemySize.x / 2, (float) enemySize.y / 2);
                            zombie.organism.setScale(0.75, 0.75);
                            zombie.aim = sendEnemy.aim;

                            mutex.lock();
                            A.zombies.push_back(zombie);
                            mutex.unlock();

                            break;
                        }
                        case 2: {
                            Organism zombie(zombie1FullHealth, 100, zombie1Speed, speedDrawZombie1, zombie1Damage, true,
                                            textureZombie1PathsWalkFullHealth, textureZombie1PathsWalkHalfHealth,
                                            textureZombie1PathsWalkSmallHealth, numberZombie1PathsWalk, 0.001,
                                            textureZombie1PathsAttackFullHealth, textureZombie1PathsAttackHalfHealth,
                                            textureZombie1PathsAttackSmallHealth, numberZombie1PathsWalk, 0.001,
                                            spriteZombie1);

                            zombie.organism.setPosition(sendEnemy.position);

                            Vector2u enemySize = zombie.organism.getTexture()->getSize();
                            zombie.organism.setOrigin((float) enemySize.x / 2, (float) enemySize.y / 2);
                            zombie.organism.setScale(1.3, 1.3);
                            zombie.aim = sendEnemy.aim;

                            mutex.lock();
                            A.zombies1.push_back(zombie);
                            mutex.unlock();
                            break;
                        }

                        case 3: {
                            Organism zombie(zombie2FullHealth, 100, zombie2Speed, speedDrawZombie2, zombie2Damage, true,
                                            textureZombie2PathsWalkFullHealth, textureZombie2PathsWalkHalfHealth,
                                            textureZombie2PathsWalkSmallHealth, numberZombie2PathsWalk, 0.001,
                                            textureZombie2PathsAttackFullHealth, textureZombie2PathsAttackHalfHealth,
                                            textureZombie2PathsAttackSmallHealth, numberZombie2PathsWalk, 0.001,
                                            spriteZombie2);

                            zombie.organism.setPosition(sendEnemy.position);

                            Vector2u enemySize = zombie.organism.getTexture()->getSize();
                            zombie.organism.setOrigin((float) enemySize.x / 2, (float) enemySize.y / 2);
                            zombie.organism.setScale(1.4, 1.4);
                            zombie.aim = sendEnemy.aim;

                            mutex.lock();
                            A.zombies2.push_back(zombie);
                            mutex.unlock();
                            break;
                        }

                        case 4: {
                            Organism zombie(zombie3FullHealth, 100, zombie3Speed, speedDrawZombie3, zombie3Damage, true,
                                            textureZombie3PathsWalkFullHealth, textureZombie3PathsWalkHalfHealth,
                                            textureZombie3PathsWalkSmallHealth, numberZombie3PathsWalk, 0.001,
                                            textureZombie3PathsAttackFullHealth, textureZombie3PathsAttackHalfHealth,
                                            textureZombie3PathsAttackSmallHealth, numberZombie3PathsWalk, 0.001,
                                            spriteZombie3);

                            zombie.organism.setPosition(sendEnemy.position);

                            Vector2u enemySize = zombie.organism.getTexture()->getSize();
                            zombie.organism.setOrigin((float) enemySize.x / 2, (float) enemySize.y / 2);
                            zombie.organism.setScale(1.4, 1.4);
                            zombie.aim = sendEnemy.aim;

                            mutex.lock();
                            A.zombies3.push_back(zombie);
                            mutex.unlock();
                            break;
                        }

                        case 5: {
                            Organism zombie(dogFullHealth, 100, dogSpeed, speedDrawDog, dogDamage, true,
                                            textureDogPathsWalkFullHealth, textureDogPathsWalkFullHealth,
                                            textureDogPathsWalkFullHealth, numberZombie2PathsWalk, 0.001,
                                            textureDogPathsAttackFullHealth, textureDogPathsAttackFullHealth,
                                            textureDogPathsAttackFullHealth, numberZombie2PathsWalk, 0.001,
                                            spriteDog);
                            zombie.organism.setPosition(sendEnemy.position);

                            Vector2u enemySize = zombie.organism.getTexture()->getSize();
                            zombie.organism.setOrigin((float) enemySize.x / 2, (float) enemySize.y / 2);
                            zombie.organism.setScale(1.0, 1.0);
                            zombie.aim = sendEnemy.aim;

                            mutex.lock();
                            A.dogs.push_back(zombie);
                            mutex.unlock();
                            break;
                        }
                        default:
                            break;
                    }

                    break;
                }
                default:
                    break;
            }
        }

        packet.clear();
    }
}
