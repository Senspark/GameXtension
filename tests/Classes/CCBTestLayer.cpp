//
//  CCBTestLayer.cpp
//  utils-cpp-test
//
//  Created by greewoo on 4/3/14.
//
//

#include "CCBTestLayer.h"
#include "VisibleRect.h"
#include "controller.h"

bool CCBTestLayer::init() {
    Layer::init();
    return true;
}

void CCBTestLayer::onEnter() {
    Layer::onEnter();
    LabelTTF* label = LabelTTF::create("MainMenu", "Arial", 20);
    //#endif
    MenuItemLabel* pMenuItem = MenuItemLabel::create(label, this, menu_selector(CCBTestLayer::mainMenuCallback));
    
    Menu* pMenu =Menu::create(pMenuItem, NULL);
    
    pMenu->setPosition( Vec2(0, 0) );
    pMenuItem->setPosition( Vec2( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CCBTestLayer::mainMenuCallback(Ref* pSender)
{
    auto scene = Scene::create();
    auto layer = new (std::nothrow) TestController();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    layer->addConsoleAutoTest();
#endif
    layer->autorelease();
    layer->addConsoleAutoTest();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);

}
