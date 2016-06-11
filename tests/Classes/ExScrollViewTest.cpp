//
//  ExScrollViewTest.cpp
//  senspark_test
//
//  Created by HuyPhan on 11/27/14.
//
//

#include "ExScrollViewTest.h"
#include "controller.h"
#include "testResource.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

#define IMG_INDICATOR_NORMAL   "Images/img_indicator_normal.png"
#define IMG_INDICATOR_ACTIVE   "Images/img_indicator_active.png"

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneScrollViewIdx = -1;

#define MAX_LAYER_SCROLL_VIEW    4

Layer* nextScrollView();
Layer* backScrollView();
Layer* restartScrollView();

static std::function<Layer*()> createFunctionsScrollView[] = {
    CL(ExScrollViewDemo0),
    CL(ExScrollViewDemo1),
    CL(ExScrollViewDemo2),
    CL(ExScrollViewDemo3),
};

Layer* nextScrollView()
{
    sceneScrollViewIdx++;
    sceneScrollViewIdx = sceneScrollViewIdx % MAX_LAYER_SCROLL_VIEW;
    
    auto layer = (createFunctionsScrollView[sceneScrollViewIdx])();
    return layer;
}

Layer* backScrollView()
{
    sceneScrollViewIdx--;
    int total = MAX_LAYER_SCROLL_VIEW;
    if( sceneScrollViewIdx < 0 )
        sceneScrollViewIdx += total;
    
    auto layer = (createFunctionsScrollView[sceneScrollViewIdx])();
    return layer;
}

Layer* restartScrollView()
{
    auto layer = (createFunctionsScrollView[sceneScrollViewIdx])();
    return layer;
    
    return layer;
}


void ExScrollViewTestScene::runThisTest()
{
    auto layer = nextScrollView();
    
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}

void ExScrollViewDemo::onEnter()
{
    // add menu
    backItem    = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(ExScrollViewDemo::backCallback, this) );
    restartItem = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(ExScrollViewDemo::restartCallback, this) );
    nextItem    = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(ExScrollViewDemo::nextCallback, this) );
    
    Menu *pMenu = Menu::create(backItem, restartItem, nextItem, nullptr);
    pMenu->setPosition(Point::ZERO);
    
    backItem->setPosition(VisibleRect::center().x - restartItem->getContentSize().width * 2,
                          VisibleRect::bottom().y + restartItem->getContentSize().height * 0.5f);
    
    restartItem->setPosition(VisibleRect::center().x,
                             VisibleRect::bottom().y + restartItem->getContentSize().height * 0.5f);
    
    nextItem->setPosition(VisibleRect::center().x + restartItem->getContentSize().width * 2,
                          VisibleRect::bottom().y + restartItem->getContentSize().height * 0.5f);
    
    this->addChild(pMenu, 100);
    
    // init this lable for show click page item
    _displayClickLabel = Text::create("", "fonts/Marker Felt.ttf", 12);
    _displayClickLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    _displayClickLabel->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.5f,
                                         Director::getInstance()->getWinSize().height * 0.15f));
    this->addChild(_displayClickLabel);
    
    _pExScrollView->setClickCallback(CC_CALLBACK_1(ExScrollViewDemo::doPageItemClick, this));
    
    BaseTest::onEnter();
}

void ExScrollViewDemo::onExit()
{
    BaseTest::onExit();
}

