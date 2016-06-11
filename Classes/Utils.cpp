//
// TimeUtils.cpp
// GameXtension
//
// Created by greewoo-macos on 5/4/13.
//
//

#include "Utils.h"
#include <thread>

NS_SS_BEGIN

float Utils::getTimeDifferenceMS(timeval& start, timeval& end){
    return (end.tv_sec - start.tv_sec)*1000.0f + (end.tv_usec - start.tv_usec) / 1000.0f;
}

cocos2d::Vector<cocos2d::Node*> Utils::getChildrenRecursively(cocos2d::Node* node, cocos2d::Node* exceptNode) {
    cocos2d::Vector<cocos2d::Node*> allChildren;
    for (int i=0; i<node->getChildren().size(); i++) {
        cocos2d::Node* child = (node->getChildren()).at(i);
		if (child != exceptNode) {
            allChildren.pushBack(child);
			allChildren.pushBack(getChildrenRecursively(child, exceptNode));
		}
	}

    return allChildren;
}

cocos2d::Vector<cocos2d::SpriteFrame*> Utils::createFramesArray(const char* pattern, int num, int start, bool isReverted) {
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    if (!isReverted) {
        for( int i = start; i < num+start; i++ )
        {
            animFrames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format(pattern, i)));
        }
    } else {
        for( int i = num+start-1; i >=start; i-- )
        {
            animFrames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format(pattern, i)));
        }

    }
    
    return animFrames;
}

void Utils::runDelayCode(const std::function<void()>& func, int delayTime) {
    std::thread t([func, delayTime]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));
        func();
    });
    t.detach();
}

std::string Utils::getDateString(const time_t &t) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    struct tm now;
    localtime_s(&now, &t);
#else
    struct tm now = *localtime( & t );
#endif
    
    return cocos2d::StringUtils::format("%02d/%02d/%02d", now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);
}

NS_SS_END
