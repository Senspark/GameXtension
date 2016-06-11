//
// SoundMusic.h
// GameXtension
//
// Created by Duc Nguyen on 5/9/13.
// Finished version 1.0 by Lam Ho on 08/04/14.
//
//

/*
 This simple sound music class provides
 - init sound resources then preload them
 - Play background music with ability to detect not to play again current music
 */

#ifndef __GameXtension__SoundMusic__
#define __GameXtension__SoundMusic__

#include "cocos2d.h"
#include "SSMacros.h"
#include "SimpleAudioEngine.h"

NS_SS_BEGIN

class SoundMusic: public cocos2d::Ref
{
public:
    SoundMusic();
    
    virtual ~SoundMusic();
    
    // init sound resources then preload them
    virtual bool init(const char** soundResources);
    
    /* Play background music with ability to detect not to play again current music
     - resource is path of music
     - loop is loop or not loop
    */
    void playBackgroundMusic(const char* resource, bool loop=false);

protected:

    const char** _soundResources;
    
    std::string _lastMusic;
};
    
NS_SS_END

#endif /* defined(__GameXtension__SoundMusic__) */
