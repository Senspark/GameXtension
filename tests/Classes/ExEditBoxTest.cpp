//
//  ExEditBoxTest.cpp
//  senspark_test
//
//  Created by HuyPhan on 11/27/14.
//
//

#include "ExEditBoxTest.h"
#include "testResource.h"
#include "controller.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneExEditBoxIdx = -1;

#define MAX_LAYER_ExEditBox    1

Layer* nextExEditBox();
Layer* backExEditBox();
Layer* restartExEditBox();

static std::function<Layer*()> createFunctionsExEditBox[] = {
    CL(ExEditBoxDemo0),
};

Layer* nextExEditBox()
{
    sceneExEditBoxIdx++;
    sceneExEditBoxIdx = sceneExEditBoxIdx % MAX_LAYER_ExEditBox;
    
    auto layer = (createFunctionsExEditBox[sceneExEditBoxIdx])();
    return layer;
}

Layer* backExEditBox()
{
    sceneExEditBoxIdx--;
    int total = MAX_LAYER_ExEditBox;
    if( sceneExEditBoxIdx < 0 )
        sceneExEditBoxIdx += total;
    
    auto layer = (createFunctionsExEditBox[sceneExEditBoxIdx])();
    return layer;
}

Layer* restartExEditBox()
{
    auto layer = (createFunctionsExEditBox[sceneExEditBoxIdx])();
    return layer;
    
    return layer;
}


void ExEditBoxTestScene::runThisTest()
{
    auto layer = nextExEditBox();
    
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}

void ExEditBoxDemo::onEnter()
{
    // add menu
    backItem    = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(ExEditBoxDemo::backCallback, this) );
    restartItem = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(ExEditBoxDemo::restartCallback, this) );
    nextItem    = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(ExEditBoxDemo::nextCallback, this) );
    
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

void ExEditBoxDemo::onExit()
{
    BaseTest::onExit();
}

void ExEditBoxDemo::backCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExEditBoxTestScene();
    auto layer = backExEditBox();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void ExEditBoxDemo::nextCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExEditBoxTestScene();
    auto layer = nextExEditBox();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void ExEditBoxDemo::restartCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExEditBoxTestScene();
    auto layer = restartExEditBox();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

std::string ExEditBoxDemo::title() const
{
    return "ExEditBoxDemo";
}

std::string ExEditBoxDemo::subtitle() const
{
    return "";
}

//// ExTabViewDemo0
//

void ExEditBoxDemo0::onEnter()
{
    _pExEditBox = ExEditBox::create(Size(Director::getInstance()->getWinSize().width * 0.6f, 60.0f), cocos2d::extension::Scale9Sprite::create(s_pathBtnBlankScreen));
    _pExEditBox->setPosition(Vec2(VisibleRect::center().x, VisibleRect::top().y - _pExEditBox->getContentSize().height));
    _pExEditBox->setAnchorPoint(Vec2(0.5, 1.0f));
    _pExEditBox->setPlaceHolder("Temp");
    _pExEditBox->setFontName("Marker Felt");
    _pExEditBox->setFontSize(25);
    _pExEditBox->setFontColor(Color3B::RED);
    _pExEditBox->setInputMode(EditBox::InputMode::ANY);
    
    this->addChild(_pExEditBox);
    
    ExEditBoxDemo::onEnter();
}

std::string ExEditBoxDemo0::subtitle() const
{
    return "Just use ExEditBoxDemo0";
}