void ExScrollViewDemo::backCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExScrollViewTestScene();
    auto layer = backScrollView();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void ExScrollViewDemo::nextCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExScrollViewTestScene();
    auto layer = nextScrollView();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void ExScrollViewDemo::restartCallback(Ref* sender)
{
    auto scene = new (std::nothrow) ExScrollViewTestScene();
    auto layer = restartScrollView();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void ExScrollViewDemo::doPageItemClick(Ref* pObj)
{
    Layout* pLayout = dynamic_cast<Layout*>(pObj);
    if(pLayout)
    {
        _displayClickLabel->setString(String::createWithFormat("Just click on page item %s (tag,index = %i)", pLayout->getName().c_str(), pLayout->getTag())->getCString());
    }
}

std::string ExScrollViewDemo::title() const
{
    return "ExScrollViewDemo";
}

std::string ExScrollViewDemo::subtitle() const
{
    return "";
}

void ExScrollViewDemo::addPage(Vector<Node*>* pArr)
{
    _pExScrollView->addPage("Page number " + std::to_string((int)_pExScrollView->getPageCount() + 1), s_pathPageBackground, pArr);
}

void ExScrollViewDemo::removeLastPage()
{
    _pExScrollView->removeLastPage();
}

void ExScrollViewDemo::refreshData()
{
    _pExScrollView->updateLayout();
}

//// ExScrollViewDemo0
//
void ExScrollViewDemo0::onEnter()
{
    _pExScrollView = ExScrollView::create( Size(Director::getInstance()->getWinSize().width * 0.8f,
                                                Director::getInstance()->getWinSize().height * 0.6f));
    
    _pExScrollView->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.5f,
                                     Director::getInstance()->getWinSize().height * 0.5f));
    
    for (int i = 0; i < 10; i++)
    {
        addPage();
    }
    
    // turn of indicator
    _pExScrollView->setEnableIndicator(false);
    
    this->addChild(_pExScrollView);
    _pExScrollView->setPageBackgroundColorType(Layout::BackGroundColorType::GRADIENT);
    _pExScrollView->setPageBackgroundColor(Color4B(rand() % 255, rand() % 255, rand() % 255, rand() % 255));
    _pExScrollView->scrollToCenter();
    
    ExScrollViewDemo::onEnter();
}

std::string ExScrollViewDemo0::subtitle() const
{
    return "Blank page, no indicator, has 10 page item";
}



//// ExScrollViewDemo1
//
void ExScrollViewDemo1::onEnter()
{
    _pExScrollView = ExScrollView::create(Size(Director::getInstance()->getWinSize().width * 0.8f,
                                                Director::getInstance()->getWinSize().height * 0.6f),
                                          IMG_INDICATOR_NORMAL,
                                          IMG_INDICATOR_ACTIVE);
    
    _pExScrollView->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.5f,
                                     Director::getInstance()->getWinSize().height * 0.5f));
    
    Vector<Node*> nodeArr;
    for (int i = 0; i < 10; i++)
    {
        auto pCCLabelTTF = CCLabelTTF::create("this is page item number " + std::to_string((int)_pExScrollView->getPageCount() + 1),
                                              "Marker Felt",
                                              16);
        
        pCCLabelTTF->setAnchorPoint(Vec2(0.5f, 0.5f));
        pCCLabelTTF->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
        pCCLabelTTF->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.8f * 0.5f,
                                      Director::getInstance()->getWinSize().height * 0.6f * 0.5f));
        nodeArr.clear();
        nodeArr.pushBack(pCCLabelTTF);
        addPage(&nodeArr);
    }
    
    // turn on indicator
    _pExScrollView->setEnableIndicator(true);
    _pExScrollView->setIndicatorPading(10.0f);
    _pExScrollView->setIndicatorPosition(Vec2(Director::getInstance()->getWinSize().width * 0.5f,
                                              Director::getInstance()->getWinSize().height * 0.15f));
    
    
    this->addChild(_pExScrollView);
    _pExScrollView->setPageBackgroundColorType(Layout::BackGroundColorType::SOLID);
    _pExScrollView->setPageBackgroundColor(Color4B(rand() % 255, rand() % 255, rand() % 255, rand() % 255));
    _pExScrollView->scrollToCenter();
    
    ExScrollViewDemo::onEnter();
}

std::string ExScrollViewDemo1::subtitle() const
{
    return "Has indicator, has 10 page item";
}

