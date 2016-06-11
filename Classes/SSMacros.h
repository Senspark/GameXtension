//
//  SSMacros.h
//  GameXtensionCpp
//
//  Created by greewoo on 4/8/14.
//
//

#ifndef GameXtensionCpp_SSMacros_h
#define GameXtensionCpp_SSMacros_h

#ifdef __cplusplus
    #define NS_SS_BEGIN namespace senspark {
    #define NS_SS_END   }
    #define USING_NS_SS using namespace senspark
#else
    #define NS_SS_BEGIN
    #define NS_SS_END
    #define USING_NS_SS
#endif

#define EXECUTE_ONCE(ACTION) static bool ACTION = false; \
if (ACTION==true) return; \
ACTION = true;

#define REGISTER_FILE_EXECUTE_ONCE(ACTION) static bool ACTION = false;
#define FILE_EXECUTE_ONCE(ACTION) \
if (ACTION==true) return; \
ACTION = true;
#define RESET_FILE_EXECUTE_ONCE(ACTION) ACTION = false;

#define UNUSED(a) a

#define DUMMY_EVENT_TYPE cocos2d::extension::Control::EventType::TOUCH_CANCEL

#endif
