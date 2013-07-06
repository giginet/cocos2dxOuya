/**
 *  OuyaControllerJni.java 
 *  created by giginet on Jul 6, 2013
 */
package org.kawaz.ouya.odk;

import android.view.KeyEvent;
import tv.ouya.console.api.OuyaController;

/**
 * This is a wrapper class for tv.ouya.console.api.OuyaController It enables to
 * get controller state from Native Code via JNI.
 * 
 * @author giginet
 * 
 */
public class OuyaControllerJni{
    
    public static boolean buttonChangedThisFrame(int deviceId, int ouyaButton){
        
        return false;
    }

    public static int getPlayerNumByDeviceId(int deviceId){
        return OuyaController.getPlayerNumByDeviceId(deviceId);
    }
    
    public static OuyaController getControllerByPlayer(int playerNum) {
        return OuyaController.getControllerByPlayer(playerNum);
    }
    
    public static OuyaController getControllerByDeviceId(int deviceId) {
        return OuyaController.getControllerByDeviceId(deviceId);
    }

    public static boolean onKeyDown(int keyCode){
        return OuyaController.onKeyDown(keyCode, new KeyEvent(keyCode,
                KeyEvent.ACTION_DOWN));
    }

    public static boolean onKeyUp(int keyCode){
        return OuyaController.onKeyUp(keyCode, new KeyEvent(keyCode,
                KeyEvent.ACTION_UP));
    }

    public static void startOfFrame(){
        OuyaController.startOfFrame();
    }
    
}
