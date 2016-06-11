//
//  ExTextFieldTest.cpp
//  senspark_test
//
//  Created by HuyPhan on 1/19/15.
//
//

#include "ExTextFieldTest.h"
#include "controller.h"
#include "testResource.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

#define FONT_NAME                       "fonts/Thonburi.ttf"
#define FONT_SIZE                       16

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

enum
{
    kExTextFieldNormal = 0,
    kExTextFieldNormalFixedBgWidth,
    kExTextFieldPassword,
    kExTextFieldPassFixedBgWidth,
    kExTextFieldPasswordLimit,
    kExTextFieldCount,
};

static int sceneTextFieldIdx = -1;

KeyboardNotificationLayer* createTextInputTest(int nIndex)
{
    switch(nIndex)
    {
        case kExTextFieldNormal: return new ExTextFieldDemo0();
        case kExTextFieldPassword: return new ExTextFieldDemo1();
        case kExTextFieldPasswordLimit: return new ExTextFieldDemo2();
        case kExTextFieldNormalFixedBgWidth: return new ExTextFieldDemo3();
        case kExTextFieldPassFixedBgWidth: return new ExTextFieldDemo4();
        default: return 0;
    }
}

Layer* nextTextField();
Layer* backTextField();
Layer* restartTextField();

Layer* nextTextField()
{
    sceneTextFieldIdx++;
    sceneTextFieldIdx = sceneTextFieldIdx % kExTextFieldCount;
    
    return restartTextField();
}

Layer* backTextField()
{
    sceneTextFieldIdx--;
    int total = kExTextFieldCount;
    if( sceneTextFieldIdx < 0 )
        sceneTextFieldIdx += total;
    
    return restartTextField();
}

Layer* restartTextField()
{
    
    ExTextFieldDemo* pContainerLayer = new (std::nothrow) ExTextFieldDemo;
    pContainerLayer->autorelease();
    
    auto pTestLayer = createTextInputTest(sceneTextFieldIdx);
    pTestLayer->autorelease();
    pContainerLayer->addKeyboardNotificationLayer(pTestLayer);
    
    return pContainerLayer;
}

static Rect getRect(Node * node)
{
    Rect rc;
    rc.origin = node->getPosition();
    rc.size = node->getContentSize();
    //rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}


void ExTextFieldTestScene::runThisTest()
{
    auto layer = nextTextField();
    
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}

ExTextFieldDemo::ExTextFieldDemo() : _notificationLayer(nullptr)
{
}

void ExTextFieldDemo::addKeyboardNotificationLayer(KeyboardNotificationLayer * layer)
{
    _notificationLayer = layer;
    addChild(layer);
}

void ExTextFieldDemo::onEnter()
{
    // add menu
    backItem    = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(ExTextFieldDemo::backCallback, this) );
    restartItem = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(ExTextFieldDemo::restartCallback, this) );
    nextItem    = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(ExTextFieldDemo::nextCallback, this) );
    
    
    
    Menu *pMenu = Menu::create(backItem, restartItem, nextItem, nullptr);
    pMenu->setPosition(Point::ZERO);
    
    backItem->setPosition(VisibleRect::center().x - restartItem->getContentSize().width * 2,
                          VisibleRect::bottom().y + restartItem->getContentSize().height * 0.5f);
    
    restartItem->setPosition(VisibleRect::center().x,
                             VisibleRect::bottom().y + restartItem->getContentSize().height * 0.5f);
    
    nextItem->setPosition(VisibleRect::center().x + restartItem->getContentSize().width * 2,
                          VisibleRect::bottom().y + restartItem->getContentSize().height * 0.5f);
    
    this->addChild(pMenu, 100);
    
    BaseTest::onEnter();
}

void ExTextFieldDemo::onExit()
{
    BaseTest::onExit();
}

void ExTextFieldDemo::backCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExTextFieldTestScene();
    auto layer = backTextField();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void ExTextFieldDemo::nextCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExTextFieldTestScene();
    auto layer = nextTextField();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void ExTextFieldDemo::restartCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExTextFieldTestScene();
    auto layer = restartTextField();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

std::string ExTextFieldDemo::title() const
{
    return "ExTextFieldDemo";
}

std::string ExTextFieldDemo::subtitle() const
{
    return "";
}

