//
// SoundMusic.cpp
// GameXtension
//
// Created by Duc Nguyen on 5/9/13.
//
//

#include "SoundMusic.h"
#include "SimpleAudioEngine.h"

NS_SS_BEGIN

SoundMusic::SoundMusic()
{
    _lastMusic = "";
}

SoundMusic::~SoundMusic()
{
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
    for (int i = 0; _soundResources[i] != NULL; i++)
        simpleAudioEngine->unloadEffect(_soundResources[i]);
}

bool SoundMusic::init(const char** sResources)
{
    CCLOG("SoundMusicResources starts initializing...");
    _soundResources = sResources;

    for (int i = 0; _soundResources[i] != NULL; i++) {
        CCLOG("Full path for sound resouces: %s", _soundResources[i]);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(_soundResources[i]);
    }
    return true;
}

void SoundMusic::playBackgroundMusic(const char* resource, bool loop) {
    if (_lastMusic != resource || !CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(resource, loop);
        _lastMusic = resource;
    }
}
    
NS_SS_END
