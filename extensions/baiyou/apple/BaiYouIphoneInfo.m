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

//@interface BaiYouIphoneInfo ()
//
//@property (nonatomic,strong)UIScreen *screen;
//@end

@implementation BaiYouIphoneInfo

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
    return [UIScreen mainScreen].bounds.size.width;
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
    NSString *address = @"error";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"]) {
                    // Get NSString from C String
                    address = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr)];
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    // Free memory
    freeifaddrs(interfaces);
    return address;
#else
    return @"";
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
