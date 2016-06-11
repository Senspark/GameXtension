//
//  ExTextFieldTest.h
//  senspark_test
//
//  Created by HuyPhan on 1/19/15.
//
//

#ifndef __senspark_test__ExTextFieldTest__
#define __senspark_test__ExTextFieldTest__

#include "testBasic.h"
#include "BaseTest.h"
#include <senspark-game-foundation.h>

USING_NS_CC;
USING_NS_SS;

class KeyboardNotificationLayer;

// scene class for creating
class ExTextFieldTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

// base class demo
class ExTextFieldDemo : public BaseTest
{
protected:
    KeyboardNotificationLayer * _notificationLayer;
    
    MenuItemImage* restartItem;
    MenuItemImage* nextItem;
    MenuItemImage* backItem;
    
public:
    
    ExTextFieldDemo();
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void backCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void restartCallback(Ref* sender);
    
    void addKeyboardNotificationLayer(KeyboardNotificationLayer * layer);
};

class KeyboardNotificationLayer : public Layer, public IMEDelegate
{
public:
    KeyboardNotificationLayer();
    
    virtual std::string subtitle() const = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;
    
    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);
    
    // Layer
    bool onTouchBegan(Touch  *touch, Event  *event);
    void onTouchEnded(Touch  *touch, Event  *event);
    
    
protected:
    Node * _trackNode;
    Vec2  _beginPos;
};


class ExTextFieldDemo0 : public KeyboardNotificationLayer
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    
    virtual void onClickTrackNode(bool bClicked);
    
};

class ExTextFieldDemo1 : public KeyboardNotificationLayer
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    
    virtual void onClickTrackNode(bool bClicked);
};


class ExTextFieldDemo2 : public KeyboardNotificationLayer
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    
    virtual void onClickTrackNode(bool bClicked);
};

class ExTextFieldDemo3 : public KeyboardNotificationLayer
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    
    virtual void onClickTrackNode(bool bClicked);
};

class ExTextFieldDemo4 : public KeyboardNotificationLayer
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    
    virtual void onClickTrackNode(bool bClicked);
};

//class ExTextFieldDemo5 : public KeyboardNotificationLayer
//{
//public:
//    virtual void onEnter() override;
//    virtual std::string subtitle() const override;
//    
//    virtual void onClickTrackNode(bool bClicked);
//};

#endif /* defined(__senspark_test__ExTextFieldTest__) */
