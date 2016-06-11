//
//  ScoreFromTo.h
//  bejeweled
//
//  Created by Duc Nguyen on 10/8/13.
//
//

#ifndef __bejeweled__ScoreFromTo__
#define __bejeweled__ScoreFromTo__

#include "cocos2d.h"
#include "SSMacros.h"

NS_SS_BEGIN

class ScoreFromTo : public cocos2d::ActionInterval {
public:
    /** Initializes the action with a duration, a "from" percentage and a "to" percentage */
    bool initWithDuration(float duration, int fromScore, int toScore);
    
    virtual ScoreFromTo* clone() const override;
    
    virtual cocos2d::ActionInterval* reverse(void) const override;
    
    virtual void startWithTarget(cocos2d::Node *pTarget) override;
    
    virtual void update(float time) override;
    
    CC_SYNTHESIZE_READONLY(int, _toScore, To);
    
    CC_SYNTHESIZE_READONLY(int, _fromScore, From);
    
    // for the format of the text out put
    CC_SYNTHESIZE(std::string, _strScoreFormat, Format);

    /*
         Use for increasing in a specific duration
         - duration is the period of time for running the Increasing Animation
         - fromScore is the current Score
         - toScore is the score to increase to
     */

    static ScoreFromTo* create(float duration, int fromScore, int toScore);

    /*
         Use for Steady Increasing Animation
         - fixedTime is a factor. (the larger the fixedTime, the slower the animation's speed)
         - fromScore is the current score
         - toScore is the score to increase to
     */
    static ScoreFromTo* createWithFixedStepTime(float fixedTime, int fromScore, int toScore);
protected:
};

NS_SS_END

#endif /* defined(__bejeweled__ScoreFromTo__) */
