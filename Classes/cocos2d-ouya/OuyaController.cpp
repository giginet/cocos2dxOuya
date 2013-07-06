/*
 * OuyaController.cpp
 *
 *  Created on: Jul 6, 2013
 *      Author: giginet
 */

#include "OuyaController.h"
#include "platform/android/jni/JniHelper.h"

#define CLASS_NAME "org/kawaz/ouya/odk/OuyaControllerJni"

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
jclass Kawaz::OUYA::OuyaController::getClassID(JNIEnv *pEnv) {
    jclass ret = pEnv->FindClass(CLASS_NAME);
    if (!ret) {
        CCLOG("Failed to find class of %s", CLASS_NAME);
    }

    return ret;
}

bool Kawaz::OUYA::OuyaController::getStaticMethodInfo(JniMethodInfo &methodinfo,
        const char *methodName, const char *paramCode) {
    jmethodID methodID = 0;
    JNIEnv *pEnv = 0;
    bool bRet = false;

    do {
        pEnv = getJNIEnv();
        if (!pEnv) {
            break;
        }

        jclass classID = getClassID(pEnv);

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

Kawaz::OUYA::OuyaController::OuyaController(jobject controllerObject) {
    _controller = controllerObject;
}

Kawaz::OUYA::OuyaController::~OuyaController() {
    // TODO Auto-generated destructor stub
}

Kawaz::OUYA::OuyaController* Kawaz::OUYA::OuyaController::getControllerByDeviceId(int deviceId) {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getStaticMethodInfo(methodInfo, "getControllerByDeviceId", "(I)Ltv/ouya/console/api/OuyaController;")) {
        return NULL;
    }
    jobject cObj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, deviceId);
    OuyaController *controller = new OuyaController(cObj);
    return controller;
}

Kawaz::OUYA::OuyaController* Kawaz::OUYA::OuyaController::getControllerByPlayer(int playerNum) {
    JniMethodInfo methodInfo;
    if (!Kawaz::OUYA::OuyaController::getStaticMethodInfo(methodInfo, "getControllerByPlayer", "(I)Ltv/ouya/console/api/OuyaController;")) {
        return NULL;
    }
    jobject cObj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, playerNum);
    OuyaController *controller = new OuyaController(cObj);
    return controller;
}

int Kawaz::OUYA::OuyaController::getPlayerNum() {
    return 0;
}

int Kawaz::OUYA::OuyaController::getDeviceId() {
    return 0;
}

