//
//  ExTabViewTest.cpp
//  senspark_test
//
//  Created by HuyPhan on 11/27/14.
//
//

#include "ExTabViewTest.h"
#include "controller.h"
#include "testResource.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

#define IMG_TAB_NORMAL          "Images/tab_normal.png"
#define IMG_TAB_ACTIVE          "Images/tab_active.png"
#define IMG_BTN_CLOSE           "Images/btn_tableview_close.png"
#define IMG_BTN_CLOSE_SELECT    "Images/btn_tableview_close_select.png"

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;

#define MAX_LAYER    3

Layer* next();
Layer* back();
Layer* restart();

static std::function<Layer*()> createFunctions[] = {
    CL(ExTabViewDemo1),
    CL(ExTabViewDemo2),
    CL(ExTabViewDemo3),
};

Layer* next()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* back()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* restart()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
    
    return layer;
}


void ExTabViewTestScene::runThisTest()
{
    auto layer = next();
    
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}

void ExTabViewDemo::onEnter()
{
    // add menu
    backItem    = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(ExTabViewDemo::backCallback, this) );
    restartItem = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(ExTabViewDemo::restartCallback, this) );
    nextItem    = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(ExTabViewDemo::nextCallback, this) );
    
    pLableInfo = Label::create("No tab just click", "Marker Felt", 16.0f);
    
    Menu *pMenu = Menu::create(backItem, restartItem, nextItem, nullptr);
    pMenu->setPosition(Point::ZERO);
    
    backItem->setPosition(VisibleRect::center().x - restartItem->getContentSize().width * 2,
                          VisibleRect::bottom().y + restartItem->getContentSize().height * 0.5f);
    
    restartItem->setPosition(VisibleRect::center().x,
                             VisibleRect::bottom().y + restartItem->getContentSize().height * 0.5f);
    
    nextItem->setPosition(VisibleRect::center().x + restartItem->getContentSize().width * 2,
                          VisibleRect::bottom().y + restartItem->getContentSize().height * 0.5f);
    
    pLableInfo->setPosition(VisibleRect::center().x,
                            VisibleRect::bottom().y + restartItem->getContentSize().height * 1.7f);
    
    this->addChild(pLableInfo);
    
    this->addChild(pMenu, 100);
    
    BaseTest::onEnter();
}

void ExTabViewDemo::onExit()
{
    BaseTest::onExit();
}

void ExTabViewDemo::backCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExTabViewTestScene();
    auto layer = back();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void ExTabViewDemo::nextCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExTabViewTestScene();
    auto layer = next();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void ExTabViewDemo::restartCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExTabViewTestScene();
    auto layer = restart();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

std::string ExTabViewDemo::title() const
{
    return "ExTabViewDemo";
}

std::string ExTabViewDemo::subtitle() const
{
    return "";
}

