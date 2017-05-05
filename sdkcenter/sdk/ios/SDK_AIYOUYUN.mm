//
//  SDK_AIYOUYUN.cpp
//  cocos2d_libs
//
//  Created by gumin on 2017/5/5.
//
//

#include "SDK_AIYOUYUN.h"
#import <Foundation/Foundation.h>
#import <AYUserCenter/AYUserCenter.h>

#import <Foundation/Foundation.h>

@interface AYImpl_ios:NSObject
{
    baiyou::SDK_AIYOUYUN * cpp;
}
-(baiyou::SDK_AIYOUYUN *) getObj;
@end

@implementation AYImpl_ios

-(baiyou::SDK_AIYOUYUN *) getObj{
    return cpp;
}

-(void) setObj: (baiyou::SDK_AIYOUYUN *) value{
    cpp = value;
}

@end

namespace baiyou {
    
    
    int AYU_Callback(const char *retMsg, id caller){
        
        // 解析json数据
        NSString *strretmssage = [NSString stringWithCString:retMsg encoding:NSUTF8StringEncoding];
        
        NSData * data = [strretmssage dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary * o = [NSJSONSerialization JSONObjectWithData:data
                                                           options:NSJSONReadingAllowFragments
                                                             error:nil];
        // 根据callBackFun分析
        NSString * functionType = [o objectForKey:@"callBackFun"];
        
        // 解析retMsg
        NSDictionary * dict = [o objectForKey:@"retMsg"];
        
        
        // 使用weakSelf做点什么
        NSLog(@"functionType is %@ -- %@",functionType,dict);
        LoginResult result;
        
        if ([functionType isEqualToString:@"LoginSuccess"]){
            result.errorCode = 0;
            result.uid = std::string([[dict objectForKey:@"_id"] UTF8String]);
            result.name = std::string([[dict objectForKey:@"name"] UTF8String]);
            result.alias = std::string([[dict objectForKey:@"nickName"] UTF8String]);
            result.isGuest = [[dict objectForKey:@"anonymousFlag"] intValue] == 1;
        }else{
            result.errorCode = 1;
        }
        [((AYImpl_ios*)caller) getObj]->_loginCallback(result);
        return 0;
    }
    
    bool SDK_AIYOUYUN::init(){
        AYImpl_ios *impl = [AYImpl_ios alloc];
        [impl setObj:this];
        AYUC_initUserCenter(AYU_Callback, impl);
        return true;
    }
    
    void SDK_AIYOUYUN::Login(std::function<void (const LoginResult&)> callback){
        _loginCallback = callback;
        LoginGameCloud();
    }
    
    void SDK_AIYOUYUN::Logout(){
        
    }
    
    void SDK_AIYOUYUN::Pay(){
        
    }
    
    bool SDK_AIYOUYUN::handleURL(const char *){
        return false;
    }
    
    bool SDK_AIYOUYUN::openURL(const char *){
        return false;
    }
}
