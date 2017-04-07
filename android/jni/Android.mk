LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(COCOS2DX_ROOT))
$(call import-add-path,$(COCOS2DX_ROOT)/external)
$(call import-add-path,$(COCOS2DX_ROOT)/cocos)
$(call import-add-path,$(COCOS2DX_ROOT)/cocos/editor-support/cocosbuilder)
$(call import-add-path,$(COCOS2DX_ROOT)/extensions)
#$(call import-add-path,$(COCOS2DX_ROOT)/cocos/prebuilt-mk)

LOCAL_MODULE := sensparkgamefoundation_static

LOCAL_MODULE_FILENAME := libsensparkgamefoundation

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)

LOCAL_SRC_FILES := cpp/main.cpp
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(LOCAL_PATH)/../../include/gameXtension.h

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include/gameXtension.h
					

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../include
					
LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocosdenshion_static 
LOCAL_STATIC_LIBRARIES += cocos_extension_static 
LOCAL_STATIC_LIBRARIES += cocosbuilder_static

include $(BUILD_STATIC_LIBRARY)

#$(call import-module,.)
#$(call import-module,extensions/prebuilt-mk)
#$(call import-module,editor-support/cocosbuilder/prebuilt-mk)
#$(call import-module,prebuilt-mk)