void ExTabViewDemo::addTab()
{
    auto pLayerTab = LayerColor::create(Color4B(rand() % 255, rand() % 255, rand() % 255, rand() % 255));
    
    auto pCCLabelTTF = CCLabelTTF::create("this is lable in tab " + std::to_string((int)_pExTabView->getTabViewArray().size() + 1), "Marker Felt", 10.0f);
    pCCLabelTTF->setAnchorPoint(Vec2(0.5f, 0.5f));
    pCCLabelTTF->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
    pCCLabelTTF->setPosition(Vec2(Director::getInstance()->getWinSize().width * (0.5f - 0.2f),
                                  Director::getInstance()->getWinSize().height * (0.5f - 0.3f)));
    pLayerTab->addChild(pCCLabelTTF);
    
    int nCount = 2 + rand() % 2;
    for(int k = nCount; k >= 0; k--)
    {
        auto btnLeft = Button::create(s_pathBtnBlankScreen);
        btnLeft->setTitleColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
        btnLeft->setTitleFontName("Marker Felt");
        btnLeft->setTitleFontSize(8.0f);
        btnLeft->setTitleText("Just click but do nothing");
        btnLeft->setAnchorPoint(Vec2(1.05f, 0.5f));
        btnLeft->setPosition(pCCLabelTTF->getPosition() +
                             Vec2(-pCCLabelTTF->getContentSize().width * 0.5f,
                                  btnLeft->getContentSize().height * 1.1f * (k - (nCount / 2))));
        
        pLayerTab->addChild(btnLeft);
        
        auto btnRight = Button::create(s_pathBtnBlankScreen);
        btnRight->setTitleColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
        btnRight->setTitleFontName("Marker Felt");
        btnRight->setTitleFontSize(8.0f);
        btnRight->setTitleText("Just click but do nothing");
        btnRight->setAnchorPoint(Vec2(-0.05f, 0.5f));
        btnRight->setPosition(pCCLabelTTF->getPosition() +
                              Vec2(pCCLabelTTF->getContentSize().width * 0.5f,
                                   btnRight->getContentSize().height * 1.1f * (k - (nCount / 2))));
        
        pLayerTab->addChild(btnRight);
    }
    
    _pExTabView->addTab("Tab " + std::to_string((int)_pExTabView->getTabViewArray().size() + 1), pLayerTab);
}

void ExTabViewDemo::removeLastTab()
{
    _pExTabView->removeLastTab();
}

void ExTabViewDemo::initData()
{
    _pExTabView->initTabData();
}

void ExTabViewDemo::tabClickCallback(Ref* sender)
{
    Node* pNode = dynamic_cast<Node*>(sender);
    pLableInfo->setString(string("Current tab select: ") + pNode->getName());
}

//// ExTabViewDemo0
//

void ExTabViewDemo0::callCloseCallback(Ref* pObj)
{
    auto scene = Scene::create();
    
    auto layer = new (std::nothrow) TestController();
    scene->addChild(layer);
    layer->release();
    
    Director::getInstance()->replaceScene(scene);
    
    cocostudio::ArmatureDataManager::destroyInstance();
}

void ExTabViewDemo0::onEnter()
{
    _pExTabView = ExTabView::create(Rect(   Director::getInstance()->getWinSize().width * 0.2f,
                                             Director::getInstance()->getWinSize().height * 0.2f,
                                             Director::getInstance()->getWinSize().width * 0.6f,
                                             Director::getInstance()->getWinSize().height * 0.6f),
                                        IMG_TAB_NORMAL,
                                        IMG_TAB_ACTIVE,
                                        CC_CALLBACK_1(ExTabViewDemo::tabClickCallback, this),
                                        CC_CALLBACK_1(ExTabViewDemo0::callCloseCallback, this),
                                        IMG_BTN_CLOSE,
                                        IMG_BTN_CLOSE_SELECT
                                        );
    
    _pExTabView->setTitleFontSize(20);
    
    for (int i = 0; i < 2; i++)
    {
        addTab();
    }
    
    this->addChild(_pExTabView);
    
    ExTabViewDemo::onEnter();
}

std::string ExTabViewDemo0::subtitle() const
{
    return "Have close button. 2 tabs";
}

//// ExTabViewDemo1
//
void ExTabViewDemo1::onEnter()
{
    
    _pExTabView = ExTabView::create(Rect(   Director::getInstance()->getWinSize().width * 0.2f,
                                             Director::getInstance()->getWinSize().height * 0.2f,
                                             Director::getInstance()->getWinSize().width * 0.6f,
                                             Director::getInstance()->getWinSize().height * 0.6f),
                                        IMG_TAB_NORMAL,
                                        IMG_TAB_ACTIVE,
                                        CC_CALLBACK_1(ExTabViewDemo::tabClickCallback, this),
                                        [=](Ref* sender)
                                        {
                                            auto scene = Scene::create();
                                            
                                            auto layer = new (std::nothrow) TestController();
                                            scene->addChild(layer);
                                            layer->release();
                                            
                                            Director::getInstance()->replaceScene(scene);
                                            
                                            cocostudio::ArmatureDataManager::destroyInstance();
                                        },
                                        IMG_BTN_CLOSE,
                                        IMG_BTN_CLOSE_SELECT
                                        );
    
    _pExTabView->setTitleFontSize(20);
    _pExTabView->setLeftTabMargin(2.0f);
    
    for (int i = 0; i < 2; i++)
    {
        addTab();
    }
    
    this->addChild(_pExTabView);
    
    ExTabViewDemo::onEnter();
}

