//
//  ActionTestScene.cpp
//  senspark-test
//
//  Created by greewoo on 5/3/14.
//
//

#include "ActionTestScene.h"
#include "AppMacros.h"
#include "GameDelayTime.h"
#include "ChangingContentSizeAction.h"

USING_NS_SS;

static std::function<Layer*()> createFunctions[] = {
    CL(EventTest),
    CL(GameDelayTimeTest),
    CL(GameSequenceOneActionTest),
    CL(GameSequenceTwoActionsTest),
    CL(GameSequenceThreeActionsTest),
    CL(GameSequenceReverseTest),
    CL(GameSpawnOneActionTest),
    CL(GameSpawnTwoActionsTest),
    CL(GameSpawnThreeActionsTest),
    CL(GameRepeatTest),
    CL(GameRepeatForeverTest),
    CL(ChangingContentSizeByTest),
    CL(ChangingContentSizeToTest),
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

void ActionTestScene::onEnter() {
    TestScene::onEnter();
}


void ActionTestScene::onExit() {
    TestScene::onExit();
}

void ActionTestScene::runThisTest() {
    FileFuncLog("..checked");
    sceneIdx = -1;
    addChild(nextAction());
    
    Director::getInstance()->replaceScene(this);
}

void ActionDemo::onEnter() {
    BaseTest::onEnter();
    
    winSize = Director::getInstance()->getWinSize();
    
    testOneAction = TestOneAction::create();
    
    testTwoAction = TestTwoAction::create();
}

void ActionDemo::onExit() {
    BaseTest::onExit();
}

std::string ActionDemo::title() const {
    return "ActionTest";
}

std::string ActionDemo::subtitle() const {
    return "";
}

void ActionDemo::restartCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new ActionTestScene();
    s->addChild( restartAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ActionDemo::nextCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new ActionTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ActionDemo::backCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new ActionTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void GameSequenceOneActionTest::onEnter() {
    ActionDemo::onEnter();
    
    //testOneAction->setMax(3);
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig,"See console, TestOneAction runs 0..100");
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 125) );
    
    sequence = GameSequence::create(testOneAction, NULL);
    this->runAction(sequence);
}

std::string GameSequenceOneActionTest::subtitle() const {
    return "GameSequenceOneActionTest";
}

void GameSequenceTwoActionsTest::onEnter() {
    ActionDemo::onEnter();
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig, "See console, TestOneAction run 0..100, \n then TestTwoAction runs 0..100");
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 125) );
    
    sequence = GameSequence::create(testOneAction, testTwoAction, NULL);
    this->runAction(sequence);

}

std::string GameSequenceTwoActionsTest::subtitle() const {
    return "GameSequenceTwoActionsTest";
}

void GameSequenceThreeActionsTest::onEnter() {
    ActionDemo::onEnter();
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig, "See console, TestOneAction run 0..100, \n then TestTwoAction runs 0..100, \n then copied TestOneAction runs 0..100");
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 125) );
    
    TestOneAction* copiedTestOneAction = (TestOneAction*) testOneAction->clone();
    sequence = GameSequence::create(testOneAction, testTwoAction, copiedTestOneAction, NULL);
    this->runAction(sequence);
}

std::string GameSequenceThreeActionsTest::subtitle() const {
    return "GameSequenceThreeActionsTest";
}

void GameSequenceReverseTest::onEnter() {
    ActionDemo::onEnter();
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig, "See console");
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 65) );
    
    sequence = GameSequence::create(testOneAction, testTwoAction, NULL);
    this->runAction(sequence->reverse());
}

std::string GameSequenceReverseTest::subtitle() const {
    return "GameSequenceReverseTest";
}

void GameSpawnOneActionTest::onEnter() {
    ActionDemo::onEnter();
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig, "See console, TestOneAction runs 0..100");
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 125) );
    
    parallel = GameSpawn::create(testOneAction, NULL);
    this->runAction(parallel);
}

std::string GameSpawnOneActionTest::subtitle() const {
    return "GameSpawnOneActionTest";
}

void GameSpawnTwoActionsTest::onEnter() {
    ActionDemo::onEnter();
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig, "See console, TestOneAction runs 0..50,\nsimultaneously TestTwoAction run 0..100");
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 125) );
    
    testOneAction->setMax(50);
    
    parallel = GameSpawn::create(testOneAction, testTwoAction, NULL);
    this->runAction(parallel);
}

