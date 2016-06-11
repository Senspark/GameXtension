//
//  GameRepeat.cpp
//  GameXtensionCpp
//
//  Created by greewoo on 5/7/14.
//
//

#include "GameRepeat.h"

NS_SS_BEGIN

static bool __debug = false;

GameRepeat::~GameRepeat() {
    CC_SAFE_RELEASE(_innerAction);
}

GameRepeat* GameRepeat::clone() const {
    auto a = new (std::nothrow) GameRepeat();

    a->setInnerAction(_innerAction);
    a->setTimes(_times);
    a->autorelease();
    
    return a;

}

void GameRepeat::startWithTarget(cocos2d::Node *target) {
    GameAction::startWithTarget(target);
    _count = 0;
}

void GameRepeat::stop(void) {
    GameAction::stop();
    _innerAction->stop();
    _isDone = true;
}

void GameRepeat::update(float t) {
    if (__debug) {
        cocos2d::log("t=%.1f _innerAction isDone %d", t, _innerAction->isDone());
    }
    if (_times==0.0 || _times>_count) {
        if (t==0.0 || _innerAction->isDone()==true) {
            _innerAction->startWithTarget(_target);
            _innerAction->update(0);
            _count++;
        } else {
            _innerAction->update(0.5);
        }
    } else {
        if (_innerAction->isDone()) {
            
            _isDone = true;
        } else {
            _innerAction->update(0.5);
        }
    }
}

GameAction* GameRepeat::reverse(void) const {
    return (GameAction*) this->clone();
}

GameRepeat* GameRepeat::create(GameAction *innerAction, unsigned int times) {
    GameRepeat* action = new GameRepeat;
    innerAction->retain();
    action->setInnerAction(innerAction);
    action->setTimes(times);
    action->autorelease();
    return action;
}

NS_SS_END