std::string ExTabViewDemo1::subtitle() const
{
    return "Have close button. 2 tabs, use lambada func for callback close btn";
}

//// ExTabViewDemo2
//
void ExTabViewDemo2::onEnter()
{
    _pExTabView = ExTabView::create(Rect(   Director::getInstance()->getWinSize().width * 0.2f,
                                             Director::getInstance()->getWinSize().height * 0.2f,
                                             Director::getInstance()->getWinSize().width * 0.6f,
                                             Director::getInstance()->getWinSize().height * 0.6f),
                                        IMG_TAB_NORMAL,
                                        IMG_TAB_ACTIVE,
                                        CC_CALLBACK_1(ExTabViewDemo::tabClickCallback, this)
                                        );
    
    _pExTabView->setTitleFontSize(20);
    _pExTabView->setLeftTabMargin(2.0f);
    
    for (int i = 0; i < 1; i++)
    {
        addTab();
    }
    
    this->addChild(_pExTabView);
    
    //add the menu item for add or remove
    TTFConfig ttfConfig("fonts/arial.ttf", 10.0f);
    auto pLabelAdd = Label::createWithTTF(ttfConfig, "Add tab");
    
    auto pMenuItem1 = MenuItemLabel::create(        pLabelAdd,
                                                    [=](Ref* sender)
                                                    {
                                                        this->addTab();
                                                        this->initData();
                                                    } );
    
    auto pLabelRev = Label::createWithTTF(ttfConfig, "Remove tab");
    
    auto pMenuItem2 = MenuItemLabel::create(pLabelRev,
                                            [=](Ref* sender)
                                            {
                                                if(_pExTabView->getTabNameArray().size() > 1)
                                                {
                                                    this->removeLastTab();
                                                    this->initData();
                                                }
                                            } );
    
    auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
    
    pMenu->setPosition(Vec2::ZERO);
    pMenuItem1->setPosition(Vec2(VisibleRect::left().x + 50.0f, VisibleRect::center().y + 50.0f));
    pMenuItem2->setPosition(Vec2(VisibleRect::left().x + 50.0f, VisibleRect::center().y - 50.0f));
    
    this->addChild(pMenu);
    
    ExTabViewDemo::onEnter();
}

std::string ExTabViewDemo2::subtitle() const
{
    return "Add or remove. 1 tabs";
}

//// ExTabViewDemo3
//
void ExTabViewDemo3::onEnter()
{
    _pExTabView = ExTabView::create(Rect(   Director::getInstance()->getWinSize().width * 0.2f,
                                             Director::getInstance()->getWinSize().height * 0.2f,
                                             Director::getInstance()->getWinSize().width * 0.6f,
                                             Director::getInstance()->getWinSize().height * 0.6f),
                                        IMG_TAB_NORMAL,
                                        IMG_TAB_ACTIVE,
                                        CC_CALLBACK_1(ExTabViewDemo::tabClickCallback, this)
                                        );
    
    _pExTabView->setTitleFontSize(20);
    _pExTabView->setLeftTabMargin(2.0f);
    
    for (int i = 0; i < 3; i++)
    {
        addTab();
    }
    
    this->addChild(_pExTabView);
    
    ExTabViewDemo::onEnter();
}

std::string ExTabViewDemo3::subtitle() const
{
    return "Don't have close btn. 3 tabs";
}

