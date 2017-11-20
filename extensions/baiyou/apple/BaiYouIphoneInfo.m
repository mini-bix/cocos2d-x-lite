//
//  BaiYouIphoneInfo.m
//  cocos2d_libs
//
//  Created by wuxiaolan on 2017/11/17.
//

#import "BaiYouIphoneInfo.h"
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#import <CoreTelephony/CTCarrier.h>
#import <SystemConfiguration/CaptiveNetwork.h>
#import <UIkit/UIScreen.h>
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
    CTTelephonyNetworkInfo *info = [CTTelephonyNetworkInfo new];
    CTCarrier *carrier = [info subscriberCellularProvider];
    
    if (!carrier.isoCountryCode) {
        return @"";
    }
    return [NSString stringWithFormat:@"%@%@",[carrier mobileCountryCode],[carrier mobileNetworkCode]];
}

+ (NSString *)getNetWorkStaus {
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
}

+ (CGFloat)getCurrentScreenWith {
    return  [UIScreen mainScreen].bounds.size.width;
}
+ (CGFloat)getCurrentScreenHeight {
    return [UIScreen mainScreen].bounds.size.width;
}

+ (CGFloat)getScreenDpi {
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
}

+ (NSString *)getCPUInfo{
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
}

+ (NSString *)getGPUInfo{
    NSString * gpuInfo = @"";
    return gpuInfo;
}

+ (NSString *)getTotalMemorySize
{
    long long size =[NSProcessInfo processInfo].physicalMemory;
    
    return [NSString stringWithFormat:@"%.1f",size/1024.f/1024.f];
}

+ (NSString *)getIPAddress {
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
    
}

+ (NSString *)getOpenGLRender{
    NSString * OpenGLVersion = [NSString stringWithCString:(const char*)glGetString(GL_RENDERER) encoding:NSASCIIStringEncoding];
    return OpenGLVersion;
}

+ (NSString *)getOpenGLVersion{
    NSString * OpenGLVersion = [NSString stringWithCString:(const char*)glGetString(GL_VERSION) encoding:NSASCIIStringEncoding];
    return OpenGLVersion;
}

@end
