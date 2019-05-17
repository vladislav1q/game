#include "SFML/Audio.hpp"

#pragma once

using namespace sf;

class SoundsAll{
public:
    SoundsAll(){
        for(int i = 0; i < 13; i++){
            buffer[i].loadFromFile(pathToDirectory + "sounds/sounds/" + std::to_string(i) + ".wav");
            sound[i].setBuffer(buffer[i]);
        }
    }

    void setVolume(int volume){
        for(int i = 0; i < 13; i++){
            sound[i].setVolume(volume);
        }
    }

    void stop(){
        for(int i = 0; i < 13; i++){
            sound[i].pause();
        }
    }
    SoundBuffer buffer[13];
    Sound sound[13];
};

class MusicAll{
public:
    MusicAll(){
        for(int i = 0; i < 7; i++){
            music[i].openFromFile(pathToDirectory + "sounds/music/" + std::to_string(i) + ".ogg");
            music[i].setLoop(true);
        }
    }

    void setVolume(int volume){
        for(int i = 0; i < 7; i++){
            music[i].setVolume(volume);
        }
    }

    void stop(){
        for(int i = 0; i < 7; i++){
            music[i].pause();
        }
    }

    Music music[7];
};


SoundsAll soundsAll;
MusicAll musicAll;

int numberMusicMenu = 0;
int numberMusicGame = 3;
