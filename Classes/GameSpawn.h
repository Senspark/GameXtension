//
//  GameSpawn.h
//  senspark-game-foundation
//
//  Created by greewoo on 5/3/14.
//
//

#ifndef __senspark_game_foundation__GameSpawn__
#define __senspark_game_foundation__GameSpawn__

#include "cocos2d.h"
#include "GameAction.h"
#include <vector>

NS_SS_BEGIN

class GameSpawn: public GameAction {
public:
    ~GameSpawn(void);
    /** initializes the action
     */
    bool initWithTwoActions(GameAction *actionOne, GameAction *actionTwo);
    /**
     */
    virtual GameSpawn* clone() const override;
    /**
     */
    virtual void startWithTarget(cocos2d::Node *target) override;
    /**
     */
    virtual void stop(void) override;
    /**
     */
    virtual void update(float t) override;
    /**
     */
    virtual GameAction* reverse(void) const override;
    
public:
    /** helper constructor to create an array of parallel-able actions
     */
    static GameSpawn* create(GameAction *action1, ...);
    /** helper constructor to create an array of parallel-able actions given an array
     */
    static GameSpawn* create(cocos2d::__Array* arrayOfActions);
    /** helper constructor to create an array of parallel-able actions
     */
    static GameSpawn* createWithVariableList(GameAction *action1, va_list args);
    /** creates the action
     */
    static GameSpawn* createWithTwoActions(GameAction *actionOne, GameAction *actionTwo);
    
protected:
    GameAction* _actions[2];
    bool _action0FirstDone;
    bool _action1FirstDone;
};

NS_SS_END

#endif /* defined(__senspark_game_foundation__GameSpawn__) */