//// ExScrollViewDemo2
//
void ExScrollViewDemo2::onEnter()
{
    _pExScrollView = ExScrollView::create( Size(Director::getInstance()->getWinSize().width * 0.8f,
                                                Director::getInstance()->getWinSize().height * 0.6f),
                                          IMG_INDICATOR_NORMAL,
                                          IMG_INDICATOR_ACTIVE);
    
    _pExScrollView->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.5f,
                                     Director::getInstance()->getWinSize().height * 0.5f));
    
    Vector<Node*> nodeArr;
    for (int i = 0; i < 10; i++)
    {
        auto pCCLabelTTF = CCLabelTTF::create("this is page item number " + std::to_string((int)_pExScrollView->getPageCount() + 1),
                                              "Marker Felt",
                                              16);
        
        pCCLabelTTF->setAnchorPoint(Vec2(0.5f, 0.5f));
        pCCLabelTTF->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
        pCCLabelTTF->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.8f  * 0.5f,
                                      Director::getInstance()->getWinSize().height * 0.6f * 0.5f));
        nodeArr.clear();
        nodeArr.pushBack(pCCLabelTTF);
        addPage(&nodeArr);
    }
    
    // turn ont indicator
    _pExScrollView->setEnableIndicator(true);
    _pExScrollView->setIndicatorPading(10.0f);
    _pExScrollView->setIndicatorPosition(Vec2(Director::getInstance()->getWinSize().width * 0.5f,
                                              Director::getInstance()->getWinSize().height * 0.15f));
    
    
    this->addChild(_pExScrollView);
    _pExScrollView->setPageBackgroundColorType(Layout::BackGroundColorType::SOLID);
    _pExScrollView->setPageBackgroundColor(Color4B(rand() % 255, rand() % 255, rand() % 255, rand() % 255));
    _pExScrollView->scrollToCenter();
    
    //add the menu item for add or remove
    TTFConfig ttfConfig("fonts/arial.ttf", 10);
    auto pLabelAdd = Label::createWithTTF(ttfConfig, "Add page");
    
    auto pMenuItem1 = MenuItemLabel::create(pLabelAdd,
                                            [=](Ref* sender)
                                            {
                                                Vector<Node*> nodeArr;
                                                auto pCCLabelTTF = CCLabelTTF::create("this is page item number " + std::to_string((int)_pExScrollView->getPageCount() + 1),
                                                                                      "Marker Felt",
                                                                                      50.0f);
                                                
                                                pCCLabelTTF->setAnchorPoint(Vec2(0.5f, 0.5f));
                                                pCCLabelTTF->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
                                                pCCLabelTTF->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.8f  * 0.5f,
                                                                              Director::getInstance()->getWinSize().height * 0.6f * 0.5f));
                                                
                                                nodeArr.pushBack(pCCLabelTTF);
                                                this->addPage(&nodeArr);
                                                
                                                auto pMenu = this->getChildByName("MenuPage");
                                                if(pMenu)
                                                {
                                                    MenuItemLabel* pMenuItem = dynamic_cast<MenuItemLabel*>(pMenu->getChildByName("LableCount"));
                                                    if(pMenuItem)
                                                    {
                                                        pMenuItem->setString("Have " + std::to_string((int)_pExScrollView->getPageCount()) + " pages");
                                                    }
                                                }
                                            } );
    
    
    auto pLabelRev = Label::createWithTTF(ttfConfig, "Remove page");
    
    auto pMenuItem2 = MenuItemLabel::create(pLabelRev,
                                            [=](Ref* sender)
                                            {
                                                if(_pExScrollView->getPageCount() > 1)
                                                {
                                                    this->removeLastPage();
                                                    auto pMenu = this->getChildByName("MenuPage");
                                                    if(pMenu)
                                                    {
                                                        MenuItemLabel* pMenuItem = dynamic_cast<MenuItemLabel*>(pMenu->getChildByName("LableCount"));
                                                        if(pMenuItem)
                                                        {
                                                            pMenuItem->setString("Have " + std::to_string((int)_pExScrollView->getPageCount()) + " pages");
                                                        }
                                                    }
                                                }
                                            } );
    
    auto pLabelCount = Label::createWithTTF(ttfConfig, "Have 10 pages");
    
    auto pMenuItem3 = MenuItemLabel::create(pLabelCount);
    pMenuItem3->setName("LableCount");
    
    auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
    
    pMenu->setPosition(Vec2::ZERO);
    pMenu->setName("MenuPage");
    pMenuItem1->setPosition(Vec2(VisibleRect::left().x + 80.0f, VisibleRect::center().y + 2.0f * 50.0f));
    pMenuItem2->setPosition(Vec2(VisibleRect::left().x + 80.0f, VisibleRect::center().y + 50.0f));
    pMenuItem3->setPosition(Vec2(VisibleRect::left().x + 120.0f, VisibleRect::center().y - 50.0f));
    
    this->addChild(pMenu);
    
    ExScrollViewDemo::onEnter();
}

