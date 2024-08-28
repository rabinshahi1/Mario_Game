#include<SFML/Audio.hpp>
#include"./Headers/AudioManager.h"
#include<iostream>
using namespace std;
AudioManager::AudioManager()
{
    if(!eatBuffer.loadFromFile("./Resources/Audios/Eating.wav"))
    {
        std::cout<<"Opps problem in loading";
    }
    else{
        eatSound.setBuffer(eatBuffer);
        
    }
    if(!jumpBuffer.loadFromFile("./Resources/Audios/jump.wav"))
    {
        std::cout<<"Opps problem in loading";
    }
    else{
        jumpSound.setBuffer(jumpBuffer);
        
    }
    if(!coinBuffer.loadFromFile("./Resources/Audios/coinCollect.wav"))
    {
        std::cout<<"Opps problem in loading";
    }
    else
    {
        coinSound.setBuffer(coinBuffer); 
    }
    if(!redHpBuffer.loadFromFile("./Resources/Audios/obstacle.wav"))
    {
        std::cout<<"Opps problem in loading";
    }
    else
    {
        redHpSound.setBuffer(redHpBuffer); 
    }
    if(!deathBuffer.loadFromFile("./Resources/Audios/Death.wav"))
    {
        std::cout<<"Opps problem in loading";
    }
    else
    {
        
        deathSound.setBuffer(deathBuffer); 
    }
     if(!introBuffer.loadFromFile("./Resources/Audios/Intro.wav"))
    {
        std::cout<<"Opps problem in loading";
    }
    else
    {
        
        introSound.setBuffer(introBuffer); 
    }
    
}
void AudioManager::playJumpSound()
{
   jumpSound.play();
}
void AudioManager::stopIntroSound()
{
   introSound.stop();
   introSound.setPlayingOffset(sf::Time::Zero);
}
void AudioManager::playCoinSound()
{
   coinSound.play();

}
void AudioManager::playDeathSound()
{
   deathSound.play();

}
void AudioManager::playRedHpSound()
{
   redHpSound.play();

}
void AudioManager::playIntroSound()
{
   introSound.play();

}
void AudioManager :: stopDeathSound()
{
    deathSound.stop();
    deathSound.setPlayingOffset(sf::Time::Zero);
}
void AudioManager :: resetDeathSound()

{
    deathSound.setPlayingOffset(sf::Time::Zero);
}
void AudioManager :: resetIntroSound()

{
    introSound.setPlayingOffset(sf::Time::Zero);
}
void AudioManager :: playEatSound()
{
    eatSound.play();
}