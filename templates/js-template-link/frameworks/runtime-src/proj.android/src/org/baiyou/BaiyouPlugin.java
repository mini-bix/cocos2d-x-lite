package org.baiyou;

import java.util.UUID;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.telephony.TelephonyManager;
import android.util.Log;
import org.cocos2dx.lib.Cocos2dxActivity;

public class BaiyouPlugin {
	
	private static Context _app;
	
	public static  Context App(){
		if (_app == null){
			_app = Cocos2dxActivity.getContext();
		}
		return _app;
	}
	
	public static String getProperty(String key){
		try {  
		    ApplicationInfo appInfo = App().getPackageManager().getApplicationInfo(App().getPackageName(),PackageManager.GET_META_DATA);  
		    String value = appInfo.metaData.getString(key);  
		    Log.d("cocos2dx ", " baiyou  meta getProperty : "+ key + " " + value);
		    return value;
		} catch (PackageManager.NameNotFoundException e) {  
		    e.printStackTrace();  
		} 
		return "";
	}
    
    public static String getUUID(){
        final TelephonyManager tm = (TelephonyManager) (App().getSystemService(Context.TELEPHONY_SERVICE));
        final String tmDevice, tmSerial, androidId;
        tmDevice = "" + tm.getDeviceId();
        tmSerial = "" + tm.getSimSerialNumber();
        androidId = "" + android.provider.Settings.Secure.getString(App().getContentResolver(),android.provider.Settings.Secure.ANDROID_ID);
        UUID deviceUuid = new UUID(androidId.hashCode(), ((long)tmDevice.hashCode() << 32) | tmSerial.hashCode());
        String uniqueId = deviceUuid.toString();
        Log.d("cocos2d-x BaiyouPlugin","uuid= "+uniqueId);
        return uniqueId;
    }
    
}