std::string GameSpawnTwoActionsTest::subtitle() const {
    return "GameSpawnTwoActionsTest";
}

void GameSpawnThreeActionsTest::onEnter() {
    ActionDemo::onEnter();
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig,"See console, TestOneAction runs 0..50,\nsimultaneously TestTwoAction run 0..70,\nsimultaneously copied TestOneAction run 0..100");
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 125) );
    
    testOneAction->setMax(50);
    testTwoAction->setMax(70);
    TestOneAction* copiedTestOneAction = (TestOneAction*) testOneAction->clone();
    
    parallel = GameSpawn::create(testOneAction, testTwoAction, copiedTestOneAction, NULL);
    this->runAction(parallel);
}

std::string GameSpawnThreeActionsTest::subtitle() const {
    return "GameSpawnThreeActionsTest";
}

void GameDelayTimeTest::onEnter() {
    ActionDemo::onEnter();
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig,"See console, DelayTime runs in 2 seconds,\nTestOneAction run 0..100");
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 125) );
    
    sequence = GameSequence::create(GameDelayTime::create(2.0), testOneAction, NULL);
    this->runAction(sequence);
}

std::string GameDelayTimeTest::subtitle() const {
    return "GameDelayTimeTest";
}

void GameRepeatTest::onEnter() {
    ActionDemo::onEnter();
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig,"See console, nTestOneAction run 0..100 twice");
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 125) );
    
    GameRepeat* repeat = GameRepeat::create(testOneAction, 2);
    this->runAction(repeat);
}

std::string GameRepeatTest::subtitle() const {
    return "GameRepeatTest";
}

void GameRepeatForeverTest::onEnter() {
    ActionDemo::onEnter();
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig, "See console, nTestOneAction run 0..100 forever \n stop after 10 seconds");
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 125) );
    
    sequence = GameSequence::create(testOneAction, NULL);
    
    repeatForever = GameRepeat::create(sequence, 0);
    this->runAction(repeatForever);
    
    this->scheduleOnce(schedule_selector(GameRepeatForeverTest::stopRepeatForever), 10.0);
}

std::string GameRepeatForeverTest::subtitle() const {
    return "GameRepeatForeverTest";
}

void GameRepeatForeverTest::stopRepeatForever(float dt) {
    repeatForever->stop();
}

void ChangingContentSizeByTest::onEnter() {
    ActionDemo::onEnter();
    
    scale9Sprite =  cocos2d::extension::Scale9Sprite::create("Images/path.png");
    scale9Sprite->setPosition(VisibleRect::center());
    scale9Sprite->setInsetLeft(0);
    scale9Sprite->setInsetTop(20);
    scale9Sprite->setInsetRight(0);
    scale9Sprite->setInsetBottom(20);

    scale9Sprite->runAction(ChangingContentSizeBy::create(1, Size(0, 100)));
    
    addChild(scale9Sprite);
}

std::string ChangingContentSizeByTest::subtitle() const {
    return "ChangingContentSizeByTest";
}

void ChangingContentSizeToTest::onEnter() {
    ActionDemo::onEnter();
    
    scale9Sprite = cocos2d::extension::Scale9Sprite::create("Images/path.png");
    scale9Sprite->setPosition(VisibleRect::center());
    scale9Sprite->setInsetLeft(0);
    scale9Sprite->setInsetTop(20);
    scale9Sprite->setInsetRight(0);
    scale9Sprite->setInsetBottom(20);
    
    scale9Sprite->runAction(ChangingContentSizeTo::create(1, Size(scale9Sprite->getContentSize().width, 150)));
    
    addChild(scale9Sprite);
}

std::string ChangingContentSizeToTest::subtitle() const {
    return "ChangingContentSizeToTest";
}

void EventTest::onEnter() {
    ActionDemo::onEnter();
    TestOneAction* one = TestOneAction::create();
    one->retain();
    this->runAction(one);

    getEventDispatcher()->dispatchCustomEvent("test-event");
}

std::string EventTest::subtitle() const {
    return "EventTest";
}


//TODO: ChangingContentSize reversing test cases





