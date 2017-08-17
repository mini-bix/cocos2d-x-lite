//
//  KeyChainStore.h
//  cocos2d_libs
//
//  Created by gumin on 2016/12/16.
//
//

#ifndef KeyChainStore_h
#define KeyChainStore_h

#import <Foundation/Foundation.h>

@interface KeyChainStore : NSObject

+ (void)save:(NSString *)service data:(id)data;
+ (id)load:(NSString *)service;
+ (void)deleteKeyData:(NSString *)service;

@end


#endif /* KeyChainStore_h */
