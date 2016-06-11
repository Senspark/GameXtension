//
//  ActionTestScene.h
//  senspark-test
//
//  Created by greewoo on 5/3/14.
//
//

#ifndef __senspark_test__ActionTestScene__
#define __senspark_test__ActionTestScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameAction.h"
#include "TestBasic.h"
#include "TestOneAction.h"
#include "TestTwoAction.h"
#include "GameSequence.h"
#include "GameSpawn.h"
#include "GameRepeat.h"
#include "BaseTest.h"


USING_NS_CC;
USING_NS_SS;
using namespace cocos2d::ui;

class ActionTestScene: public TestScene {
public:
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void runThisTest();
};

class ActionDemo: public BaseTest {
    
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    virtual void restartCallback(Ref* pSender) override;
    virtual void nextCallback(Ref* pSender) override;
    virtual void backCallback(Ref* pSender) override;
    
protected:
    Size winSize;
    
    TestOneAction* testOneAction;
    TestTwoAction* testTwoAction;
    
    GameSequence* sequence;
    GameSpawn* parallel;
};

class GameSequenceOneActionTest: public ActionDemo {
public:
    CREATE_FUNC(GameSequenceOneActionTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class GameSequenceTwoActionsTest: public ActionDemo {
public:
    CREATE_FUNC(GameSequenceTwoActionsTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class GameSequenceThreeActionsTest: public ActionDemo {
public:
    CREATE_FUNC(GameSequenceThreeActionsTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class GameSequenceReverseTest: public ActionDemo {
public:
    CREATE_FUNC(GameSequenceReverseTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class GameSpawnOneActionTest: public ActionDemo {
public:
    CREATE_FUNC(GameSpawnOneActionTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class GameSpawnTwoActionsTest: public ActionDemo {
public:
    CREATE_FUNC(GameSpawnTwoActionsTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class GameSpawnThreeActionsTest: public ActionDemo {
public:
    CREATE_FUNC(GameSpawnThreeActionsTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class GameDelayTimeTest: public ActionDemo {
public:
    CREATE_FUNC(GameDelayTimeTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class GameRepeatTest: public ActionDemo {
public:
    CREATE_FUNC(GameRepeatTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class GameRepeatForeverTest: public ActionDemo {
public:
    CREATE_FUNC(GameRepeatForeverTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void stopRepeatForever(float dt);
    
    GameRepeat* repeatForever;
};

class ChangingContentSizeByTest: public ActionDemo {
public:
    CREATE_FUNC(ChangingContentSizeByTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
protected:
    cocos2d::extension::Scale9Sprite* scale9Sprite;
};

class ChangingContentSizeToTest: public ActionDemo {
public:
    CREATE_FUNC(ChangingContentSizeToTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
protected:
    cocos2d::extension::Scale9Sprite* scale9Sprite;
};

class ContentSizeToTest: public ActionDemo {
public:
    CREATE_FUNC(ContentSizeToTest);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
protected:
    cocos2d::extension::Scale9Sprite* scale9Sprite;
};

class EventTest: public ActionDemo {
public:
    CREATE_FUNC(EventTest);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
protected:
};



#endif /* defined(__senspark_test__ActionTestScene__) */
