//
//  GameSequence.cpp
//  senspark-game-foundation
//
//  Created by greewoo on 4/29/14.
//
//

#include "GameSequence.h"
#include "ExtraAction.h"

NS_SS_BEGIN

static bool __debug = false;

//
// Sequence
//

GameSequence* GameSequence::createWithTwoActions(GameAction *actionOne, GameAction *actionTwo)
{
    GameSequence *pSequence = new GameSequence();
    pSequence->initWithTwoActions(actionOne, actionTwo);
    pSequence->autorelease();
    
    return pSequence;
}

GameSequence* GameSequence::create(GameAction *action1, ...)
{
    va_list params;
    va_start(params, action1);
    
    GameSequence *pRet = GameSequence::createWithVariableList(action1, params);
    
    va_end(params);
    
    return pRet;
}

GameSequence* GameSequence::createWithVariableList(GameAction *action1, va_list args)
{
    GameAction *pNow;
    GameAction *pPrev = action1;
    bool bOneAction = true;
    
    while (action1)
    {
        pNow = va_arg(args, GameAction*);
        if (pNow)
        {
            pPrev = createWithTwoActions(pPrev, pNow);
            bOneAction = false;
        }
        else
        {
            // If only one action is added to GameSequence, make up a GameSequence by adding a simplest finite time action.
            if (bOneAction)
            {
                pPrev = createWithTwoActions(pPrev, ExtraAction::create());
            }
            break;
        }
    }
    
    return ((GameSequence*)pPrev);
}

GameSequence* GameSequence::create(cocos2d::__Array* arrayOfActions)
{
    GameSequence* pRet = NULL;
    do
    {
        long count = arrayOfActions->count();
        CC_BREAK_IF(count == 0);
        
        GameAction* prev = (GameAction*) arrayOfActions->getObjectAtIndex(0);
        
        if (count > 1)
        {
            for (unsigned int i = 1; i < count; ++i)
            {
                prev = createWithTwoActions(prev, (GameAction*)arrayOfActions->getObjectAtIndex(i));
            }
        }
        else
        {
            // If only one action is added to GameSequence, make up a GameSequence by adding a simplest game action.
            prev = createWithTwoActions(prev, ExtraAction::create());
        }
        pRet = (GameSequence*)prev;
    }while (0);
    return pRet;
}

bool GameSequence::initWithTwoActions(GameAction *actionOne, GameAction *actionTwo)
{
    CCAssert(actionOne != NULL, "");
    CCAssert(actionTwo != NULL, "");
    
    
    _actions[0] = actionOne;
    actionOne->retain();
    
    _actions[1] = actionTwo;
    actionTwo->retain();
    
    return true;
}

GameSequence* GameSequence::clone() const
{
    auto a = new (std::nothrow) GameSequence();
    
    a->initWithTwoActions((GameAction*)(_actions[0]->clone()),
                              (GameAction*)(_actions[1]->clone()));
    
    a->autorelease();
    return a;
}

GameSequence::~GameSequence(void)
{
    CC_SAFE_RELEASE(_actions[0]);
    CC_SAFE_RELEASE(_actions[1]);
}

void GameSequence::startWithTarget(cocos2d::Node *target)
{
    GameAction::startWithTarget(target);
    _last = -1;
}

void GameSequence::stop(void)
{
    if( _last != - 1)
    {
        _actions[_last]->stop();
    }
    
    GameAction::stop();
}

void GameSequence::update(float t)
{
    if (__debug) {
        cocos2d::log("Action0 is %d", _actions[0]->isDone());
        cocos2d::log("Action1 is %d", _actions[1]->isDone());
    }
    if (t==0) {
        _actions[0]->startWithTarget(_target);
        _actions[0]->update(0);
        _last = 0;
    } else if (_actions[0]->isDone() && _last == 0) {
        _actions[0]->update(1);
        _actions[0]->stop();
        
        _actions[1]->startWithTarget(_target);
        _actions[1]->update(0);
        _last = 1;
    } else if (_actions[1]->isDone() && _last == 1) {
        _actions[1]->update(1);
        _actions[1]->stop();
        _isDone = true;
    } else {
        _actions[_last]->update(0.5);
    }
}

GameAction* GameSequence::reverse(void) const
{
    return GameSequence::createWithTwoActions(_actions[1]->reverse(), _actions[0]->reverse());
}

NS_SS_END
