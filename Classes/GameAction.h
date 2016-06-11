//
//  GameAction.h
//  senspark-game-foundation
//
//  Created by greewoo on 4/27/14.
//
//

#ifndef __senspark_game_foundation__GameAction__
#define __senspark_game_foundation__GameAction__

#include "cocos2d.h"
#include "SSMacros.h"

NS_SS_BEGIN

class GameAction: public cocos2d::Action {
public:
    GameAction(): _isDone(false) {}
    
    bool init() {return true;}

    virtual void step(float dt) override;
    
    virtual bool isDone() const override;

    virtual void update(float time) override {}
    
    virtual void startWithTarget(cocos2d::Node *target) override;
    
    /** returns a reversed action */
    virtual GameAction* reverse(void) const override;
    
    virtual GameAction* clone(void) const override;
    
protected:

    bool _isDone;
    
    bool _isFirstTick;
};

NS_SS_END

#endif /* defined(__senspark_game_foundation__GameAction__) */
