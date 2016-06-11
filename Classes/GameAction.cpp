//
//  GameAction.cpp
//  senspark-game-foundation
//
//  Created by greewoo on 4/27/14.
//
//

#include "GameAction.h"

NS_SS_BEGIN

#define DONE_NOTIFICATION "done-notification"

static bool __debug = false;

void GameAction::step(float dt) {
    if (__debug)
        cocos2d::log("GameAction step");
    float time;
    if (_isFirstTick) {
        _isFirstTick = false;
        time = 0;
    } else if (_isDone) {
        time = 1;
    } else {
        time = 0.5;
    }
    if (__debug)
        cocos2d::log("GameAction time=%.1f", time);
    update(time);
}

void GameAction::startWithTarget(cocos2d::Node *target) {
    cocos2d::Action::startWithTarget(target);
    _isDone = false;
    _isFirstTick = true;
}

bool GameAction::isDone() const {
    return _isDone;
}

GameAction* GameAction::reverse(void) const {
    cocos2d::log("senspark::GameAction::reverse: Implement me");
    return NULL;
}

GameAction* GameAction::clone() const {
    cocos2d::log("senspark::GameAction::clone: Implement me");
    return NULL;
}


NS_SS_END
