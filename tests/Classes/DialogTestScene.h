//
//  DialogTest.h
//  senspark-test
//
//  Created by greewoo on 4/4/14.
//
//

#ifndef __senspark_test__DialogTest__
#define __senspark_test__DialogTest__

#include "testBasic.h"
#include "cocos2d.h"
#include "QuestionDialog.h"
#include "BaseTest.h"

using namespace senspark;

class DialogTestScene: public TestScene {
public:
    virtual void onEnter();
    
    virtual void runThisTest();
};

class DialogDemo: public BaseTest {
    
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
};

class DialogPopup: public DialogDemo {
public:
    CREATE_FUNC(DialogPopup);
    virtual void onEnter();
    virtual std::string subtitle() const override;
    
    void okCallFunc();
};


class DialogQuestion: public DialogDemo {
public:
    CREATE_FUNC(DialogQuestion);
    virtual void onEnter();
    virtual std::string subtitle() const override;
    
    void onYesCallFunc();
    
};

class DialogReplace: public DialogDemo {
public:
    CREATE_FUNC(DialogReplace);
    virtual void onEnter();
    virtual std::string subtitle() const override;
    
    void onYesCallFunc();
};

class DialogTransition: public DialogDemo {
public:
    CREATE_FUNC(DialogTransition);
    virtual void onEnter();
    virtual std::string subtitle() const override;
    void onCloseCallFunc();
    void onPositiveCallFunc(Value* data);
};

class DialogNotification: public DialogDemo {
public:
    CREATE_FUNC(DialogNotification);
    virtual void onEnter();
    virtual void onExit();
    virtual std::string subtitle() const override;
    
    void receiveShowDialogEvent(EventCustom* data);
    void receiveHideDialogEvent(EventCustom* data);
};

class DialogSound: public DialogDemo {
public:
    CREATE_FUNC(DialogSound);
    virtual void onEnter();
    virtual std::string subtitle() const override;
    
    void delayedCallFunc();
};




#endif /* defined(__senspark_test__DialogTest__) */
