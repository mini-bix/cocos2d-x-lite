package org.baiyou;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileFilter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.UUID;

import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.AlarmManager;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.ConfigurationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.Resources;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.opengl.GLES10;
import android.os.Build;
import android.os.PowerManager;
import android.os.SystemClock;
import android.telephony.TelephonyManager;
import android.text.format.Formatter;
import android.util.DisplayMetrics;
import android.util.Log;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;

import com.aiyou.gamecloud.ucenter.MainActivity;

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
    
    public static String getVersionName(){
    	PackageInfo pInfo;
		try {
			pInfo = App().getPackageManager().getPackageInfo(App().getPackageName(), 0);
			return pInfo.versionName;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			return "";
		}
    }
    
    public static DisplayMetrics getScreenWidth(){
		Resources resources = App().getResources();
		DisplayMetrics dm = resources.getDisplayMetrics();
		return dm;
    }
    
    public static String getOpenGLVersion(){
    	ActivityManager am =(ActivityManager) App().getSystemService(Context.ACTIVITY_SERVICE); 
    	ConfigurationInfo info = am.getDeviceConfigurationInfo();
		return info.getGlEsVersion();
    }
    
    public static String getOperators(Context context) {
        TelephonyManager tm = (TelephonyManager) context
                .getSystemService(Context.TELEPHONY_SERVICE);
        String operator = "";
        String IMSI = tm.getSubscriberId();
        if (IMSI == null || IMSI.equals("")) {
            return operator;
        }
        operator = IMSI;
        return operator;
    }
    
    public static String getNetWorkType(Context context) {
    	  //结果返回值
    	  String netType = "nono_connect";
    	  //获取手机所有连接管理对象
    	  ConnectivityManager manager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
    	  //获取NetworkInfo对象
    	  NetworkInfo networkInfo = manager.getActiveNetworkInfo();
    	  //NetworkInfo对象为空 则代表没有网络
    	  if (networkInfo == null) {
    	    return netType;
    	  }
    	  //否则 NetworkInfo对象不为空 则获取该networkInfo的类型
    	  int nType = networkInfo.getType();
    	  if (nType == ConnectivityManager.TYPE_WIFI) {
    	    //WIFI
    	    netType = "Wifi";
    	  } else if (nType == ConnectivityManager.TYPE_MOBILE) {
    		  netType = "Mobile";
    	  }
    	  return netType;
    }
    
    public static String getTotalMemory() { 
        String str1 = "/proc/meminfo";// 系统内存信息文件 
        String str2; 
        String[] arrayOfString; 
        long initial_memory = 0; 
      
        try { 
          FileReader localFileReader = new FileReader(str1); 
          BufferedReader localBufferedReader = new BufferedReader( 
              localFileReader, 8192); 
          str2 = localBufferedReader.readLine();
      
          arrayOfString = str2.split("\\s+"); 
          for (String num : arrayOfString) { 
            Log.i(str2, num + "\t"); 
          } 
      
          initial_memory = Integer.valueOf(arrayOfString[1]).intValue()/1024;// 获得系统总内存，单位是KB，乘以1024转换为Byte 
          localBufferedReader.close(); 
      
        } catch (IOException e) { 
        } 
        return String.valueOf(initial_memory);// Byte转换为KB或者MB，内存大小规格化 
     }
    
    public static String getIPAddress(Context context) {
        NetworkInfo info = ((ConnectivityManager) context
                .getSystemService(Context.CONNECTIVITY_SERVICE)).getActiveNetworkInfo();
        if (info != null && info.isConnected()) {
            if (info.getType() == ConnectivityManager.TYPE_MOBILE) {//当前使用2G/3G/4G网络
                try {
                    //Enumeration<NetworkInterface> en=NetworkInterface.getNetworkInterfaces();
                    for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements(); ) {
                        NetworkInterface intf = en.nextElement();
                        for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements(); ) {
                            InetAddress inetAddress = enumIpAddr.nextElement();
                            if (!inetAddress.isLoopbackAddress() && inetAddress instanceof Inet4Address) {
                                return inetAddress.getHostAddress();
                            }
                        }
                    }
                } catch (SocketException e) {
                    e.printStackTrace();
                }

            } else if (info.getType() == ConnectivityManager.TYPE_WIFI) {//当前使用无线网络
                WifiManager wifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
                WifiInfo wifiInfo = wifiManager.getConnectionInfo();
                String ipAddress = intIP2StringIP(wifiInfo.getIpAddress());//得到IPV4地址
                return ipAddress;
            }
        } else {
        	return "";
        }
        return "";
    }

    public static String intIP2StringIP(int ip) {
        return (ip & 0xFF) + "." +
                ((ip >> 8) & 0xFF) + "." +
                ((ip >> 16) & 0xFF) + "." +
                (ip >> 24 & 0xFF);
    }
    
    public static String getCPUInfo(){
    	String cpuInfo = "";
    	 try{  
    	      FileReader fr = new FileReader("/proc/cpuinfo");  
    	      BufferedReader br = new BufferedReader(fr);  
    	      String text = br.readLine();  
    	      String[] array = text.split(":\\s+",2);  
    	       for(int i = 0; i < array.length; i++){  
    	       }  
    	       cpuInfo = array[1];  
    	  }catch(FileNotFoundException e){  
    	    e.printStackTrace();  
    	  }catch (IOException e){  
    	     e.printStackTrace();  
    	  }
         String result = "";    
         ProcessBuilder cmd;    
         try {    
                 String[] args = { "/system/bin/cat",    
                                 "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq" };    
                 cmd = new ProcessBuilder(args);    
                 Process process = cmd.start();    
                 InputStream in = process.getInputStream();    
                 byte[] re = new byte[24];    
                 while (in.read(re) != -1) {    
                         result = result + new String(re);    
                 }    
                 in.close();    
         } catch (IOException ex) {    
                 ex.printStackTrace();    
                 result = "0";    
         }
        cpuInfo =cpuInfo +"-"+ result.trim(); 
        String count = "";
        if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.GINGERBREAD_MR1) {
        	count = "1";
          }
          try {
        	  count = String.valueOf(new File("/sys/devices/system/cpu/").listFiles(CPU_FILTER).length);
          } catch (SecurityException e) {
        	  count = "0";
          } catch (NullPointerException e) {
        	  count = "0";
          }
        cpuInfo =cpuInfo +"-"+ count;
    	return cpuInfo;
    }
    
    private static final FileFilter CPU_FILTER = new FileFilter() {
    	  @Override
    	  public boolean accept(File pathname) {
    	    String path = pathname.getName();
    	    //regex is slow, so checking char by char.
    	    if (path.startsWith("cpu")) {
    	      for (int i = 3; i < path.length(); i++) {
    	        if (path.charAt(i) < '0' || path.charAt(i) > '9') {
    	          return false;
    	        }
    	      }
    	      return true;
    	    }
    	    return false;
    	  }
    	};
    
    public static String getDeviceInfo(){
    	
    	try {
    		JSONObject info = new JSONObject();
    		info.put("systemName", "android");
			info.put("systemVersion",android.os.Build.VERSION.RELEASE);
			info.put("device",android.os.Build.DEVICE);
			info.put("model",android.os.Build.MODEL);
			info.put("screenWidth", String.valueOf(getScreenWidth().widthPixels));
			info.put("screenHeight", String.valueOf(getScreenWidth().heightPixels));
			info.put("screenDpi", String.valueOf(getScreenWidth().densityDpi));
			info.put("netWork", getNetWorkType(App()));
			info.put("totalMemory", getTotalMemory());
			info.put("openglVersion",getOpenGLVersion());
			info.put("operatorName", getOperators(App()));
			info.put("ip", getIPAddress(App()));
			info.put("cpuInfo", getCPUInfo());
			info.put("gpuInfo", "");
			info.put("openglRender", GLES10.glGetString(GL10.GL_RENDERER));
			return info.toString(2);
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return "{}";
		}
    }
    
}
