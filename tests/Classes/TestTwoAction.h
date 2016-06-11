//
//  TestTwoAction.h
//  cocos-experiment
//
//  Created by greewoo on 4/27/14.
//
//

#ifndef __cocos_experiment__TestTwoAction__
#define __cocos_experiment__TestTwoAction__

#include "cocos2d.h"
#include "GameAction.h"

USING_NS_CC;
USING_NS_SS;

class TestTwoAction: public GameAction {
    
public:
    static TestTwoAction* create();
    
    TestTwoAction(): testTwo(0), max(100) {}
    
    virtual void update(float time);
    
    virtual void startWithTarget(Node *target);
    
    TestTwoAction* clone() const override;
    /**
     */
    virtual GameAction* reverse(void) const override;
    
protected:
    CC_SYNTHESIZE(int, testTwo, TestTwo);
    CC_SYNTHESIZE(int, max, Max);
    
};

#endif /* defined(__cocos_experiment__TestTwoAction__) */
