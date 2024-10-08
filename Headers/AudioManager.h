#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include<SFML/Audio.hpp>

class AudioManager
{
    private:
    sf::SoundBuffer jumpBuffer ,coinBuffer,deathBuffer,redHpBuffer,introBuffer,eatBuffer,hitBuffer;
    sf::Sound jumpSound,coinSound,deathSound,redHpSound,introSound,eatSound,hitSound;
    public:
    AudioManager();
    void playJumpSound();
    void stopIntroSound();
    void playCoinSound();
    void playDeathSound();
    void stopDeathSound();
    void resetDeathSound();
    void resetIntroSound();
    void playRedHpSound();
    void playIntroSound();
    void playEatSound();
    void playHitSound();
};

#endif