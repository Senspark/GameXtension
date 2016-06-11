//
//  GameDelayTime.h
//  GameXtensionCpp
//
//  Created by greewoo on 5/7/14.
//
//

#ifndef __GameXtensionCpp__GameDelayTime__
#define __GameXtensionCpp__GameDelayTime__

#include "cocos2d.h"
#include "GameAction.h"

NS_SS_BEGIN

class GameDelayTime: public GameAction {
public:
    /**
     */
    virtual GameDelayTime* clone() const override;
    /**
     */
    virtual void startWithTarget(cocos2d::Node *target) override;
    /**
     */
    virtual void update(float t) override;
    /**
     */
    virtual GameAction* reverse(void) const override;

    static GameDelayTime* create(float duration);
    /** get/sets action duration
     */
    CC_SYNTHESIZE(float, _duration, Duration);
protected:
    timeval _startingMoment;
};

NS_SS_END

#endif /* defined(__GameXtensionCpp__GameDelayTime__) */
