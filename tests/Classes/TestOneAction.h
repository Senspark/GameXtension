//
//  TestOneAction.h
//  cocos-experiment
//
//  Created by greewoo on 4/27/14.
//
//

#ifndef __cocos_experiment__TestOneAction__
#define __cocos_experiment__TestOneAction__

#include "cocos2d.h"
#include "GameAction.h"

USING_NS_CC;
USING_NS_SS;

class TestOneAction: public GameAction {
public:
    static TestOneAction* create();
    
    TestOneAction(): testOne(0), max(100) {}
    /**
     */
    virtual TestOneAction* clone() const;
    
    virtual void update(float time);
    
    virtual void startWithTarget(Node *target);
    /**
     */
    virtual GameAction* reverse(void) const override;
    /**
     */
    virtual void stop();

    void receiveEvent(EventCustom*);
    
protected:
    CC_SYNTHESIZE(int, testOne, TestOne);
    CC_SYNTHESIZE(int, max, Max);
};

#endif /* defined(__cocos_experiment__TestOneAction__) */
