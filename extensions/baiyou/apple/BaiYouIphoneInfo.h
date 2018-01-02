//
//  BaiYouIphoneInfo.h
//  cocos2d_libs
//
//  Created by wuxiaolan on 2017/11/17.
//

#import <Foundation/Foundation.h>

@interface BaiYouIphoneInfo : NSObject


/**
 得到当前手机所属运营商名称，如果没有则为nil
 @return 返回运营商名称
 */
+ (NSString *)getCurrentPhoneOperatorName;
//返回当前网络类型
+ (NSString *)getNetWorkStaus;
//返回cpu信息
+ (NSString *)getCPUInfo;
//返回gpu信息
+ (NSString *)getGPUInfo;
//返回屏幕宽度
+ (CGFloat)getCurrentScreenWith;
//返回屏幕高度
+ (CGFloat)getCurrentScreenHeight;
//返回屏幕dpi
+ (CGFloat)getScreenDpi;
//返回内存大小
+ (NSString *)getTotalMemorySize;
//返回ip地址
+ (NSString *)getIPAddress;
//返回OpenGL render信息
+ (NSString *)getOpenGLRender;
//返回OpenGL版本
+ (NSString *)getOpenGLVersion;
//返回设备型号
+ (NSString *)getDeviceName;
@end
