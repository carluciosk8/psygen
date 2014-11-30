LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE           := psygen

LOCAL_C_INCLUDES       := $(LOCAL_PATH)/include

LOCAL_SRC_FILES        := \
	psygen_main.cpp \
    Square.cpp \
    src/Engine/AndroidLogger.cpp \
    src/Engine/AndroidApplication.cpp \
    src/Engine/AndroidDisplay.cpp \
    #src/Engine/AndroidTimeSource.cpp \
    #src/Engine/Application.cpp \
    #src/Engine/Clock.cpp \
    #src/Engine/Node.cpp \
    #src/Engine/Renderer.cpp \
						  
LOCAL_LDLIBS           := -llog -landroid -lEGL -lGLESv2

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)
