package org.baiyou;

import java.util.ArrayList;
import java.util.UUID;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.PowerManager;
import android.os.SystemClock;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.WindowManager;

import org.cocos2dx.lib.Cocos2dxActivity;

public class BaiyouPlugin {
	
	private static Activity _app;
	
	private static int currentNotificationID;
	
	private static ArrayList<PendingIntent> pendingInAlarms = new ArrayList<PendingIntent>();
	
	private static PowerManager.WakeLock mWakeLock;
	
	public static  Activity App(){
		if (_app == null){
			_app = (Activity)Cocos2dxActivity.getContext();
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
    
    public static String getPackageName(){
        return App().getPackageName();
    }
    
    public static void setIdleTimerDisabled(boolean dis){
    	if (dis){
    		if (mWakeLock == null){
    			PowerManager pm = (PowerManager) App().getSystemService(Context.POWER_SERVICE);  
    			mWakeLock = pm.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK, "My Tag"); 
    		}
    		if (!mWakeLock.isHeld()){
    			Log.d("cocos2d-x BaiyouPlugin","Wake Lock Acquuire Called");
    			mWakeLock.acquire();
    		}
    	}else{
    		if (mWakeLock != null && mWakeLock.isHeld()){
    			Log.d("cocos2d-x BaiyouPlugin","Wake Lock Release Called");
    			mWakeLock.release();
    		}
    	}
    }
    
    public static void scheduleLocalNotification(String title,String content,int delay){
    	try{
	    	AlarmManager alarmManager = (AlarmManager)App().getSystemService(Context.ALARM_SERVICE);
			Intent intent = new Intent(App(),TimeAlarm.class);
			intent.putExtra("id", currentNotificationID++);
			intent.putExtra("icon", App().getResources().getIdentifier("icon", "drawable", App().getPackageName()));
			intent.putExtra("title", title);
			intent.putExtra("content", content);
			PendingIntent pendingIntent = PendingIntent.getBroadcast(App(), 
					0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
			alarmManager.set(AlarmManager.ELAPSED_REALTIME_WAKEUP, SystemClock.elapsedRealtime()+delay*1000 ,pendingIntent);
			pendingInAlarms.add(pendingIntent);
    	}catch(Exception e){
    		e.printStackTrace();
    	}
    	
    }
    
    public static void unScheduleAllLocalNotification(){
    	NotificationManager notifiManger = (NotificationManager)App().getSystemService(Context.NOTIFICATION_SERVICE);
		notifiManger.cancelAll();
		
		AlarmManager alarmManager = (AlarmManager)App().getSystemService(Context.ALARM_SERVICE);
		for (int i = 0; i < pendingInAlarms.size(); i++) {
			try{
				alarmManager.cancel(pendingInAlarms.get(i));
			}catch(Exception e){
				e.printStackTrace();
			}
		}
		pendingInAlarms.clear();
    }
    
}
