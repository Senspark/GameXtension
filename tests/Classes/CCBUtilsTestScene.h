//
//  CCBUtilsTestScene.h
//  utils-cpp-test
//
//  Created by greewoo on 4/2/14.
//
//

#ifndef __utils_cpp_test__CCBUtilsTestScene__
#define __utils_cpp_test__CCBUtilsTestScene__

#include <iostream>

#include "testBasic.h"
#include "BaseTest.h"


class CCBUtilsTestScene: public TestScene {
public:
    virtual void onEnter();
    
    virtual void runThisTest();
};

class CCBUtilsDemo: public BaseTest {
    
public:
    virtual void onEnter();
    virtual void onExit();
    
    virtual std::string title();
    virtual std::string subtitle();
    
    void restartCallback(Ref* pSender);
    void nextCallback(Ref* pSender);
    void backCallback(Ref* pSender);
};

class CCBUtilsOpenScene: public CCBUtilsDemo {
public:
    CREATE_FUNC(CCBUtilsOpenScene);
    virtual void onEnter();
    virtual std::string subtitle();
};

#endif /* defined(__utils_cpp_test__CCBUtilsTestScene__) */
