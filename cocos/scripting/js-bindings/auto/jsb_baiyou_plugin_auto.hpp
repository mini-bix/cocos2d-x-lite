#include "base/ccConfig.h"
#ifndef __baiyou_plugin_h__
#define __baiyou_plugin_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_baiyou_BaiyouPlugin_class;
extern JSObject *jsb_baiyou_BaiyouPlugin_prototype;

bool js_baiyou_plugin_BaiyouPlugin_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_baiyou_plugin_BaiyouPlugin_finalize(JSContext *cx, JSObject *obj);
void js_register_baiyou_plugin_BaiyouPlugin(JSContext *cx, JS::HandleObject global);
void register_all_baiyou_plugin(JSContext* cx, JS::HandleObject obj);
bool js_baiyou_plugin_BaiyouPlugin_getBundleVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_MessageBox(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_openURL(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_unScheduleAllLocalNotification(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_scheduleLocalNotification(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_getBundleId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_setIdleTimerDisabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_getProperty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_getUUID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_restart(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_getDeviceInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_GetAnySDKUserInitFinished(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_SetAnySDKUserInitFinished(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_baiyou_SDKUserInfo_class;
extern JSObject *jsb_baiyou_SDKUserInfo_prototype;

bool js_baiyou_plugin_SDKUserInfo_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_baiyou_plugin_SDKUserInfo_finalize(JSContext *cx, JSObject *obj);
void js_register_baiyou_plugin_SDKUserInfo(JSContext *cx, JS::HandleObject global);
void register_all_baiyou_plugin(JSContext* cx, JS::HandleObject obj);
bool js_baiyou_plugin_SDKUserInfo_setUserName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKUserInfo_getUserId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKUserInfo_getAlias(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKUserInfo_setUserId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKUserInfo_setAlias(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKUserInfo_getUserName(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_baiyou_SDKCenter_class;
extern JSObject *jsb_baiyou_SDKCenter_prototype;

bool js_baiyou_plugin_SDKCenter_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_baiyou_plugin_SDKCenter_finalize(JSContext *cx, JSObject *obj);
void js_register_baiyou_plugin_SDKCenter(JSContext *cx, JS::HandleObject global);
void register_all_baiyou_plugin(JSContext* cx, JS::HandleObject obj);
bool js_baiyou_plugin_SDKCenter_getUserInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKCenter_Pay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKCenter_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKCenter_Logout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKCenter_Login(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKCenter_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_SDKCenter_SDKCenter(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __baiyou_plugin_h__
