//
// Persistence.h
// GameXtension
//
// Created by Duc Nguyen on 3/21/13.
// Finished version 1.0 by Lam Ho on 08/04/14.
//

/* This class provides a persistence with minimal functionality includes saving:
 - LangCode
 - SoundEnabled
 - MusicEnable
 - HighScore
 */

#ifndef __GameXtension__Persistence__
#define __GameXtension__Persistence__

#include "cocos2d.h"
#include "SSMacros.h"

 NS_SS_BEGIN

class Persistence : public cocos2d::Ref
{
public:
    
    Persistence();
    
    virtual ~Persistence();
    
    // Get/Set language code
    CC_PROPERTY(std::string, _langCode, LanguageCode);

    // Get/Set sound enabled
    CC_PROPERTY(bool, _soundEnabled, SoundEnabled);
    
    // Get/Set music enable
    CC_PROPERTY(bool, _musicEnabled, MusicEnabled);
    
    // Get/Set high score
    CC_PROPERTY(int, _highScore, HighScore);
    
    // Get/Set the first running game flag
    CC_PROPERTY(bool, _firstRunning, FirstRunning);
    
    CREATE_FUNC(Persistence);
    
    virtual bool init() { return true; };
    
protected:
    cocos2d::UserDefault* _userDefault;
};
    
NS_SS_END

#endif /* defined(__GameXtension__Persistence__) */