KeyboardNotificationLayer::KeyboardNotificationLayer()
                            : _trackNode(nullptr)
{
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(KeyboardNotificationLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(KeyboardNotificationLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool KeyboardNotificationLayer::onTouchBegan(Touch  *touch, Event  *event)
{
    CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
    _beginPos = touch->getLocation();
    return true;
}

void KeyboardNotificationLayer::onTouchEnded(Touch  *touch, Event  *event)
{
    if (! _trackNode)
    {
        return;
    }
    
    auto endPos = touch->getLocation();
    
    float delta = 5.0f;
    if (::abs(endPos.x - _beginPos.x) > delta
        || ::abs(endPos.y - _beginPos.y) > delta)
    {
        // not click
        _beginPos.x = _beginPos.y = -1;
        return;
    }
    
    // decide the trackNode is clicked.
    Rect rect;
    auto point = convertTouchToNodeSpaceAR(touch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);
    
    rect = getRect(_trackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
          rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    
    this->onClickTrackNode(rect.containsPoint(point));
    CCLOG("----------------------------------");
}

void KeyboardNotificationLayer::keyboardWillShow(IMEKeyboardNotificationInfo& info)
{
    CCLOG("ExTextFieldDemo:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
          info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);
    
    if (! _trackNode)
    {
        return;
    }
    
    auto rectTracked = getRect(_trackNode);
    CCLOG("ExTextFieldDemo:trackingNodeAt(origin:%f,%f, size:%f,%f)",
          rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);
    
    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! rectTracked.intersectsRect(info.end))
    {
        return;
    }
    
//    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
//    float adjustVert = info.end.getMaxY() - rectTracked.getMinY();
//    CCLOG("ExTextFieldDemo:needAdjustVerticalPosition(%f)", adjustVert);
//    
//    // move all the children node of KeyboardNotificationLayer
//    auto& children = getChildren();
//    Node * node = 0;
//    ssize_t count = children.size();
//    Vec2 pos;
//    for (int i = 0; i < count; ++i)
//    {
//        node = children.at(i);
//        pos = node->getPosition();
//        pos.y += adjustVert;
//        node->setPosition(pos);
//    }
}

//// ExTextFieldDemo0
//
void ExTextFieldDemo0::onEnter()
{
    KeyboardNotificationLayer::onEnter();
    
    // add TextFieldTTF
    auto s = Director::getInstance()->getWinSize();
    
    std::string strSubtitle = subtitle();
    TTFConfig ttfConfig;
    ttfConfig.fontFilePath = FONT_NAME;
    ttfConfig.fontSize = 16;
    auto subTitle = Label::createWithTTF(ttfConfig, strSubtitle.c_str());
    addChild(subTitle, 9999);
    subTitle->setPosition(VisibleRect::center().x, VisibleRect::top().y - 60);
    
    Texture2D *pTexture2D = Director::getInstance()->getTextureCache()->getTextureForKey(s_pathBtnBlankScreen);
    if(pTexture2D == nullptr)
    {
        pTexture2D = Director::getInstance()->getTextureCache()->addImage(s_pathBtnBlankScreen);
    }
    
    auto pExTextField = ExTextField::textFieldWithPlaceHolder("<click here for input normal>",
                                                              FONT_NAME,
                                                              FONT_SIZE,
                                                              SpriteFrame::createWithTexture(pTexture2D, Rect(0.0f, 0.0f, pTexture2D->getContentSize().width, pTexture2D->getContentSize().height)));
    this->addChild(pExTextField);
    pExTextField->setAnchorPoint(Vec2(0.0f, 0.5f));
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // on android, TextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position to make it visable
    pExTextField->setPosition(Vec2(s.width * 0.1f, s.height * 0.7f + 50.0f));
#else
    pExTextField->setPosition(Vec2(s.width * 0.1f, s.height * 0.7f));
#endif
    
    _trackNode = pExTextField;
}

std::string ExTextFieldDemo0::subtitle() const
{
    return "normal";
}

void ExTextFieldDemo0::onClickTrackNode(bool bClicked)
{
    auto pTextField = (ExTextField*)_trackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("ExTextFieldDemo0 attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("ExTextFieldDemo0 detachWithIME");
        pTextField->detachWithIME();
    }
}

//// ExTextFieldDemo1
//
void ExTextFieldDemo1::onEnter()
{
    KeyboardNotificationLayer::onEnter();
    
    // add TextFieldTTF
    auto s = Director::getInstance()->getWinSize();
    
    std::string strSubtitle = subtitle();
    TTFConfig ttfConfig;
    ttfConfig.fontFilePath = FONT_NAME;
    ttfConfig.fontSize = 16;
    auto subTitle = Label::createWithTTF(ttfConfig, strSubtitle.c_str());
    addChild(subTitle, 9999);
    subTitle->setPosition(VisibleRect::center().x, VisibleRect::top().y - 60);
    
    Texture2D *pTexture2D = Director::getInstance()->getTextureCache()->getTextureForKey(s_pathBtnBlankScreen);
    if(pTexture2D == nullptr)
    {
        pTexture2D = Director::getInstance()->getTextureCache()->addImage(s_pathBtnBlankScreen);
    }
    
    auto pExTextField = ExTextField::textFieldWithPlaceHolder("<click here for input pass>",
                                                              FONT_NAME,
                                                              FONT_SIZE,
                                                              SpriteFrame::createWithTexture(pTexture2D, Rect(0.0f, 0.0f, pTexture2D->getContentSize().width, pTexture2D->getContentSize().height)));
    this->addChild(pExTextField);
    pExTextField->setPasswordEnabled(true);
    pExTextField->setAnchorPoint(Vec2(0.0f, 0.5f));
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // on android, TextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position to make it visable
    pExTextField->setPosition(Vec2(s.width * 0.1f, s.height * 0.7f + 50.0f));
#else
    pExTextField->setPosition(Vec2(s.width * 0.1f, s.height * 0.7f));
#endif
    
    _trackNode = pExTextField;
    
}

std::string ExTextFieldDemo1::subtitle() const
{
    return "password";
}

void ExTextFieldDemo1::onClickTrackNode(bool bClicked)
{
    auto pTextField = (ExTextField*)_trackNode;
    if (bClicked)
    {
        // ExTextFieldDemo1 be clicked
        CCLOG("ExTextFieldDemo1 attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // ExTextFieldDemo1 not be clicked
        CCLOG("ExTextFieldDemo1 detachWithIME");
        pTextField->detachWithIME();
    }
}

//// ExTextFieldDemo2
//
void ExTextFieldDemo2::onEnter()
{
    KeyboardNotificationLayer::onEnter();
    
    // add TextFieldTTF
    auto s = Director::getInstance()->getWinSize();
    
    std::string strSubtitle = subtitle();
    TTFConfig ttfConfig;
    ttfConfig.fontFilePath = FONT_NAME;
    ttfConfig.fontSize = 16;
    auto subTitle = Label::createWithTTF(ttfConfig, strSubtitle.c_str());
    addChild(subTitle, 9999);
    subTitle->setPosition(VisibleRect::center().x, VisibleRect::top().y - 60);
    
    Texture2D *pTexture2D = Director::getInstance()->getTextureCache()->getTextureForKey(s_pathBtnBlankScreen);
    if(pTexture2D == nullptr)
    {
        pTexture2D = Director::getInstance()->getTextureCache()->addImage(s_pathBtnBlankScreen);
    }
    
    auto pExTextField = ExTextField::textFieldWithPlaceHolder("<click here for input pass and limit>",
                                                              FONT_NAME,
                                                              FONT_SIZE,
                                                              SpriteFrame::createWithTexture(pTexture2D, Rect(0.0f, 0.0f, pTexture2D->getContentSize().width, pTexture2D->getContentSize().height)));
    this->addChild(pExTextField);
    pExTextField->setPasswordEnabled(true);
    pExTextField->setMaxTextLenght(12);
    pExTextField->setAnchorPoint(Vec2(0.0f, 0.5f));
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // on android, TextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position to make it visable
    pExTextField->setPosition(Vec2(s.width * 0.1f, s.height * 0.7f + 50.0f));
#else
    pExTextField->setPosition(Vec2(s.width * 0.1f, s.height * 0.7f));
#endif
    
    _trackNode = pExTextField;
}

std::string ExTextFieldDemo2::subtitle() const
{
    return "password + litmit input";
}

void ExTextFieldDemo2::onClickTrackNode(bool bClicked)
{
    auto pTextField = (ExTextField*)_trackNode;
    if (bClicked)
    {
        // ExTextFieldDemo1 be clicked
        CCLOG("ExTextFieldDemo1 attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // ExTextFieldDemo1 not be clicked
        CCLOG("ExTextFieldDemo1 detachWithIME");
        pTextField->detachWithIME();
    }
}

//// ExTextFieldDemo3
//
void ExTextFieldDemo3::onEnter()
{
    KeyboardNotificationLayer::onEnter();
    
    // add TextFieldTTF
    auto s = Director::getInstance()->getWinSize();
    
    std::string strSubtitle = subtitle();
    TTFConfig ttfConfig;
    ttfConfig.fontFilePath = FONT_NAME;
    ttfConfig.fontSize = 16;
    auto subTitle = Label::createWithTTF(ttfConfig, strSubtitle.c_str());
    addChild(subTitle, 9999);
    subTitle->setPosition(VisibleRect::center().x, VisibleRect::top().y - 60);
    
    Texture2D *pTexture2D = Director::getInstance()->getTextureCache()->getTextureForKey(s_pathBtnBlankScreen);
    if(pTexture2D == nullptr)
    {
        pTexture2D = Director::getInstance()->getTextureCache()->addImage(s_pathBtnBlankScreen);
    }
    
    auto pExTextField = ExTextField::textFieldWithPlaceHolder("<click here>",
                                                              FONT_NAME,
                                                              FONT_SIZE,
                                                              SpriteFrame::createWithTexture(pTexture2D, Rect(0.0f, 0.0f, pTexture2D->getContentSize().width, pTexture2D->getContentSize().height)));
    this->addChild(pExTextField);
    pExTextField->setAnchorPoint(Vec2(0.0f, 0.5f));
    pExTextField->setFixedBackgroundWidth(300.0f);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // on android, TextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position to make it visable
    pExTextField->setPosition(Vec2(s.width * 0.1f, s.height * 0.7f + 50.0f));
#else
    pExTextField->setPosition(Vec2(s.width * 0.1f, s.height * 0.7f));
#endif
    
    _trackNode = pExTextField;
}

std::string ExTextFieldDemo3::subtitle() const
{
    return "Nomal text have default background width";
}

void ExTextFieldDemo3::onClickTrackNode(bool bClicked)
{
    auto pTextField = (ExTextField*)_trackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("ExTextFieldDemo3 attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("ExTextFieldDemo3 detachWithIME");
        pTextField->detachWithIME();
    }
}


//// ExTextFieldDemo4
//
void ExTextFieldDemo4::onEnter()
{
    KeyboardNotificationLayer::onEnter();
    
    // add TextFieldTTF
    auto s = Director::getInstance()->getWinSize();
    
    std::string strSubtitle = subtitle();
    TTFConfig ttfConfig;
    ttfConfig.fontFilePath = FONT_NAME;
    ttfConfig.fontSize = 16;
    auto subTitle = Label::createWithTTF(ttfConfig, strSubtitle.c_str());
    addChild(subTitle, 9999);
    subTitle->setPosition(VisibleRect::center().x, VisibleRect::top().y - 60);
    
    Texture2D *pTexture2D = Director::getInstance()->getTextureCache()->getTextureForKey(s_pathBtnBlankScreen);
    if(pTexture2D == nullptr)
    {
        pTexture2D = Director::getInstance()->getTextureCache()->addImage(s_pathBtnBlankScreen);
    }
    
    auto pExTextField = ExTextField::textFieldWithPlaceHolder("<click here>",
                                                              FONT_NAME,
                                                              FONT_SIZE,
                                                              SpriteFrame::createWithTexture(pTexture2D, Rect(0.0f, 0.0f, pTexture2D->getContentSize().width, pTexture2D->getContentSize().height)));
    this->addChild(pExTextField);
    pExTextField->setPasswordEnabled(true);
    pExTextField->setAnchorPoint(Vec2(0.0f, 0.5f));
    pExTextField->setFixedBackgroundWidth(300.0f);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // on android, TextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position to make it visable
    pExTextField->setPosition(Vec2(s.width * 0.1f, s.height * 0.7f + 50.0f));
#else
    pExTextField->setPosition(Vec2(s.width * 0.1f, s.height * 0.7f));
#endif
    
    _trackNode = pExTextField;
    
}

std::string ExTextFieldDemo4::subtitle() const
{
    return "password + fixed width";
}

void ExTextFieldDemo4::onClickTrackNode(bool bClicked)
{
    auto pTextField = (ExTextField*)_trackNode;
    if (bClicked)
    {
        // ExTextFieldDemo1 be clicked
        CCLOG("ExTextFieldDemo4 attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // ExTextFieldDemo1 not be clicked
        CCLOG("ExTextFieldDemo4 detachWithIME");
        pTextField->detachWithIME();
    }
}