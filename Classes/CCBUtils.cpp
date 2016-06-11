//
// CCBUtils.cpp
// GameXtension
//
// Created by Duc Nguyen on 11/23/12.
// Seperate into a library by Lam Ho on 27/03/14.
//

#include "CCBUtils.h"

USING_NS_CC_EXT;

NS_SS_BEGIN

static CCBUtils* _instance = NULL;

CCBUtils* CCBUtils::getInstance()
{
    if (_instance == NULL)
    {
        _instance = new CCBUtils();
    }
    
    return _instance;
}

cocos2d::Node* CCBUtils::openNode(const char *pszCCBName)
{
    cocosbuilder::NodeLoaderLibrary* nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::getInstance();
    cocosbuilder::CCBReader* reader = new cocosbuilder::CCBReader(nodeLoaderLibrary);
    cocos2d::Node *node = reader->readNodeGraphFromFile(pszCCBName);
    reader->release();
    return node;
}

cocos2d::Node* CCBUtils::openNode(const char *pszName, cocosbuilder::CCBMemberVariableAssigner *pCCBMemberVariableAssigner, cocosbuilder::CCBSelectorResolver * pCCBSelectorResolver, cocos2d::Ref *pOwner) {
    cocosbuilder::NodeLoaderLibrary* nodeLoader = cocosbuilder::NodeLoaderLibrary::getInstance();
    cocosbuilder::CCBReader* reader = new cocosbuilder::CCBReader(nodeLoader, pCCBMemberVariableAssigner, pCCBSelectorResolver);
    cocos2d::Node* node = reader->readNodeGraphFromFile(pszName, pOwner);
    reader->release();
    return node;
}

cocos2d::Scene* CCBUtils::openScene(const char *pszCCBName)
{
    return openScene(pszCCBName, NULL);
}

cocos2d::Scene* CCBUtils::openScene(const char *pszCCBName, cocos2d::Ref* pOwner)
{
    cocosbuilder::NodeLoaderLibrary* nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::getInstance();
    cocosbuilder::CCBReader* reader = new cocosbuilder::CCBReader(nodeLoaderLibrary);
    cocos2d::Scene* scene = reader->createSceneWithNodeGraphFromFile(pszCCBName, pOwner);
    reader->release();
    return scene;
}
    
NS_SS_END

