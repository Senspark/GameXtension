//
//  ExTabViewTest.h
//  senspark_test
//
//  Created by HuyPhan on 11/27/14.
//
//

#ifndef __senspark_test__ExTabViewTest__
#define __senspark_test__ExTabViewTest__

#include "testBasic.h"
#include "BaseTest.h"
#include <senspark-game-foundation.h>

USING_NS_CC;
USING_NS_SS;

// scene class for creating
class ExTabViewTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

// base class demo
class ExTabViewDemo : public BaseTest
{
protected:
    ExTabView * _pExTabView;
    
    MenuItemImage* restartItem;
    MenuItemImage* nextItem;
    MenuItemImage* backItem;
    Label* pLableInfo;
    
public:
    
    void addTab();
    void removeLastTab();
    void initData();
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void backCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void restartCallback(Ref* sender);
    
    void tabClickCallback(Ref* sender);
};

class ExTabViewDemo0 : public ExTabViewDemo
{
public:
    CREATE_FUNC(ExTabViewDemo0);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    
    void callCloseCallback(Ref* pObj);
};

class ExTabViewDemo1 : public ExTabViewDemo
{
public:
    CREATE_FUNC(ExTabViewDemo1);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ExTabViewDemo2 : public ExTabViewDemo
{
public:
    CREATE_FUNC(ExTabViewDemo2);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ExTabViewDemo3 : public ExTabViewDemo
{
public:
    CREATE_FUNC(ExTabViewDemo3);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

#endif /* defined(__senspark_test__ExTabViewTest__) */
