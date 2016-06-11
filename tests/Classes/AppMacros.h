#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

/* For demonstrating using one design resolution to match different resources,
   or one resource to match different design resolutions.

   [Situation 1] Using one design resolution to match different resources.
     Please look into Appdelegate::applicationDidFinishLaunching.
     We check current device frame size to decide which resource need to be selected.
     So if you want to test this situation which said in title '[Situation 1]',
     you should change ios simulator to different device(e.g. iphone, iphone-retina3.5, iphone-retina4.0, ipad, ipad-retina),
     or change the window size in "proj.XXX/main.cpp" by "CCEGLView::setFrameSize" if you are using win32 or linux plaform
     and modify "proj.mac/AppController.mm" by changing the window rectangle.

   [Situation 2] Using one resource to match different design resolutions.
     The coordinates in your codes is based on your current design resolution rather than resource size.
     Therefore, your design resolution could be very large and your resource size could be small.
     To test this, just define the marco 'TARGET_DESIGN_RESOLUTION_SIZE' to 'DESIGN_RESOLUTION_2048X1536'
     and open iphone simulator or create a window of 480x320 size.

   [Note] Normally, developer just need to define one design resolution(e.g. 960x640) with one or more resources.
 */

#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_1024X768   1
#define DESIGN_RESOLUTION_2048X1536  2

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_480X320

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::Size(480, 320),   "resources-iphone" };
static Resource mediumResource =  { cocos2d::Size(1024, 768),  "resources-ipad"   };
static Resource largeResource  =  { cocos2d::Size(2048, 1536), "resources-ipadhd" };

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::Size designResolutionSize = cocos2d::Size(2048, 1536);
#else
#error unknown target design resolution!
#endif

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)

#define TESTS_COUNT 7

const std::string testNames[TESTS_COUNT] = {
    "EmptyTest",
    "UtilsTest",
    "CCBUtilsTest",
    "DialogTest",
    "StringResourceTest",
    "SoundMusicTest",
    "ActionTest",
};

enum
{
    TEST_EMPTY = 0,
    TEST_UTILS,
    TEST_CCB_UTILS,
    TEST_DIALOG,
    TEST_STRING_RESOURCE,
    TEST_SOUND_MUSIC,
    TEST_GAME_ACTION
};

#define LINE_SPACE          40

#define FuncLog(MESSAGE) CCLOG("Func = %s: %s", __FUNCTION__, MESSAGE)
#define FileFuncLog(MESSAGE) CCLOG("File = %s Func = %s: %s", __FILE__, __FUNCTION__, MESSAGE)



static const char pathB1[]             = "Images/b1.png";
static const char pathB2[]             = "Images/b2.png";
static const char pathR1[]             = "Images/r1.png";
static const char pathR2[]             = "Images/r2.png";
static const char pathF1[]             = "Images/f1.png";
static const char pathF2[]             = "Images/f2.png";
static const char pathGrossini[]       = "Images/grossini.png";
static const char pathSister1[]        = "Images/grossinis_sister1.png";
static const char pathSister2[]        = "Images/grossinis_sister2.png";
static const char pathClose[]        = "Images/close.png";

#define kVietnamese "vietnamese"
#define kEnglish "english"
#define kTurkish "turkish"
#define kRussian "russian"
#define kThai "thai"

#endif /* __APPMACROS_H__ */
