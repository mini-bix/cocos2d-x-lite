#include "scripting/js-bindings/auto/jsb_baiyou_plugin_auto.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "baiyou/BaiyouPlugin.h"
#include "baiyou/SDKCenter.h"
#include "baiyou/sdk/SDK_Common.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
JSClass  *jsb_baiyou_BaiyouPlugin_class;
JSObject *jsb_baiyou_BaiyouPlugin_prototype;

bool js_baiyou_plugin_BaiyouPlugin_getBundleVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_getBundleVersion : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getBundleVersion();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_getBundleVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_MessageBox(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_MessageBox : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_BaiyouPlugin_MessageBox : Error processing arguments");
        cobj->MessageBox(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_MessageBox : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_openURL(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_openURL : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_BaiyouPlugin_openURL : Error processing arguments");
        cobj->openURL(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_openURL : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_unScheduleAllLocalNotification(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_unScheduleAllLocalNotification : Invalid Native Object");
    if (argc == 0) {
        cobj->unScheduleAllLocalNotification();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_unScheduleAllLocalNotification : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_scheduleLocalNotification(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_scheduleLocalNotification : Invalid Native Object");
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        int arg2 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_BaiyouPlugin_scheduleLocalNotification : Error processing arguments");
        cobj->scheduleLocalNotification(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_scheduleLocalNotification : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_getBundleId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_getBundleId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getBundleId();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_getBundleId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_setIdleTimerDisabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_setIdleTimerDisabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_BaiyouPlugin_setIdleTimerDisabled : Error processing arguments");
        cobj->setIdleTimerDisabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_setIdleTimerDisabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_getProperty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_getProperty : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_BaiyouPlugin_getProperty : Error processing arguments");
        std::string ret = cobj->getProperty(arg0);
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_getProperty : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_getUUID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_getUUID : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getUUID();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_getUUID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_restart(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_restart : Invalid Native Object");
    if (argc == 0) {
        cobj->restart();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_restart : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_getDeviceInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::BaiyouPlugin* cobj = (baiyou::BaiyouPlugin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_BaiyouPlugin_getDeviceInfo : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getDeviceInfo();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_getDeviceInfo : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_baiyou_plugin_BaiyouPlugin_GetAnySDKUserInitFinished(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        bool ret = baiyou::BaiyouPlugin::GetAnySDKUserInitFinished();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_GetAnySDKUserInitFinished : wrong number of arguments");
    return false;
}

bool js_baiyou_plugin_BaiyouPlugin_SetAnySDKUserInitFinished(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_BaiyouPlugin_SetAnySDKUserInitFinished : Error processing arguments");
        baiyou::BaiyouPlugin::SetAnySDKUserInitFinished(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_SetAnySDKUserInitFinished : wrong number of arguments");
    return false;
}

bool js_baiyou_plugin_BaiyouPlugin_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        baiyou::BaiyouPlugin* ret = baiyou::BaiyouPlugin::getInstance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<baiyou::BaiyouPlugin>(cx, (baiyou::BaiyouPlugin*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_baiyou_plugin_BaiyouPlugin_getInstance : wrong number of arguments");
    return false;
}


void js_register_baiyou_plugin_BaiyouPlugin(JSContext *cx, JS::HandleObject global) {
    jsb_baiyou_BaiyouPlugin_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_baiyou_BaiyouPlugin_class->name = "BaiyouPlugin";
    jsb_baiyou_BaiyouPlugin_class->addProperty = JS_PropertyStub;
    jsb_baiyou_BaiyouPlugin_class->delProperty = JS_DeletePropertyStub;
    jsb_baiyou_BaiyouPlugin_class->getProperty = JS_PropertyStub;
    jsb_baiyou_BaiyouPlugin_class->setProperty = JS_StrictPropertyStub;
    jsb_baiyou_BaiyouPlugin_class->enumerate = JS_EnumerateStub;
    jsb_baiyou_BaiyouPlugin_class->resolve = JS_ResolveStub;
    jsb_baiyou_BaiyouPlugin_class->convert = JS_ConvertStub;
    jsb_baiyou_BaiyouPlugin_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBundleVersion", js_baiyou_plugin_BaiyouPlugin_getBundleVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("MessageBox", js_baiyou_plugin_BaiyouPlugin_MessageBox, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("openURL", js_baiyou_plugin_BaiyouPlugin_openURL, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unScheduleAllLocalNotification", js_baiyou_plugin_BaiyouPlugin_unScheduleAllLocalNotification, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scheduleLocalNotification", js_baiyou_plugin_BaiyouPlugin_scheduleLocalNotification, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBundleId", js_baiyou_plugin_BaiyouPlugin_getBundleId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_baiyou_plugin_BaiyouPlugin_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIdleTimerDisabled", js_baiyou_plugin_BaiyouPlugin_setIdleTimerDisabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getProperty", js_baiyou_plugin_BaiyouPlugin_getProperty, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUUID", js_baiyou_plugin_BaiyouPlugin_getUUID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("restart", js_baiyou_plugin_BaiyouPlugin_restart, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeviceInfo", js_baiyou_plugin_BaiyouPlugin_getDeviceInfo, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("GetAnySDKUserInitFinished", js_baiyou_plugin_BaiyouPlugin_GetAnySDKUserInitFinished, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("SetAnySDKUserInitFinished", js_baiyou_plugin_BaiyouPlugin_SetAnySDKUserInitFinished, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_baiyou_plugin_BaiyouPlugin_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_baiyou_BaiyouPlugin_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_baiyou_BaiyouPlugin_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_baiyou_BaiyouPlugin_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "BaiyouPlugin"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<baiyou::BaiyouPlugin>(cx, jsb_baiyou_BaiyouPlugin_class, proto, JS::NullPtr());
}

JSClass  *jsb_baiyou_SDKUserInfo_class;
JSObject *jsb_baiyou_SDKUserInfo_prototype;

bool js_baiyou_plugin_SDKUserInfo_setUserName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKUserInfo* cobj = (baiyou::SDKUserInfo *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKUserInfo_setUserName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_SDKUserInfo_setUserName : Error processing arguments");
        cobj->setUserName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKUserInfo_setUserName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_SDKUserInfo_getUserId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKUserInfo* cobj = (baiyou::SDKUserInfo *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKUserInfo_getUserId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getUserId();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKUserInfo_getUserId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_baiyou_plugin_SDKUserInfo_getAlias(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKUserInfo* cobj = (baiyou::SDKUserInfo *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKUserInfo_getAlias : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getAlias();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKUserInfo_getAlias : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_baiyou_plugin_SDKUserInfo_setUserId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKUserInfo* cobj = (baiyou::SDKUserInfo *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKUserInfo_setUserId : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_SDKUserInfo_setUserId : Error processing arguments");
        cobj->setUserId(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKUserInfo_setUserId : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_SDKUserInfo_setAlias(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKUserInfo* cobj = (baiyou::SDKUserInfo *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKUserInfo_setAlias : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_SDKUserInfo_setAlias : Error processing arguments");
        cobj->setAlias(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKUserInfo_setAlias : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_SDKUserInfo_getUserName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKUserInfo* cobj = (baiyou::SDKUserInfo *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKUserInfo_getUserName : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getUserName();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKUserInfo_getUserName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

void js_register_baiyou_plugin_SDKUserInfo(JSContext *cx, JS::HandleObject global) {
    jsb_baiyou_SDKUserInfo_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_baiyou_SDKUserInfo_class->name = "SDKUserInfo";
    jsb_baiyou_SDKUserInfo_class->addProperty = JS_PropertyStub;
    jsb_baiyou_SDKUserInfo_class->delProperty = JS_DeletePropertyStub;
    jsb_baiyou_SDKUserInfo_class->getProperty = JS_PropertyStub;
    jsb_baiyou_SDKUserInfo_class->setProperty = JS_StrictPropertyStub;
    jsb_baiyou_SDKUserInfo_class->enumerate = JS_EnumerateStub;
    jsb_baiyou_SDKUserInfo_class->resolve = JS_ResolveStub;
    jsb_baiyou_SDKUserInfo_class->convert = JS_ConvertStub;
    jsb_baiyou_SDKUserInfo_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setUserName", js_baiyou_plugin_SDKUserInfo_setUserName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUserId", js_baiyou_plugin_SDKUserInfo_getUserId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAlias", js_baiyou_plugin_SDKUserInfo_getAlias, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUserId", js_baiyou_plugin_SDKUserInfo_setUserId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAlias", js_baiyou_plugin_SDKUserInfo_setAlias, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUserName", js_baiyou_plugin_SDKUserInfo_getUserName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_baiyou_SDKUserInfo_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_baiyou_SDKUserInfo_class,
        dummy_constructor<baiyou::SDKUserInfo>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_baiyou_SDKUserInfo_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SDKUserInfo"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<baiyou::SDKUserInfo>(cx, jsb_baiyou_SDKUserInfo_class, proto, JS::NullPtr());
}

JSClass  *jsb_baiyou_SDKCenter_class;
JSObject *jsb_baiyou_SDKCenter_prototype;

bool js_baiyou_plugin_SDKCenter_getUserInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKCenter* cobj = (baiyou::SDKCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKCenter_getUserInfo : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_SDKCenter_getUserInfo : Error processing arguments");
        baiyou::SDKUserInfo* ret = cobj->getUserInfo(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<baiyou::SDKUserInfo>(cx, (baiyou::SDKUserInfo*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKCenter_getUserInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_SDKCenter_Pay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKCenter* cobj = (baiyou::SDKCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKCenter_Pay : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_SDKCenter_Pay : Error processing arguments");
        cobj->Pay(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKCenter_Pay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_SDKCenter_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKCenter* cobj = (baiyou::SDKCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKCenter_init : Invalid Native Object");
    if (argc == 1) {
        std::vector<int> arg0;
        ok &= jsval_to_std_vector_int(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_SDKCenter_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKCenter_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_SDKCenter_Logout(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKCenter* cobj = (baiyou::SDKCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKCenter_Logout : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_SDKCenter_Logout : Error processing arguments");
        cobj->Logout(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKCenter_Logout : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_SDKCenter_Login(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    baiyou::SDKCenter* cobj = (baiyou::SDKCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_baiyou_plugin_SDKCenter_Login : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_baiyou_plugin_SDKCenter_Login : Error processing arguments");
        cobj->Login(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_baiyou_plugin_SDKCenter_Login : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_baiyou_plugin_SDKCenter_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        baiyou::SDKCenter* ret = baiyou::SDKCenter::getInstance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<baiyou::SDKCenter>(cx, (baiyou::SDKCenter*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_baiyou_plugin_SDKCenter_getInstance : wrong number of arguments");
    return false;
}

bool js_baiyou_plugin_SDKCenter_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    baiyou::SDKCenter* cobj = new (std::nothrow) baiyou::SDKCenter();

    js_type_class_t *typeClass = js_get_type_from_native<baiyou::SDKCenter>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_create_weak_jsobject(cx, cobj, typeClass, "baiyou::SDKCenter"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_baiyou_SDKCenter_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SDKCenter)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    jsproxy = jsb_get_js_proxy(jsobj);
    if (jsproxy) {
        baiyou::SDKCenter *nobj = static_cast<baiyou::SDKCenter *>(jsproxy->ptr);
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        if (nobj) {
            jsb_remove_proxy(nproxy, jsproxy);
            JS::RootedValue flagValue(cx);
            JS_GetProperty(cx, jsobj, "__cppCreated", &flagValue);
            if (flagValue.isNullOrUndefined()){
                delete nobj;
            }
        }
        else
            jsb_remove_proxy(nullptr, jsproxy);
    }
}
void js_register_baiyou_plugin_SDKCenter(JSContext *cx, JS::HandleObject global) {
    jsb_baiyou_SDKCenter_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_baiyou_SDKCenter_class->name = "SDKCenter";
    jsb_baiyou_SDKCenter_class->addProperty = JS_PropertyStub;
    jsb_baiyou_SDKCenter_class->delProperty = JS_DeletePropertyStub;
    jsb_baiyou_SDKCenter_class->getProperty = JS_PropertyStub;
    jsb_baiyou_SDKCenter_class->setProperty = JS_StrictPropertyStub;
    jsb_baiyou_SDKCenter_class->enumerate = JS_EnumerateStub;
    jsb_baiyou_SDKCenter_class->resolve = JS_ResolveStub;
    jsb_baiyou_SDKCenter_class->convert = JS_ConvertStub;
    jsb_baiyou_SDKCenter_class->finalize = js_baiyou_SDKCenter_finalize;
    jsb_baiyou_SDKCenter_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getUserInfo", js_baiyou_plugin_SDKCenter_getUserInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Pay", js_baiyou_plugin_SDKCenter_Pay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_baiyou_plugin_SDKCenter_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Logout", js_baiyou_plugin_SDKCenter_Logout, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Login", js_baiyou_plugin_SDKCenter_Login, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_baiyou_plugin_SDKCenter_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_baiyou_SDKCenter_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_baiyou_SDKCenter_class,
        js_baiyou_plugin_SDKCenter_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_baiyou_SDKCenter_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SDKCenter"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<baiyou::SDKCenter>(cx, jsb_baiyou_SDKCenter_class, proto, JS::NullPtr());
}

void register_all_baiyou_plugin(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "baiyou", &ns);

    js_register_baiyou_plugin_BaiyouPlugin(cx, ns);
    js_register_baiyou_plugin_SDKUserInfo(cx, ns);
    js_register_baiyou_plugin_SDKCenter(cx, ns);
}

