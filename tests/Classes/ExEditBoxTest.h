//
//  ExEditBoxTest.h
//  senspark_test
//
//  Created by HuyPhan on 11/27/14.
//
//

#ifndef __DemoUI__ExEditBoxTest__
#define __DemoUI__ExEditBoxTest__

#include "testBasic.h"
#include "BaseTest.h"
#include <senspark-game-foundation.h>

USING_NS_CC;
USING_NS_SS;

// scene class for creating
class ExEditBoxTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

// base class demo
class ExEditBoxDemo : public BaseTest
{
protected:
    ExEditBox* _pExEditBox;
    
    MenuItemImage* restartItem;
    MenuItemImage* nextItem;
    MenuItemImage* backItem;
    
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void backCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void restartCallback(Ref* sender);
};

class ExEditBoxDemo0 : public ExEditBoxDemo
{
public:
    CREATE_FUNC(ExEditBoxDemo0);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

#endif /* defined(__DemoUI__ExEditBoxTest__) */
