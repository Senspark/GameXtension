//
//  TestTwoAction.cpp
//  cocos-experiment
//
//  Created by greewoo on 4/27/14.
//
//

#include "TestTwoAction.h"


TestTwoAction* TestTwoAction::create() {
    TestTwoAction* action = new TestTwoAction;
    action->autorelease();
    return action;

}

void TestTwoAction::startWithTarget(Node *target) {
    GameAction::startWithTarget(target);
    testTwo = 0;
}

void TestTwoAction::update(float time) {
    log("TestTwoAction update %.1f index:%d ", time, testTwo);
    testTwo ++;
    if (testTwo==max) {
        _isDone = true;
        log("TestTwoAction update done");
    }
}

TestTwoAction* TestTwoAction::clone() const
{
    auto a = new (std::nothrow) TestTwoAction();
    a->setTestTwo(testTwo);
    a->autorelease();
    return a;
}

GameAction* TestTwoAction::reverse(void) const
{
    return (GameAction*) this->clone();
}
