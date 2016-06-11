#include "AppDelegate.h"
#include "controller.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("OnlineChineseChess");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    auto designSize = Size(480,320);
    
    auto screenSize = glview->getFrameSize();
    
    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    
    searchPaths.push_back("ccb");
    searchPaths.push_back("sound");
    
    if (screenSize.width >= 2048)
    {
        //glview ->setContentScaleFactor(2048/designSize.width);
        searchPaths.push_back("resources-ipadhd");
    }
    else if (screenSize.width >= 960)
    {
        //glview ->setContentScaleFactor(960/designSize.width);
        searchPaths.push_back("resources-iphonehd");
    }
    else
    {
        //glview ->setContentScaleFactor(480/designSize.width);
        searchPaths.push_back("resources-iphone");
    }
    
    fileUtils->setSearchPaths(searchPaths);
    
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_WIDTH);

    auto scene = Scene::create();
    auto layer = new (std::nothrow) TestController();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    layer->addConsoleAutoTest();
#endif
    layer->autorelease();
    layer->addConsoleAutoTest();
    scene->addChild(layer);
    director->runWithScene(scene);
    
    director->setDisplayStats(false);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::setCurrentTest(BaseTest* curTest)
{
    _curTest = curTest;
}

BaseTest* AppDelegate::getCurrentTest()
{
    return _curTest;
}
