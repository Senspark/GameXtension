//
//  CCBUtilsTestScene.cpp
//  utils-cpp-test
//
//  Created by greewoo on 4/2/14.
//
//

#include "CCBUtilsTestScene.h"
#include "testBasic.h"
#include "AppMacros.h"
#include "CCBUtils.h"
#include "CCBTestLayer.h"

using namespace senspark;

static std::function<Layer*()> createFunctions[] = {
    CL(CCBUtilsOpenScene),
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

void CCBUtilsTestScene::onEnter() {
    TestScene::onEnter();
}

void CCBUtilsTestScene::runThisTest() {
    FileFuncLog("..checked");
    sceneIdx = -1;
    //addChild(nextAction());
    
    /* Create an autorelease CCNodeLoaderLibrary. */
    NodeLoaderLibrary* nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    
    nodeLoaderLibrary->registerNodeLoader("CCBTestLayer", CCBTestLayerLoader::loader());

    Director::getInstance()->replaceScene(CCBUtils::getInstance()->openScene("TestScene"));
}

void CCBUtilsDemo::onEnter() {
    BaseTest::onEnter();
}

void CCBUtilsDemo::onExit() {
    BaseTest::onExit();
}

std::string CCBUtilsDemo::title() {
    return "CCBUtils";
}

std::string CCBUtilsDemo::subtitle() {
    return "";
}

void CCBUtilsDemo::restartCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new CCBUtilsTestScene();
    s->addChild( restartAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void CCBUtilsDemo::nextCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new CCBUtilsTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void CCBUtilsDemo::backCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new CCBUtilsTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void CCBUtilsOpenScene::onEnter() {
    CCBUtilsDemo::onEnter();
    
    
}

std::string CCBUtilsOpenScene::subtitle() {
    return "OpenScene";
}
