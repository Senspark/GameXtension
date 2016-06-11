//
//  ContentSizeTo.h
//  GameXtensionCpp
//
//  Created by greewoo on 5/17/14.
//
//

#ifndef __GameXtensionCpp__ContentSizeTo__
#define __GameXtensionCpp__ContentSizeTo__

#include "cocos2d.h"
#include "SSMacros.h"

NS_SS_BEGIN

/**ChangingContentSize actions are used for CCScale9Sprite
 */
class ChangingContentSizeBy: public cocos2d::ActionInterval {
public:
    /** initializes the action runs in duration time with a delta content size
     */
    bool initWithDuration(float duration, cocos2d::Size deltaContentSize);
    
    virtual ChangingContentSizeBy *clone() const override;
    
    virtual void startWithTarget(cocos2d::Node *pTarget) override;
    
    virtual cocos2d::ActionInterval* reverse(void) const override;
    
    virtual void update(float time) override;
    
public:
    /** creates an action runs in duration time with a delta content size
     */
    static ChangingContentSizeBy* create(float duration, cocos2d::Size deltaContentSize);
    
protected:
    cocos2d::Size _deltaContentSize;
    cocos2d::Size _startContentSize;
    cocos2d::Size _previousContentSize;
    
};

class ChangingContentSizeTo: public ChangingContentSizeBy {
public:
    /** initializes the action runs in duration time with a new content size
     */
    bool initWithDuration(float duration, cocos2d::Size contentSize);
    
    virtual ChangingContentSizeTo *clone() const override;
    virtual void startWithTarget(cocos2d::Node *pTarget) override;

public:
    /** creates an action runs in duration time with a new content size
     */
    static ChangingContentSizeTo* create(float duration, cocos2d::Size contentSize);
    
protected:
    cocos2d::Size _endContentSize;
};

NS_SS_END

#endif /* defined(__GameXtensionCpp__ContentSizeTo__) */
