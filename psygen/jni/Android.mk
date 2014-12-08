LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := psygen

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SRC_FILES := \
    src/Engine/RenderCommands/GlClear.cpp \
    src/Engine/RenderCommands/GlClearColor.cpp \
    src/Engine/RenderCommands/GlEnable.cpp \
    src/Engine/RenderCommands/GlDisable.cpp \
    src/Engine/RenderCommands/GlShader.cpp \
    src/Engine/RenderCommands/GlVertexArray.cpp \
    src/Engine/RenderCommands/GlViewport.cpp \
    src/Engine/AndroidApplication.cpp \
    src/Engine/AndroidDisplay.cpp \
    src/Engine/AndroidEventManager.cpp \
    src/Engine/AndroidLogger.cpp \
    psygen_main.cpp \

#    src/Engine/AndroidClock.cpp \
#    src/Engine/AndroidEventManager.cpp \

LOCAL_CPPFLAGS := -std=c++11
						  
LOCAL_LDLIBS           := -llog -landroid -lEGL -lGLESv2

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)
