//
//  SDK_GameCenter.m
//  cocos2d_libs
//
//  Created by gumin on 2017/5/4.
//
//

#import <Foundation/Foundation.h>
#include "SDK_GameCenter.h"
#import <GameKit/GameKit.h>

namespace baiyou {
    
    bool SDK_GameCenter::init(){
        return true;
    }
    
    void SDK_GameCenter::Login(std::function<void (const LoginResult&)> callback){
        
#if TARGET_OS_IOS
        GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
        if ([localPlayer isAuthenticated]){
            LoginResult result;
            result.errorCode = 0;
            result.uid = std::string([[localPlayer playerID] UTF8String]);
            result.name = std::string([[localPlayer displayName] UTF8String]);
            result.alias = std::string([[localPlayer alias] UTF8String]);
            result.channel = "GameCenter";
            callback(result);
        }else{
            localPlayer.authenticateHandler = ^(UIViewController *viewController, NSError *error) {
                LoginResult result;
                if (error){
                    result.errorCode = 1;
                }else{
                    result.errorCode = 0;
                    result.uid = std::string([[localPlayer playerID] UTF8String]);
                    result.name = std::string([[localPlayer displayName] UTF8String]);
                    result.alias = std::string([[localPlayer alias] UTF8String]);
                    result.channel = "GameCenter";
                }
                callback(result);
            };
        }
#endif
    }
    
    void SDK_GameCenter::Logout(){
        
    }
    
    void SDK_GameCenter::Pay(){
        
    }
}

