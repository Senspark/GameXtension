//
// CCBUtils.h
// GameXtension
//
// Created by Duc Nguyen on 11/23/12.
// Finished version 1.0 by Lam Ho on 08/04/14.
//

#ifndef __GameXtension__CCBUtils__
#define __GameXtension__CCBUtils__


#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"
#include "SSMacros.h"

NS_SS_BEGIN

class CCBUtils
{
    
public:
    /* Get the singleton of CCBUtils */
    static CCBUtils* getInstance();
    
    /* Create a CCNode from pszCCBName ccb file*/
    cocos2d::Node* openNode(const char *pszCCBName);

    /*  
        - Create a CCNode from ccb file,
        - Bind the member variable assigner to  pCCBMemberVariableAssigner
        - Bind the selector resolver to pCCBSelectorResolver
        - Bind the owner to pOwner
     */
    cocos2d::Node* openNode(const char *pszName, cocosbuilder::CCBMemberVariableAssigner *pCCBMemberVariableAssigner, cocosbuilder::CCBSelectorResolver * pCCBSelectorResolver, cocos2d::Ref *pOwner);
    
    /* Create a CCScreen from pszCCBName ccb file*/
    cocos2d::Scene* openScene(const char *pszCCBName);
    
    /*
        - Create a CCScreen from pszCCBName ccb file,
        - Bind the owner to pOwner
     */
    cocos2d::Scene* openScene(const char *pszCCBName, cocos2d::Ref* pOwner);
    
};
    
NS_SS_END

#endif /* defined(__GameXtension__CCBUtils__) */
