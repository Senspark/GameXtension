//
//  SoundMusicTestScene.cpp
//  senspark-test
//
//  Created by greewoo on 4/8/14.
//
//

#include "SoundMusicTestScene.h"
#include "AppMacros.h"
#include "DialogDirector.h"

static std::function<Layer*()> createFunctions[] = {
    CL(SoundMusicBackground),
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    
    return pLayer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
 
    return pLayer;
}

static Layer* restartAction()
{
    Layer* pLayer = (createFunctions[sceneIdx])();

    return pLayer;
}

void SoundMusicTestScene::onEnter() {
    TestScene::onEnter();
}

void SoundMusicTestScene::runThisTest() {
    FileFuncLog("..checked");
    sceneIdx = -1;
    addChild(nextAction());
    
    Director::getInstance()->replaceScene(this);
}

void SoundMusicDemo::onEnter() {
    BaseTest::onEnter();
    
    senspark::DialogDirector::getInstance()->setParentScene(this);
    
    winSize = Director::getInstance()->getWinSize();
    
    soundMusic = new SoundMusic;
}

void SoundMusicDemo::onExit() {
    Layer::onExit();
}

std::string SoundMusicDemo::title() const {
    return "SoundMusic";
}

std::string SoundMusicDemo::subtitle() const {
    return "";
}

void SoundMusicDemo::restartCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new SoundMusicTestScene();
    s->addChild( restartAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SoundMusicDemo::nextCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new SoundMusicTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SoundMusicDemo::backCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new SoundMusicTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SoundMusicBackground::onEnter() {
    SoundMusicDemo::onEnter();
    
    // Create test selection menu
    CCMenu* menu = CCMenu::create();
    
    const char* labels[] = {"SoundA", "SoundB", NULL};
    SEL_MenuHandler menuHandlers[] = {menu_selector(SoundMusicBackground::soundAMenuCallback), menu_selector(SoundMusicBackground::soundBMenuCallback)};
    
    for (int i=0; labels[i]!=NULL; i++) {
        LabelTTF* label = LabelTTF::create(labels[i], "Arial", 24);
        CCMenuItemLabel* menuItem = CCMenuItemLabel::create(label, this, menuHandlers[i]);
        menuItem->setPosition( Vec2( VisibleRect::center().x, (VisibleRect::top().y - 50 - (i+1) * LINE_SPACE) ));
        menu->addChild(menuItem);
    }
    
    menu->setContentSize(Size(VisibleRect::getVisibleRect().size.width, (4 + 1) * (LINE_SPACE)));
    menu->setPosition(CCPointZero);
    addChild(menu);
}

void SoundMusicBackground::soundAMenuCallback(Ref* pSender) {
    FileFuncLog("..checked");
    soundMusic->playBackgroundMusic("bg-a.mp3");
}

void SoundMusicBackground::soundBMenuCallback(Ref* pSender) {
    FileFuncLog("..checked");
    soundMusic->playBackgroundMusic("bg-b.mp3");
}

std::string SoundMusicBackground::subtitle() {
    return "Background";
}

