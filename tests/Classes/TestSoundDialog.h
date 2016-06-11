//
//  TestSoundDialog.h
//  senspark-test
//
//  Created by greewoo on 4/6/14.
//
//

#ifndef __senspark_test__TestSoundDialog__
#define __senspark_test__TestSoundDialog__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Dialog.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;


class TestSoundDialog: public senspark::Dialog {
public:
    static senspark::Dialog* dialog();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    CREATE_FUNC(TestSoundDialog);
};

class TestSoundDialogLoader: public LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TestSoundDialogLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TestSoundDialog);
};

#endif /* defined(__senspark_test__TestSoundDialog__) */
