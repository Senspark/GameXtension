//
//  SoundMusicTestScene.h
//  senspark-test
//
//  Created by greewoo on 4/8/14.
//
//

#ifndef __senspark_test__SoundMusicTestScene__
#define __senspark_test__SoundMusicTestScene__

#include "testBasic.h"
#include "cocos2d.h"
#include "SoundMusic.h"
#include "BaseTest.h"

using namespace senspark;

class SoundMusicTestScene: public TestScene {
public:
    virtual void onEnter();
    
    virtual void runThisTest();
};

class SoundMusicDemo: public BaseTest {
    
public:
    virtual void onEnter();
    virtual void onExit();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void restartCallback(Ref* pSender) override;
    void nextCallback(Ref* pSender) override;
    void backCallback(Ref* pSender) override;
    
protected:
    Size winSize;
    SoundMusic* soundMusic;    
};

class SoundMusicBackground: public SoundMusicDemo {
public:
    CREATE_FUNC(SoundMusicBackground);
    virtual void onEnter();
    virtual std::string subtitle();
    
    virtual void soundAMenuCallback(Ref* pSender);
    virtual void soundBMenuCallback(Ref* pSender);
};


#endif /* defined(__senspark_test__SoundMusicTestScene__) */
