#include "base/ccConfig.h"
#ifndef __baiyou_sdk_h__
#define __baiyou_sdk_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_baiyou_SDKUserInfo_class;
extern JSObject *jsb_baiyou_SDKUserInfo_prototype;

bool js_baiyou_sdk_SDKUserInfo_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_baiyou_sdk_SDKUserInfo_finalize(JSContext *cx, JSObject *obj);
void js_register_baiyou_sdk_SDKUserInfo(JSContext *cx, JS::HandleObject global);
void register_all_baiyou_sdk(JSContext* cx, JS::HandleObject obj);
bool js_baiyou_sdk_SDKUserInfo_setUserName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKUserInfo_getUserId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKUserInfo_getAlias(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKUserInfo_setUserId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKUserInfo_setAlias(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKUserInfo_getUserName(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_baiyou_SDKCenter_class;
extern JSObject *jsb_baiyou_SDKCenter_prototype;

bool js_baiyou_sdk_SDKCenter_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_baiyou_sdk_SDKCenter_finalize(JSContext *cx, JSObject *obj);
void js_register_baiyou_sdk_SDKCenter(JSContext *cx, JS::HandleObject global);
void register_all_baiyou_sdk(JSContext* cx, JS::HandleObject obj);
bool js_baiyou_sdk_SDKCenter_getUserInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKCenter_Pay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKCenter_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKCenter_Logout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKCenter_Login(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKCenter_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_sdk_SDKCenter_SDKCenter(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __baiyou_sdk_h__
