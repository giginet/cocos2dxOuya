/*
 * OuyaController.h
 *
 *  Created on: Jul 6, 2013
 *      Author: giginet
 */

#ifndef OUYACONTROLLER_H_
#define OUYACONTROLLER_H_

#include <jni.h>
#include "cocos2d.h"

namespace Kawaz {
    namespace OUYA {

        typedef struct JniMethodInfo_
        {
            JNIEnv *    env;
            jclass      classID;
            jmethodID   methodID;
        } JniMethodInfo;

        class OuyaController;

        class OuyaController {

          private:
            jobject _controller;
            OuyaController(jobject controllerObject);
            static JNIEnv *getJNIEnv();
            static jclass getClassID(JNIEnv *pEnv, const char *className);
            static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode);
            static bool getMethodInfo(JniMethodInfo &methodInfo, const char *className, const char *methodName, const char *paramCode);
          public:
            virtual ~OuyaController();
            static OuyaController* getControllerByDeviceId(int deviceId);
            static OuyaController* getControllerByPlayer(int playerNum);
            static int getPlayerNumByDeviceId(int deviceId);
            /*static bool onGenericMotionEvent();
            static bool onKeyDown(int keyCode);
            static bool onKeyUp(int keyCode);*/
            static void startOfFrame();
            int getDeviceId();
            int getPlayerNum();
            bool buttonChangedThisFrame(int ouyaButton);
            float getAxisValue(int ouyaAxis);
            bool getButton(int ouyaButton);

            static const int MAX_CONTROLLERS = 4;
            static const float STICK_DEADZONE = 0.25f;

            enum {
                AXIS_L2 = 17,
                AXIS_LS_X = 0,
                AXIS_LS_Y = 1,
                AXIS_R2 = 18,
                AXIS_RS_X = 11,
                AXIS_RS_Y = 14,
                BUTTON_A = 97,
                BUTTON_DPAD_DOWN = 20,
                BUTTON_DPAD_LEFT = 21,
                BUTTON_DPAD_RIGHT = 22,
                BUTTON_DPAD_UP = 19,
                BUTTON_L1 = 102,
                BUTTON_L2 = 104,
                BUTTON_L3 = 106,
                BUTTON_MENU = 82,
                BUTTON_O = 96,
                BUTTON_R1 = 103,
                BUTTON_R2 = 105,
                BUTTON_R3 = 107,
                BUTTON_U = 99,
                BUTTON_Y = 100
            };
        };

    }
}

#endif /* OUYACONTROLLER_H_ */
