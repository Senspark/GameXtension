//
//  GameSpawn.cpp
//  senspark-game-foundation
//
//  Created by greewoo on 5/3/14.
//
//

#include "GameSpawn.h"
#include "ExtraAction.h"

NS_SS_BEGIN

static bool __debug = false;

//
// Sequence
//

GameSpawn* GameSpawn::createWithTwoActions(GameAction *actionOne, GameAction *actionTwo)
{
    GameSpawn *pSequence = new GameSpawn();
    pSequence->initWithTwoActions(actionOne, actionTwo);
    pSequence->autorelease();
    
    return pSequence;
}

GameSpawn* GameSpawn::create(GameAction *action1, ...)
{
    va_list params;
    va_start(params, action1);
    
    GameSpawn *pRet = GameSpawn::createWithVariableList(action1, params);
    
    va_end(params);
    
    return pRet;
}

GameSpawn* GameSpawn::createWithVariableList(GameAction *action1, va_list args)
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
            // If only one action is added to GameSpawn, make up a GameSpawn by adding a simplest finite time action.
            if (bOneAction)
            {
                pPrev = createWithTwoActions(pPrev, ExtraAction::create());
            }
            break;
        }
    }
    
    return ((GameSpawn*)pPrev);
}

GameSpawn* GameSpawn::create(cocos2d::__Array* arrayOfActions)
{
    GameSpawn* pRet = NULL;
    do
    {
        long count = arrayOfActions->count();
        CC_BREAK_IF(count == 0);
        
        GameAction* prev = (GameAction*)arrayOfActions->getObjectAtIndex(0);
        
        if (count > 1)
        {
            for (unsigned int i = 1; i < count; ++i)
            {
                prev = createWithTwoActions(prev, (GameAction*)arrayOfActions->getObjectAtIndex(i));
            }
        }
        else
        {
            // If only one action is added to GameSpawn, make up a GameSpawn by adding a simplest finite time action.
            prev = createWithTwoActions(prev, ExtraAction::create());
        }
        pRet = (GameSpawn*)prev;
    }while (0);
    return pRet;
}

bool GameSpawn::initWithTwoActions(GameAction *actionOne, GameAction *actionTwo)
{
    CCAssert(actionOne != NULL, "");
    CCAssert(actionTwo != NULL, "");
    
    
    _actions[0] = actionOne;
    actionOne->retain();
    
    _actions[1] = actionTwo;
    actionTwo->retain();
    
    return true;
}

GameSpawn* GameSpawn::clone() const
{
    auto a = new (std::nothrow) GameSpawn();
    a->initWithTwoActions((GameAction*)(_actions[0]->clone()),
                              (GameAction*)(_actions[1]->clone()));
    a->autorelease();
    return a;
}

GameSpawn::~GameSpawn(void)
{
    CC_SAFE_RELEASE(_actions[0]);
    CC_SAFE_RELEASE(_actions[1]);
}

void GameSpawn::startWithTarget(cocos2d::Node *target)
{
    GameAction::startWithTarget(target);
    _action0FirstDone = true;
    _action1FirstDone = true;
}

void GameSpawn::stop(void)
{
    GameAction::stop();
    
    _actions[0]->stop();
    _actions[1]->stop();
}

void GameSpawn::update(float t)
{
    if (__debug)
        cocos2d::log("GameSpawn step %.1f", t);
    if (t==0) {
        _actions[0]->startWithTarget(_target);
        _actions[0]->update(0);
        _actions[1]->startWithTarget(_target);
        _actions[1]->update(0);
    } else {
        if (_actions[0]->isDone()) {
            if (_action0FirstDone) {
                _actions[0]->update(1);
                _actions[0]->stop();
                _action0FirstDone = false;
                if (__debug)
                    cocos2d::log("GameSpawn stop action 0");
            }
        } else {
            _actions[0]->update(0.5);
        }
        
        if (_actions[1]->isDone()) {
            if (_action1FirstDone) {
                _actions[1]->update(1);
                _actions[1]->stop();
                _action1FirstDone = false;
                if (__debug)
                    cocos2d::log("GameSpawn stop action 1");
            }
        } else {
            _actions[1]->update(0.5);
        }
        
        if (_actions[0]->isDone() && _actions[1]->isDone()) {
            _isDone = true;
        }
    }
}

GameAction* GameSpawn::reverse(void) const
{
    return GameSpawn::createWithTwoActions(_actions[1]->reverse(), _actions[0]->reverse());
}

NS_SS_END
