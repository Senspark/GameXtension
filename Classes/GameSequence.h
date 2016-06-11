//
//  GameSequence.h
//  senspark-game-foundation
//
//  Created by greewoo on 4/29/14.
//
//

#ifndef __senspark_game_foundation__GameSequence__
#define __senspark_game_foundation__GameSequence__

#include "cocos2d.h"
#include "GameAction.h"

NS_SS_BEGIN

class GameSequence: public GameAction {
public:
    ~GameSequence(void);
    /** initializes the action
     */
    bool initWithTwoActions(GameAction *actionOne, GameAction *actionTwo);
    /**
     */
    virtual GameSequence* clone() const override;
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
    /** helper constructor to create an array of sequenceable actions
     */
    static GameSequence* create(GameAction *action1, ...);
    /** helper constructor to create an array of sequenceable actions given an array
     */
    static GameSequence* create(cocos2d::__Array* arrayOfActions);
    /** helper constructor to create an array of sequence-able actions
     */
    static GameSequence* createWithVariableList(GameAction *action1, va_list args);
    /** creates the action
     */
    static GameSequence* createWithTwoActions(GameAction *actionOne, GameAction *actionTwo);
    
protected:
    GameAction* _actions[2];
    int _last;
    
};

NS_SS_END

#endif /* defined(__senspark_game_foundation__GameSequence__) */
