//
//  UtilsTestScene.cpp
//  utils-cpp-test
//
//  Created by greewoo on 3/31/14.
//
//

#include "UtilsTestScene.h"
#include "testBasic.h"
#include "AppMacros.h"
#include "Utils.h"

using namespace senspark;

static std::function<Layer*()> createFunctions[] = {
    CL(UtilsGetChildrenRecursively),
    CL(UtilsCreateFramesArray),
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    
    return pLayer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    
    return pLayer;
}

static Layer* restartAction()
{
    Layer* pLayer = (createFunctions[sceneIdx])();

    return pLayer;
}

void UtilsTestScene::onEnter() {
    TestScene::onEnter();
}

void UtilsTestScene::runThisTest() {
    FileFuncLog("..checked");
    sceneIdx = -1;
    addChild(nextAction());
    
    Director::getInstance()->replaceScene(this);
}

void UtilsDemo::onEnter() {
    BaseTest::onEnter();
    
    // Or you can create an sprite using a filename. only PNG is supported now. Probably TIFF too
    grossini = CCSprite::create(pathGrossini);
    grossini->retain();
    
    tamara = CCSprite::create(pathSister1);
    tamara->retain();
    
    kathia = CCSprite::create(pathSister2);
    kathia->retain();
    
    addChild(grossini, 1);
    addChild(tamara, 2);
    addChild(kathia, 3);
    
    grossini->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/3));
    tamara->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*2/3));
    kathia->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/2));
    
    drawNode = CCDrawNode::create();
    addChild(drawNode);
}

void UtilsDemo::onExit() {
    Layer::onExit();
}

std::string UtilsDemo::title() const {
    return "UtilsTest";
}

std::string UtilsDemo::subtitle() const {
    return "";
}

void UtilsDemo::restartCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new UtilsTestScene();
    s->addChild( restartAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void UtilsDemo::nextCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new UtilsTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void UtilsDemo::backCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new UtilsTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void UtilsGetChildrenRecursively::onEnter() {
    UtilsDemo::onEnter();
    
    Vector<Node*> array = Utils::getChildrenRecursively(this, NULL);
    
    // Test numbers of children of this layer
    char buf[100];
    sprintf(buf, "Number of children  %ld", array.size());
    
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label = Label::createWithTTF(ttfConfig, buf);
    
    addChild(label, 1);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 65) );
    
    count = -1;
    
    // Show each particular object on scene
    for (int i=0; i<array.size(); i++) {
        this->runAction(Sequence::createWithTwoActions(DelayTime::create(i*1),
                                                         CallFunc::create(CC_CALLBACK_0(UtilsGetChildrenRecursively::drawNodeRectangle,this, array.at(i)))));
    }
    
    // Add count number label
    countNumberLabel =  Label::createWithTTF(ttfConfig, "Showing the child: 0");
    countNumberLabel->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 35) );
    countNumberLabel->setVisible(false);
    addChild(countNumberLabel);
    
    // TODO: need more test
}

std::string UtilsGetChildrenRecursively::subtitle() const {
    return "GetChildrenRecursively";
}

void UtilsGetChildrenRecursively::drawNodeRectangle(Node* node) {
    FileFuncLog("..checked");
    log("%.2f %.2f",node->getPositionX(), node->getPositionY());
    
    count++;
    drawNode->clear();
    
    // draw rectangle border of node
    Vec2 points[] ={  Vec2(node->getPositionX()-node->getContentSize().width/2, node->getPositionY()-node->getContentSize().height/2),
                        Vec2(node->getPositionX()-node->getContentSize().width/2, node->getPositionY()+node->getContentSize().height/2),
                        Vec2(node->getPositionX()+node->getContentSize().width/2, node->getPositionY()+node->getContentSize().height/2),
                        Vec2(node->getPositionX()+node->getContentSize().width/2, node->getPositionY()-node->getContentSize().height/2)
                     };
    drawNode->drawPolygon(points, 4, ccc4f(0, 1, 0, 1), 1, ccc4f(1, 0, 0, 1));
    
    // draw number label that counts incrementally the nodes
    char buf[100];
    sprintf(buf, "Showing the child: %d", count);
    countNumberLabel->setString(buf);
    countNumberLabel->setVisible(true);
}

void UtilsCreateFramesArray::onEnter() {
    UtilsDemo::onEnter();
    
    // Make sprite invisible excepts grossini and tamra
    kathia->setVisible(false);
    
    // Add grossini sprite sheet into the sprite cacher
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animations/grossini.plist");
    
    // Test creating a frames array by running animation on grossini
    Animation* animation = Animation::createWithSpriteFrames(Utils::createFramesArray("grossini_dance_%02d.png", 14, 1), 0.5f);
    animation->retain();
    grossini->runAction(CCAnimate::create(animation));
    
    // Test creating a reverted frames array by running animation on grossini
    Animation* revertedAnimation = Animation::createWithSpriteFrames(Utils::createFramesArray("grossini_dance_%02d.png", 14, 1, true), 0.5f);
    revertedAnimation->retain();
    tamara->runAction(Animate::create(revertedAnimation));
}

std::string UtilsCreateFramesArray::subtitle() const {
    return "CreateFramesArray";
}

