//
//  BaiYouIphoneInfo.m
//  cocos2d_libs
//
//  Created by wuxiaolan on 2017/11/17.
//
#include "platform/CCPlatformConfig.h"
#import "BaiYouIphoneInfo.h"
#import <SystemConfiguration/CaptiveNetwork.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#import <CoreTelephony/CTCarrier.h>
#import <UIkit/UIScreen.h>
#endif
#import <mach/mach_host.h>
#import "Reachability.h"
#import <ifaddrs.h>
#import <arpa/inet.h>
#import <sys/utsname.h>

//@interface BaiYouIphoneInfo ()
//
//@property (nonatomic,strong)UIScreen *screen;
//@end

@implementation BaiYouIphoneInfo

+ (NSString *)getDeviceName {
    struct utsname systemInfo;
    
    uname(&systemInfo);
    NSString* platform = [NSString stringWithCString:systemInfo.machine
                                        encoding:NSUTF8StringEncoding];
    if ([platform isEqualToString:@"iPhone1,1"]) return @"iPhone2G";
    if ([platform isEqualToString:@"iPhone1,2"]) return @"iPhone3G";
    if ([platform isEqualToString:@"iPhone2,1"]) return @"iPhone3GS";
    if ([platform isEqualToString:@"iPhone3,1"]) return @"iPhone4";
    if ([platform isEqualToString:@"iPhone3,2"]) return @"iPhone4";
    if ([platform isEqualToString:@"iPhone3,3"]) return @"iPhone4";
    if ([platform isEqualToString:@"iPhone4,1"]) return @"iPhone4S";
    if ([platform isEqualToString:@"iPhone5,1"]) return @"iPhone5";
    if ([platform isEqualToString:@"iPhone5,2"]) return @"iPhone5";
    if ([platform isEqualToString:@"iPhone5,3"]) return @"iPhone5c";
    if ([platform isEqualToString:@"iPhone5,4"]) return @"iPhone5c";
    if ([platform isEqualToString:@"iPhone6,1"]) return @"iPhone5s";
    if ([platform isEqualToString:@"iPhone6,2"]) return @"iPhone5s";
    if ([platform isEqualToString:@"iPhone7,2"]) return @"iPhone6";
    if ([platform isEqualToString:@"iPhone7,1"]) return @"iPhone6Plus";
    if ([platform isEqualToString:@"iPhone8,1"]) return @"iPhone6s";
    if ([platform isEqualToString:@"iPhone8,2"]) return @"iPhone6sPlus";
    if ([platform isEqualToString:@"iPhone8,3"]) return @"iPhoneSE";
    if ([platform isEqualToString:@"iPhone8,4"]) return @"iPhoneSE";
    if ([platform isEqualToString:@"iPhone9,1"]) return @"iPhone7";
    if ([platform isEqualToString:@"iPhone9,2"]) return @"iPhone7Plus";
    if ([platform isEqualToString:@"iPhone9,3"])    return @"iPhone7";
    if ([platform isEqualToString:@"iPhone9,4"])    return @"iPhone7Plus";
    if ([platform isEqualToString:@"iPhone10,1"])   return @"iPhone8";
    if ([platform isEqualToString:@"iPhone10,4"])   return @"iPhone8";
    if ([platform isEqualToString:@"iPhone10,2"])   return @"iPhone8Plus";
    if ([platform isEqualToString:@"iPhone10,5"])   return @"iPhone8Plus";
    if ([platform isEqualToString:@"iPhone10,3"])   return @"iPhoneX";
    if ([platform isEqualToString:@"iPhone10,6"])   return @"iPhoneX";
    
    //iPod Touch
    if ([platform isEqualToString:@"iPod1,1"])   return @"iPodTouch";
    if ([platform isEqualToString:@"iPod2,1"])   return @"iPodTouch2G";
    if ([platform isEqualToString:@"iPod3,1"])   return @"iPodTouch3G";
    if ([platform isEqualToString:@"iPod4,1"])   return @"iPodTouch4G";
    if ([platform isEqualToString:@"iPod5,1"])   return @"iPodTouch5G";
    if ([platform isEqualToString:@"iPod7,1"])   return @"iPodTouch6G";
    
    //iPad
    if ([platform isEqualToString:@"iPad1,1"])   return @"iPad";
    if ([platform isEqualToString:@"iPad2,1"])   return @"iPad2";
    if ([platform isEqualToString:@"iPad2,2"])   return @"iPad2";
    if ([platform isEqualToString:@"iPad2,3"])   return @"iPad2";
    if ([platform isEqualToString:@"iPad2,4"])   return @"iPad2";
    if ([platform isEqualToString:@"iPad3,1"])   return @"iPad3";
    if ([platform isEqualToString:@"iPad3,2"])   return @"iPad3";
    if ([platform isEqualToString:@"iPad3,3"])   return @"iPad3";
    if ([platform isEqualToString:@"iPad3,4"])   return @"iPad4";
    if ([platform isEqualToString:@"iPad3,5"])   return @"iPad4";
    if ([platform isEqualToString:@"iPad3,6"])   return @"iPad4";
    
    //iPad Air
    if ([platform isEqualToString:@"iPad4,1"])   return @"iPadAir";
    if ([platform isEqualToString:@"iPad4,2"])   return @"iPadAir";
    if ([platform isEqualToString:@"iPad4,3"])   return @"iPadAir";
    if ([platform isEqualToString:@"iPad5,3"])   return @"iPadAir2";
    if ([platform isEqualToString:@"iPad5,4"])   return @"iPadAir2";
    
    //iPad mini
    if ([platform isEqualToString:@"iPad2,5"])   return @"iPadmini1G";
    if ([platform isEqualToString:@"iPad2,6"])   return @"iPadmini1G";
    if ([platform isEqualToString:@"iPad2,7"])   return @"iPadmini1G";
    if ([platform isEqualToString:@"iPad4,4"])   return @"iPadmini2";
    if ([platform isEqualToString:@"iPad4,5"])   return @"iPadmini2";
    if ([platform isEqualToString:@"iPad4,6"])   return @"iPadmini2";
    if ([platform isEqualToString:@"iPad4,7"])   return @"iPadmini3";
    if ([platform isEqualToString:@"iPad4,8"])   return @"iPadmini3";
    if ([platform isEqualToString:@"iPad4,9"])   return @"iPadmini3";
    if ([platform isEqualToString:@"iPad5,1"])   return @"iPadmini4";
    if ([platform isEqualToString:@"iPad5,2"])   return @"iPadmini4";
    
    if ([platform isEqualToString:@"i386"])      return @"iPhoneSimulator";
    if ([platform isEqualToString:@"x86_64"])    return @"iPhoneSimulator";
    return platform;
}