std::string ExScrollViewDemo2::subtitle() const
{
    return "Add or remove page";
}

//// ExScrollViewDemo3
//
void ExScrollViewDemo3::onEnter()
{
    _pExScrollView = ExScrollView::create( Size(Director::getInstance()->getWinSize().width * 0.8f,
                                                Director::getInstance()->getWinSize().height * 0.6f),
                                          IMG_INDICATOR_NORMAL,
                                          IMG_INDICATOR_ACTIVE);
    
    _pExScrollView->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.5f,
                                     Director::getInstance()->getWinSize().height * 0.5f));
    
    Vector<Node*> nodeArr;
    for (int i = 0; i < 10; i++)
    {
        auto pCCLabelTTF = CCLabelTTF::create("this is page item number " + std::to_string((int)_pExScrollView->getPageCount() + 1),
                                              "Marker Felt",
                                              16);
        
        pCCLabelTTF->setAnchorPoint(Vec2(0.5f, 0.5f));
        pCCLabelTTF->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
        pCCLabelTTF->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.8f * 0.5f,
                                      Director::getInstance()->getWinSize().height * 0.6f * 0.5f));
        nodeArr.clear();
        nodeArr.pushBack(pCCLabelTTF);
        addPage(&nodeArr);
    }
    
    // turn ont indicator
    _pExScrollView->setEnableIndicator(true);
    _pExScrollView->setIndicatorPading(10.0f);
    _pExScrollView->setIndicatorPosition(Vec2(Director::getInstance()->getWinSize().width * 0.5f,
                                              Director::getInstance()->getWinSize().height * 0.15f));
    
    
    this->addChild(_pExScrollView);
    _pExScrollView->setPageBackgroundColorType(Layout::BackGroundColorType::SOLID);
    _pExScrollView->setPageBackgroundColor(Color4B(rand() % 255, rand() % 255, rand() % 255, rand() % 255));
    _pExScrollView->scrollToCenter();
    
    // add slider
    Slider* pSlider = Slider::create();
    pSlider->loadBarTexture("Images/sliderTrack.png");
    pSlider->loadSlidBallTextures("Images/sliderThumb.png", "Images/sliderThumb.png", "");
    pSlider->loadProgressBarTexture("Images/sliderProgress.png");
    pSlider->setAnchorPoint(Vec2(0.5f, 0.5f));
    pSlider->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.5f,
                             Director::getInstance()->getWinSize().height * 0.3f));
    pSlider->addEventListener(CC_CALLBACK_2(ExScrollViewDemo3::sliderEvent, this));
    pSlider->setPercent(70);
    this->addChild(pSlider);
    pSlider->setScale(2.0f);
    
    // add text view
    _displayValueLabel = Text::create("PercentEditCenterAlignment: 0.7", "fonts/Marker Felt.ttf", 32);
    _displayValueLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    _displayValueLabel->setPosition(Vec2(Director::getInstance()->getWinSize().width * 0.5f,
                                         Director::getInstance()->getWinSize().height * 0.05f));
    this->addChild(_displayValueLabel);
    
    ExScrollViewDemo::onEnter();
}

std::string ExScrollViewDemo3::subtitle() const
{
    return "Have a lider to control align of page item, calcu by percent";
}

void ExScrollViewDemo3::sliderEvent(Ref *pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* pSlider = dynamic_cast<Slider*>(pSender);
        // percent 50% -> 100%
        float percent = ((float)pSlider->getPercent()) / 200.0f + 0.5f;
        _pExScrollView->setPercentEditCenterAlignment(percent);
        
        // update layout
        this->refreshData();
        
        _displayValueLabel->setString(String::createWithFormat("PercentEditCenterAlignment: %f", percent)->getCString());
    }
}
