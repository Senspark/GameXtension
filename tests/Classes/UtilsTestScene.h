//
//  UtilsTestScene.h
//  utils-cpp-test
//
//  Created by greewoo on 3/31/14.
//
//

#ifndef __utils_cpp_test__UtilsTestScene__
#define __utils_cpp_test__UtilsTestScene__

#include <iostream>
#include "cocos2d.h"
#include "testBasic.h"
#include "BaseTest.h"


class UtilsTestScene: public TestScene {
public:
    virtual void onEnter();
    
    virtual void runThisTest();
};

class UtilsDemo: public BaseTest {
    
public:
    virtual void onEnter();
    virtual void onExit();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void restartCallback(Ref* pSender) override;
    void nextCallback(Ref* pSender) override;
    void backCallback(Ref* pSender) override;

protected:
    Sprite*    grossini;
    Sprite*    tamara;
    Sprite*    kathia;
    DrawNode* drawNode;
};

class UtilsGetChildrenRecursively: public UtilsDemo {
public:
    CREATE_FUNC(UtilsGetChildrenRecursively);
    virtual void onEnter();
    virtual std::string subtitle() const override;
private:
    void drawNodeRectangle(Node* node);
    
private:
    Label* countNumberLabel;
    int count;
};

class UtilsCreateFramesArray: public UtilsDemo {
public:
    CREATE_FUNC(UtilsCreateFramesArray);
    virtual void onEnter();
    virtual std::string subtitle() const override;
};

#endif /* defined(__utils_cpp_test__UtilsTestScene__) */