+ (NSString *)getCurrentPhoneOperatorName {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CTTelephonyNetworkInfo *info = [CTTelephonyNetworkInfo new];
    CTCarrier *carrier = [info subscriberCellularProvider];
    
    if (!carrier.isoCountryCode) {
        return @"";
    }
    return [NSString stringWithFormat:@"%@%@",[carrier mobileCountryCode],[carrier mobileNetworkCode]];
#else
    return @"";
#endif

}

+ (NSString *)getNetWorkStaus {
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Reachability *reach = [Reachability reachabilityWithHostName:@"www.apple.com"];
    switch ([reach currentReachabilityStatus]) {
        case ReachableViaWiFi:   //使用的wifi
            return @"Wifi";
            break;
        case ReachableViaWWAN:  //使用的移动网络
            return @"Mobile";
            break;
        default:
            return @"";
            break;
    }
#else
    return @"";
#endif
}

+ (CGFloat)getCurrentScreenWith {
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        return  [UIScreen mainScreen].bounds.size.width;
    #else
        return 0;
    #endif
}
+ (CGFloat)getCurrentScreenHeight {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return [UIScreen mainScreen].bounds.size.height;
#else
    return 0;
#endif
}

+ (CGFloat)getScreenDpi {
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    float scale = 1;
    if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) {
        scale = [[UIScreen mainScreen] scale];
    }
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        return 132*scale;
    }else if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        return 163*scale;
    }else {
        return 160*scale;
    }
