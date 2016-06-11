//
//  TestOneAction.cpp
//  cocos-experiment
//
//  Created by greewoo on 4/27/14.
//
//

#include "TestOneAction.h"

TestOneAction* TestOneAction::create() {
    TestOneAction* action = new TestOneAction;
    action->autorelease();
    return action;
}

void TestOneAction::startWithTarget(Node *target) {
    GameAction::startWithTarget(target);
    testOne = 0;
    cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener("test-event", CC_CALLBACK_1(TestOneAction::receiveEvent, this));
}

void TestOneAction::update(float time) {
    log("TestOneAction update %.1f index:%d ", time, testOne);
    testOne ++;
    if (testOne==max) {
        _isDone = true;
        log("TestOneAction update done");
    }
}

TestOneAction* TestOneAction::clone() const
{
    auto a = new (std::nothrow) TestOneAction();
    a->setTestOne(testOne);
    a->autorelease();
    return a;
}

GameAction* TestOneAction::reverse(void) const
{
    return (GameAction*) this->clone();
}

void TestOneAction::stop() {
    GameAction::stop();
    _target = NULL;
}

void TestOneAction::receiveEvent(EventCustom*) {
    log("receiveEvent");
}
