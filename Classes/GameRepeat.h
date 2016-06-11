//
//  GameRepeat.h
//  GameXtensionCpp
//
//  Created by greewoo on 5/7/14.
//
//

#ifndef __GameXtensionCpp__GameRepeat__
#define __GameXtensionCpp__GameRepeat__

#include "cocos2d.h"
#include "GameAction.h"

NS_SS_BEGIN

class GameRepeat: public GameAction {
public:
    GameRepeat(): _innerAction(NULL), _count(0) {}
    
    ~GameRepeat();
    /**
     */
    virtual GameRepeat* clone() const override;
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
    /** helper constructor to create a game action
        @params innerAction is a game action which need to be repeated.
        @params times is a repeating times, 0 will loop forever.
     */
    static GameRepeat* create(GameAction *innerAction, unsigned int times);
    
    CC_SYNTHESIZE(GameAction*, _innerAction, InnerAction);
    
    CC_SYNTHESIZE(unsigned int, _times, Times);
    
    int _count;
    
};

NS_SS_END

#endif /* defined(__GameXtensionCpp__GameRepeat__) */
