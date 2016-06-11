LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/ActionTestScene.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/BaseTest.cpp \
../../Classes/CCBTestLayer.cpp \
../../Classes/CCBUtilsTestScene.cpp \
../../Classes/controller.cpp \
../../Classes/DialogTestScene.cpp \
../../Classes/EmptyTestScene.cpp \
../../Classes/SoundMusicTestScene.cpp \
../../Classes/StringResourceTestScene.cpp \
../../Classes/testBasic.cpp \
../../Classes/TestOneAction.cpp \
../../Classes/TestSoundDialog.cpp \
../../Classes/TestTwoAction.cpp \
../../Classes/UtilsTestScene.cpp \
../../Classes/VisibleRect.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../../cocos2d \
					$(LOCAL_PATH)/../../../cocos2d/cocos \
					$(LOCAL_PATH)/../../../cocos2d/cocos/editor-support \
					$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include \
					$(LOCAL_PATH)/../../../cocos2d/extensions \
					$(LOCAL_PATH)/../../../cocos2d/cocos/editor-support/cocosbuilder \
					$(LOCAL_PATH)/../../../cocos2d/cocos/editor-support/cocosstudio \

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_STATIC_LIBRARIES += cocostudio_static
LOCAL_STATIC_LIBRARIES += sensparkgamefoundation_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,extensions)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/cocostudio)
$(call import-module,android/jni)