#else
    return 0;
#endif
}

+ (NSString *)getCPUInfo{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    host_basic_info_data_t hostInfo;
    mach_msg_type_number_t infoCount;
    
    infoCount = HOST_BASIC_INFO_COUNT;
    host_info(mach_host_self(), HOST_BASIC_INFO, (host_info_t)&hostInfo, &infoCount);
    NSString * cpuInfo = @"";
    switch (hostInfo.cpu_type) {
        case CPU_TYPE_ARM:
            cpuInfo = @"ARM";
            break;
            
        case CPU_TYPE_ARM64:
            cpuInfo = @"ARM64";
            break;
            
        case CPU_TYPE_X86:
            cpuInfo = @"X86";
            break;
            
        case CPU_TYPE_X86_64:
            cpuInfo = @"X86_64";
            break;
        default:
            break;
    }
    integer_t cpuC = hostInfo.max_cpus;
    NSString * cpuCount = [NSString stringWithFormat:@"%d",cpuC];
    cpuInfo = [NSString stringWithFormat:@"%@%@%@",cpuInfo,@"-",cpuCount];
    return cpuInfo;
#else
    return @"";
#endif
}

+ (NSString *)getGPUInfo{
    NSString * gpuInfo = @"";
    return gpuInfo;
}

+ (NSString *)getTotalMemorySize
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    long long size =[NSProcessInfo processInfo].physicalMemory;
    
    return [NSString stringWithFormat:@"%.1f",size/1024.f/1024.f];
#else
    return @"";
#endif
}

+ (NSString *)getIPAddress {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NSError *error;
    NSURL *ipURL = [NSURL URLWithString:@"http://pv.sohu.com/cityjson?ie=utf-8"];
    
    NSMutableString *ip = [NSMutableString stringWithContentsOfURL:ipURL encoding:NSUTF8StringEncoding error:&error];
    //判断返回字符串是否为所需数据
    if ([ip hasPrefix:@"var returnCitySN = "]) {
        //对字符串进行处理，然后进行json解析
        //删除字符串多余字符串
        NSRange range = NSMakeRange(0, 19);
        [ip deleteCharactersInRange:range];
        NSString * nowIp =[ip substringToIndex:ip.length-1];
        //将字符串转换成二进制进行Json解析
        NSData * data = [nowIp dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary * dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
        NSLog(@"%@",dict);
        return dict[@"cip"] ? dict[@"cip"] : @"error";
    }
    return @"error";
//    return (ipStr ? ipStr : @"");
//    NSString *address = @"error";
//    struct ifaddrs *interfaces = NULL;
//    struct ifaddrs *temp_addr = NULL;
//    int success = 0;
//    // retrieve the current interfaces - returns 0 on success
//    success = getifaddrs(&interfaces);
//    if (success == 0) {
//        // Loop through linked list of interfaces
//        temp_addr = interfaces;
//        while(temp_addr != NULL) {
//            if(temp_addr->ifa_addr->sa_family == AF_INET) {
//                // Check if interface is en0 which is the wifi connection on the iPhone
//                if([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"]) {
//                    // Get NSString from C String
//                    address = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr)];
//                }
//            }
//            temp_addr = temp_addr->ifa_next;
//        }
//    }
//    // Free memory
//    freeifaddrs(interfaces);
#else
    return @"error";
#endif
    
}

+ (NSString *)getOpenGLRender{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NSString * OpenGLVersion = [NSString stringWithCString:(const char*)glGetString(GL_RENDERER) encoding:NSASCIIStringEncoding];
    return OpenGLVersion;
#else
    return @"";
#endif
}

+ (NSString *)getOpenGLVersion{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NSString * OpenGLVersion = [NSString stringWithCString:(const char*)glGetString(GL_VERSION) encoding:NSASCIIStringEncoding];
    return OpenGLVersion;
#else
    return @"";
#endif
}

@end
