package org.baiyou;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.NotificationCompat;
import org.cocos2dx.javascript.AppActivity;

public class TimeAlarm extends BroadcastReceiver {
	
	public void onReceive (Context context,Intent paramIntent){
		Context appContext = BaiyouPlugin.App().getApplicationContext();
		Bundle extras = paramIntent.getExtras();
		String title = extras.getString("title");
		String content = extras.getString("content");
		int icon = extras.getInt("icon");
		int notiId = extras.getInt("id");
		
		Intent showTaskIntent = new Intent(appContext, AppActivity.class);
		showTaskIntent.setAction(Intent.ACTION_MAIN);
		showTaskIntent.addCategory(Intent.CATEGORY_LAUNCHER);
		showTaskIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		 
		PendingIntent contentIntent = PendingIntent.getActivity(
				appContext,
		0,
		showTaskIntent,
		PendingIntent.FLAG_UPDATE_CURRENT);
		NotificationManager notifiManger = (NotificationManager)appContext.getSystemService (Context.NOTIFICATION_SERVICE);
		Notification noti = new NotificationCompat.Builder(BaiyouPlugin.App())
		.setSmallIcon(icon)
        .setContentTitle(title)
        .setContentText(content)
        .setContentIntent(contentIntent)
        .setDefaults(Notification.DEFAULT_SOUND)
 //       .setWhen(System.currentTimeMillis())
//        .setWhen(System.currentTimeMillis())
        .build();
		noti.tickerText = content;
		noti.flags |= Notification.FLAG_AUTO_CANCEL;
		notifiManger.notify(notiId,noti);
	}

}
