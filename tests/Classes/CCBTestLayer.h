//
//  CCBTestLayer.h
//  utils-cpp-test
//
//  Created by greewoo on 4/3/14.
//
//

#ifndef __utils_cpp_test__CCBTestLayer__
#define __utils_cpp_test__CCBTestLayer__

#include <iostream>
#include <cocos2d.h>
#include <cocos-ext.h>
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class CCBTestLayer: public Layer {
public:
    CREATE_FUNC(CCBTestLayer);

    virtual bool init();
    
    virtual void onEnter();
    
    void mainMenuCallback(Ref* pSender);
};

class CCBTestLayerLoader: public LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCBTestLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCBTestLayer);
};

#endif /* defined(__utils_cpp_test__CCBTestLayer__) */
