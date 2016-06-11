//
//  TestSoundDialog.cpp
//  senspark-test
//
//  Created by greewoo on 4/6/14.
//
//

#include "TestSoundDialog.h"
#include "CCBUtils.h"

senspark::Dialog* TestSoundDialog::dialog() {
    NodeLoaderLibrary::getInstance()->registerNodeLoader("TestSoundDialog",
                                            TestSoundDialogLoader::loader());
    return (senspark::Dialog*) senspark::CCBUtils::getInstance()->openNode("TestSoundDialog");
}

void TestSoundDialog::onEnter() {
    Dialog::onEnter();
    
    pauseParentScene();
}

void TestSoundDialog::onExit() {
    Dialog::onExit();
    
    resumeParentScene();
}
