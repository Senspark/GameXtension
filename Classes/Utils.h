//
// TimeUtils.h
// GameXtension
//
// Created by greewoo-macos on 5/4/13.
// Finished version 1.0 by Lam Ho on 08/04/14.
//

#ifndef __GameXtension__TimeUtils__
#define __GameXtension__TimeUtils__

#include "cocos2d.h"
#include "SSMacros.h"

NS_SS_BEGIN

class Utils: public cocos2d::Ref {
public:
    /* Return system time in milisecond */
    //static long long getMilisecondTime();
    
    /* Return different time between start and end moment in milisecond */
	static float getTimeDifferenceMS(timeval& start, timeval& end);
    /*  
        - Get all children recursively (even children of a child)
        - Except the children of the excepNode child
     */
    static cocos2d::Vector<cocos2d::Node*> getChildrenRecursively(cocos2d::Node *node, cocos2d::Node* exceptNode);
    /* 
        - Create frames array from pattern of frame name, pattern must follow the format "abc%d.png" or "abc%0[1-9]*d.png"
        - num is the numbers of frames you have to provide
        - start is starting number
        - if you want create a reverted frames, set the isReverted by true
     */
    static cocos2d::Vector<cocos2d::SpriteFrame*> createFramesArray(const char* pattern, int num, int start = 0, bool isReverted = false);
    
    /*
        - Run a code snippet after delay time
     */
    static void runDelayCode(const std::function<void()>& func, int delayTime);
    
    static std::string getDateString(const time_t& t);

};
    
NS_SS_END

#endif /* defined(__GameXtension__TimeUtils__) */
