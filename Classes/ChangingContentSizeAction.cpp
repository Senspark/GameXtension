//
//  ContentSizeTo.cpp
//  GameXtensionCpp
//
//  Created by greewoo on 5/17/14.
//
//

#include "ChangingContentSizeAction.h"

NS_SS_BEGIN

bool ChangingContentSizeBy::initWithDuration(float duration, const cocos2d::Size deltaContentSize)
{
    if (cocos2d::ActionInterval::initWithDuration(duration))
    {
        _deltaContentSize = deltaContentSize;
        return true;
    }
    
    return false;
}

void ChangingContentSizeBy::startWithTarget(cocos2d::Node *pTarget)
{
    cocos2d::ActionInterval::startWithTarget(pTarget);
    _previousContentSize = _startContentSize = pTarget->getContentSize();
}

ChangingContentSizeBy* ChangingContentSizeBy::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) ChangingContentSizeBy();
    a->initWithDuration(_duration, _deltaContentSize);
    a->autorelease();
    
    return a;
}

cocos2d::ActionInterval* ChangingContentSizeBy::reverse(void) const
{
    return ChangingContentSizeBy::create(_duration, cocos2d::Size(-_deltaContentSize.width, -_deltaContentSize.height));
}

void ChangingContentSizeBy::update(float t)
{
    if (_target)
    {
        //TODO: Support stackable actions
        _target->setContentSize(cocos2d::Size(_startContentSize.width+_deltaContentSize.width*t, _startContentSize.height+_deltaContentSize.height*t));
    }
}

ChangingContentSizeBy* ChangingContentSizeBy::create(float duration, cocos2d::Size deltaContentSize)
{
    ChangingContentSizeBy *changingContentSizeBy = new ChangingContentSizeBy();
    changingContentSizeBy->initWithDuration(duration, deltaContentSize);
    changingContentSizeBy->autorelease();
    
    return changingContentSizeBy;
}

//ChangingContentSizeTo

bool ChangingContentSizeTo::initWithDuration(float duration, const cocos2d::Size contentSize)
{
    if (cocos2d::ActionInterval::initWithDuration(duration))
    {
        _endContentSize = contentSize;
        return true;
    }
    
    return false;
}

void ChangingContentSizeTo::startWithTarget(cocos2d::Node *pTarget)
{
    ChangingContentSizeBy::startWithTarget(pTarget);
    _deltaContentSize = cocos2d::Size(_endContentSize.width-pTarget->getContentSize().width, _endContentSize.height-pTarget->getContentSize().height);
}

ChangingContentSizeTo* ChangingContentSizeTo::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) ChangingContentSizeTo();
    a->initWithDuration(_duration, _endContentSize);
    a->autorelease();
    return a;
}

ChangingContentSizeTo* ChangingContentSizeTo::create(float duration, cocos2d::Size contentSize)
{
    ChangingContentSizeTo *changingContentSizeTo = new ChangingContentSizeTo();
    changingContentSizeTo->initWithDuration(duration, contentSize);
    changingContentSizeTo->autorelease();
    
    return changingContentSizeTo;
}


NS_SS_END
