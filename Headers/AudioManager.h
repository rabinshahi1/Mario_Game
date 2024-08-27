#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include<SFML/Audio.hpp>

class AudioManager
{
    private:
    sf::SoundBuffer jumpBuffer ,coinBuffer,deathBuffer,redHpBuffer,eatBuffer;
    sf::Sound jumpSound,coinSound,deathSound,redHpSound,eatSound;
    public:
    AudioManager();
    void playJumpSound();
    void playCoinSound();
    void playDeathSound();
    void playRedHpSound();
    void playEatSound();
};

#endif