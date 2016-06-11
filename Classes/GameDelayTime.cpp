//
//  GameDelayTime.cpp
//  GameXtensionCpp
//
//  Created by greewoo on 5/7/14.
//
//

#include "GameDelayTime.h"
#include "Utils.h"

NS_SS_BEGIN


GameDelayTime* GameDelayTime::clone() const {
    auto a = new (std::nothrow) GameDelayTime();
    a->autorelease();
    return a;
}

void GameDelayTime::startWithTarget(cocos2d::Node *target) {
    GameAction::startWithTarget(target);

}

void GameDelayTime::update(float t) {
    if (t==0) {
        gettimeofday(&_startingMoment, NULL);
    }

    timeval now;
    gettimeofday(&now, NULL);
    if (Utils::getTimeDifferenceMS(_startingMoment, now)>_duration*1000) {
        _isDone = true;
    }
}

GameAction* GameDelayTime::reverse(void) const {
    return this->clone();
}

GameDelayTime* GameDelayTime::create(float duration) {
    GameDelayTime* action = new GameDelayTime;
    action->autorelease();
    action->setDuration(duration);
    return  action;
}

NS_SS_END
