//
// Persistence.cpp
// GameXtension
//
// Created by Duc Nguyen on 3/21/13.
//
//

#include "Persistence.h"
#include "StringManager.h"

NS_SS_BEGIN

Persistence::Persistence()
{
    _userDefault = cocos2d::UserDefault::getInstance();
    
    _soundEnabled = _userDefault->getBoolForKey("sound", true);
    _musicEnabled = _userDefault->getBoolForKey("music", true);
}

Persistence::~Persistence()
{
}

void Persistence::setLanguageCode(std::string langCode)
{
    _userDefault->setStringForKey("lang-code", langCode);
    _userDefault->flush();
}

std::string Persistence::getLanguageCode()
{
    return _userDefault->getStringForKey("lang-code", StringManager::getLangCode(senspark::LanguageType::ENGLISH));
}

void Persistence::setSoundEnabled(bool soundEnable)
{
    _soundEnabled = soundEnable;
    _userDefault->setBoolForKey("sound", soundEnable);
    _userDefault->flush();
}

bool Persistence::getSoundEnabled()
{
    return _soundEnabled;
}

void Persistence::setMusicEnabled(bool musicEnable)
{
    _musicEnabled = musicEnable;
    _userDefault->setBoolForKey("music", musicEnable);
    _userDefault->flush();
}

bool Persistence::getMusicEnabled()
{
    return _musicEnabled;
}

int Persistence::getHighScore() {
    return _userDefault->getIntegerForKey("high-score", 0);
}

void Persistence::setHighScore(int highScore) {
    _userDefault->setIntegerForKey("high-score", highScore);
    _userDefault->flush();
}

void Persistence::setFirstRunning(bool firstRunning)
{
    _userDefault->setBoolForKey("first-running", firstRunning);
    _userDefault->flush();
}

bool Persistence::getFirstRunning()
{
    return _userDefault->getBoolForKey("first-running", true);
}
    
NS_SS_END
