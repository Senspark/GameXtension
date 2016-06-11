//
//  StringResourceTest.cpp
//  senspark-test
//
//  Created by greewoo on 4/8/14.
//
//

#include "StringResourceTestScene.h"
#include "StringResource.h"
#include "AppMacros.h"

void StringResourceTestScene::onEnter() {
    TestScene::onEnter();
    
    Size winSize = Director::getInstance()->getWinSize();
    
    const char* langCodes[]={kEnglish, "french", "german", "japanese", NULL};
    const char* dictPaths[]={"en.lproj/strings.plist", "fr.lproj/strings.plist", "de.lproj/strings.plist", "ja.lproj/strings.plist"};
    
    StringResource::getInstance()->init(langCodes, dictPaths, kEnglish);
    
    LabelTTF* helloLabel = LabelTTF::create(StringResource::getInstance()->getString("hello"), "Arial", 24);
    helloLabel->setPosition(Vec2(winSize.width/2, 30));
    addChild(helloLabel);
    
    for (int i=0; langCodes[i]!=NULL; i++) {
        LabelTTF* helloLabel = LabelTTF::create(StringResource::getInstance()->getString("hello", langCodes[i]), "Arial", 24);
        helloLabel->setPosition(Vec2(winSize.width/2, 60+i*30));
        addChild(helloLabel);
    }
}

void StringResourceTestScene::runThisTest() {
    Director::getInstance()->replaceScene(this);
}
