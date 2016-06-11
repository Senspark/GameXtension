//
//  ExScrollViewTest.h
//  senspark_test
//
//  Created by HuyPhan on 11/27/14.
//
//

#ifndef __DemoUI__ExScrollViewTest__
#define __DemoUI__ExScrollViewTest__

#include "testBasic.h"
#include "BaseTest.h"
#include <senspark-game-foundation.h>

USING_NS_CC;
USING_NS_SS;

// scene class for creating
class ExScrollViewTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

// base class demo
class ExScrollViewDemo : public BaseTest
{
protected:
    ExScrollView * _pExScrollView;
    
    MenuItemImage* restartItem;
    MenuItemImage* nextItem;
    MenuItemImage* backItem;
    
    Text* _displayClickLabel;
    
public:
    
    void addPage(Vector<Node*>* pArr = nullptr);
    void removeLastPage();
    void refreshData();
    
    void doPageItemClick(Ref* pObj);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void backCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void restartCallback(Ref* sender);
};

class ExScrollViewDemo0 : public ExScrollViewDemo
{
public:
    CREATE_FUNC(ExScrollViewDemo0);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ExScrollViewDemo1 : public ExScrollViewDemo
{
public:
    CREATE_FUNC(ExScrollViewDemo1);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ExScrollViewDemo2 : public ExScrollViewDemo
{
public:
    CREATE_FUNC(ExScrollViewDemo2);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ExScrollViewDemo3 : public ExScrollViewDemo
{
public:
    void sliderEvent(Ref* pSender, Slider::EventType type);
    
    CREATE_FUNC(ExScrollViewDemo3);
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    
protected:
    Text* _displayValueLabel;
};

#endif /* defined(__DemoUI__ExScrollViewTest__) */
