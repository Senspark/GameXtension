//
//  ScoreFromTo.cpp
//  bejeweled
//
//  Created by Duc Nguyen on 10/8/13.
//
//

#include "ScoreFromTo.h"

NS_SS_BEGIN

bool ScoreFromTo::initWithDuration(float duration, int fromScore, int toScore)
{
    if (cocos2d::ActionInterval::initWithDuration(duration))
    {
        _toScore        = toScore;
        _fromScore      = fromScore;
        _strScoreFormat = "";
        return true;
    }
    
    return false;
}

ScoreFromTo* ScoreFromTo::clone() const
{
    auto a = new (std::nothrow) ScoreFromTo();
    a->initWithDuration(_duration, _fromScore, _toScore);
    a->autorelease();
    return a;
}

cocos2d::ActionInterval* ScoreFromTo::reverse(void) const
{
    return ScoreFromTo::create(_duration, _toScore, _fromScore);
}

void ScoreFromTo::startWithTarget(cocos2d::Node *pTarget)
{
    cocos2d::ActionInterval::startWithTarget(pTarget);
}

void ScoreFromTo::update(float time) {
    cocos2d::Label* label = dynamic_cast<cocos2d::Label*>(_target);
    label->setString(cocos2d::__String::createWithFormat(_strScoreFormat.length() > 0 ? _strScoreFormat.c_str() : "%d",
                                                         (int) (_fromScore + (_toScore - _fromScore) * time))->getCString());
}

ScoreFromTo* ScoreFromTo::create(float duration, int fromScore, int toScore)
{
    ScoreFromTo *scoreFromTo = new ScoreFromTo();
    scoreFromTo->initWithDuration(duration, fromScore, toScore);
    scoreFromTo->autorelease();
     
    return scoreFromTo;
}

ScoreFromTo* ScoreFromTo::createWithFixedStepTime(float fixedTime, int fromScore, int toScore)
{
    float duration = (fixedTime * (toScore-fromScore));
    return create(duration, fromScore, toScore);
}

NS_SS_END
