/*
 * OuyaController.cpp
 *
 *  Created on: Jul 6, 2013
 *      Author: giginet
 */

#include "OuyaController.h"
#include "platform/android/jni/JniHelper.h"

#define WRAPPER_CLASS_NAME "org/kawaz/ouya/odk/OuyaControllerJni"
#define CONTROLLER_CLASS_NAME "tv/ouya/console/api/OuyaController"

JNIEnv *Kawaz::OUYA::OuyaController::getJNIEnv() {
    JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
    if (NULL == jvm) {
        CCLOG("Failed to get JNIEnv. JniHelper::getJavaVM() is NULL");
        return NULL;
    }

    JNIEnv *env = NULL;
    // get jni environment
    jint ret = jvm->GetEnv((void**) &env, JNI_VERSION_1_4);

    switch (ret) {
    case JNI_OK:
        // Success!
        return env;

    case JNI_EDETACHED:
        // Thread not attached

        // TODO : If calling AttachCurrentThread() on a native thread
        // must call DetachCurrentThread() in future.
        // see: http://developer.android.com/guide/practices/design/jni.html

        if (jvm->AttachCurrentThread(&env, NULL) < 0) {
            CCLOG("Failed to get the environment using AttachCurrentThread()");
            return NULL;
        } else {
            // Success : Attached and obtained JNIEnv!
            return env;
        }

    case JNI_EVERSION:
        // Cannot recover from this error
        CCLOG("JNI interface version 1.4 not supported");
    default:
        CCLOG("Failed to get the environment using GetEnv()");
        return NULL;
    }

}

// get class and make it a global reference, release it at endJni().
jclass Kawaz::OUYA::OuyaController::getClassID(JNIEnv *pEnv,
        const char *className) {
    jclass ret = pEnv->FindClass(className);
    if (!ret) {
        CCLOG("Failed to find class of %s", className);
    }

    return ret;
}

bool Kawaz::OUYA::OuyaController::getStaticMethodInfo(JniMethodInfo &methodinfo,
        const char *className, const char *methodName, const char *paramCode) {
    jmethodID methodID = 0;
    JNIEnv *pEnv = 0;
    bool bRet = false;

    do {
        pEnv = getJNIEnv();
        if (!pEnv) {
            break;
        }

        jclass classID = getClassID(pEnv, className);

        methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
        if (!methodID) {
            CCLOG("Failed to find static method id of %s", methodName);
            break;
        }

        methodinfo.classID = classID;
        methodinfo.env = pEnv;
        methodinfo.methodID = methodID;

        bRet = true;
    } while (0);

    return bRet;
}

bool Kawaz::OUYA::OuyaController::getMethodInfo(JniMethodInfo &methodInfo,
        const char *className, const char *methodName, const char *paramCode) {
    jmethodID methodID = 0;
    JNIEnv *pEnv = 0;
    bool bRet = false;

    do {
        pEnv = getJNIEnv();
        if (!pEnv) {
            break;
        }

        jclass classID = getClassID(pEnv, className);

        methodID = pEnv->GetMethodID(classID, methodName, paramCode);
        if (!methodID) {
            CCLOG("Failed to find method id of %s", methodName);
            break;
        }

        methodInfo.classID = classID;
        methodInfo.env = pEnv;
        methodInfo.methodID = methodID;

        bRet = true;
    } while (0);

    return bRet;
}

Kawaz::OUYA::OuyaController::OuyaController(jobject controllerObject) {
    _controller = controllerObject;
}

Kawaz::OUYA::OuyaController::~OuyaController() {
    // TODO Auto-generated destructor stub
    JNIEnv *env = OuyaController::getJNIEnv();
    env->DeleteLocalRef(_controller);
}

Kawaz::OUYA::OuyaController* Kawaz::OUYA::OuyaController::getControllerByDeviceId(
        int deviceId) {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getStaticMethodInfo(methodInfo,
            WRAPPER_CLASS_NAME, "getControllerByDeviceId",
            "(I)Ltv/ouya/console/api/OuyaController;")) {
        return NULL;
    }
    jobject cObj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID,
            methodInfo.methodID, deviceId);
    OuyaController *controller = new OuyaController(cObj);
    return controller;
}

Kawaz::OUYA::OuyaController* Kawaz::OUYA::OuyaController::getControllerByPlayer(
        int playerNum) {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getStaticMethodInfo(methodInfo,
            WRAPPER_CLASS_NAME, "getControllerByPlayer",
            "(I)Ltv/ouya/console/api/OuyaController;")) {
        return NULL;
    }
    jobject cObj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID,
            methodInfo.methodID, playerNum);
    OuyaController *controller = new OuyaController(cObj);
    return controller;
}

int Kawaz::OUYA::OuyaController::getPlayerNum() {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getMethodInfo(methodInfo,
            CONTROLLER_CLASS_NAME, "getPlayerNum", "()I")) {
        return 0;
    }
    int num = methodInfo.env->CallIntMethod(_controller, methodInfo.methodID);
    return num;
}

int Kawaz::OUYA::OuyaController::getDeviceId() {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getMethodInfo(methodInfo,
            CONTROLLER_CLASS_NAME, "getDeviceId", "()I")) {
        return 0;
    }
    int deviceId = methodInfo.env->CallIntMethod(_controller,
            methodInfo.methodID);
    return deviceId;
}

bool Kawaz::OUYA::OuyaController::buttonChangedThisFrame(int ouyaButton) {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getMethodInfo(methodInfo,
            CONTROLLER_CLASS_NAME, "buttonChangeThisFrame", "(I)Z")) {
        return false;
    }
    return methodInfo.env->CallBooleanMethod(_controller, methodInfo.methodID,
            ouyaButton);
}

float Kawaz::OUYA::OuyaController::getAxisValue(int ouyaAxis) {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getMethodInfo(methodInfo,
            CONTROLLER_CLASS_NAME, "getAxisValue", "(I)F")) {
        return 0;
    }
    jfloat f = methodInfo.env->CallFloatMethod(_controller, methodInfo.methodID, ouyaAxis);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return f;
}

bool Kawaz::OUYA::OuyaController::getButton(int ouyaButton) {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getMethodInfo(methodInfo,
            CONTROLLER_CLASS_NAME, "getButton", "(I)Z")) {
        return false;
    }
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return methodInfo.env->CallBooleanMethod(_controller, methodInfo.methodID,
            ouyaButton);
}

int Kawaz::OUYA::OuyaController::getPlayerNumByDeviceId(int deviceId) {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getStaticMethodInfo(methodInfo,
            CONTROLLER_CLASS_NAME, "getPlayerNumByDeviceId", "(I)I")) {
        return 0;
    }
    return methodInfo.env->CallStaticIntMethod(methodInfo.classID,
            methodInfo.methodID, deviceId);
}

void Kawaz::OUYA::OuyaController::startOfFrame() {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getStaticMethodInfo(methodInfo,
            WRAPPER_CLASS_NAME, "startOfFrame", "()V")) {
    }
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
}
