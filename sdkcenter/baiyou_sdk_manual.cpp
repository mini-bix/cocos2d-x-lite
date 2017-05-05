//
//  baiyou_specifics.cpp
//  cocos2d_js_bindings
//
//  Created by gumin on 2017/5/4.
//
//

#include "baiyou_sdk_manual.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/js_manual_conversions.h"
#include "mozilla/Maybe.h"
#include "SDKCenter.h"
#include "jsb_baiyou_sdk_auto.hpp"

using namespace baiyou;

class BaiyouJSUserResultListener : public UserResultListener
{
public:
    BaiyouJSUserResultListener()
    {
    }
    ~BaiyouJSUserResultListener()
    {
        CCLOG("on user action result ~listener");
        _jsCallback.destroyIfConstructed();
        _jsThisObj.destroyIfConstructed();
        _ctxObj.destroyIfConstructed();
    }
    
    void onUserResult(int pluginId,int code, const char* msg)
    {
        CCLOG("on user action result: %d, msg: %s.", code, msg);
        JS::RootedObject thisObj(_ctx, _jsThisObj.ref().get().toObjectOrNull());
        JSAutoCompartment ac(_ctx, _ctxObj.ref());
        JS::RootedValue retval(_ctx);
        if (!_jsCallback.ref().get().isNullOrUndefined())
        {
            JS::AutoValueVector valArr(_ctx);
            valArr.append( INT_TO_JSVAL(pluginId) );
            valArr.append( INT_TO_JSVAL(code) );
            valArr.append( std_string_to_jsval(_ctx, msg) );
            
            JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(3, valArr.begin());
            JS_CallFunctionValue(_ctx, thisObj, _jsCallback.ref(), args, &retval);
        }
    }
    
    void setJSCallbackThis(JSContext *cx, JS::HandleValue jsThisObj)
    {
        _jsThisObj.construct(cx, jsThisObj);
    }
    void setJSCallbackFunc(JSContext *cx, JS::HandleValue func) {
        _jsCallback.construct(cx, func);
    }
    void setJSCallbackCtx(JSContext *ctx, JS::HandleObject ctxObj) {
        _ctx = ctx;
        _ctxObj.construct(ctx, ctxObj);
    }
private:
    mozilla::Maybe<JS::PersistentRootedValue> _jsCallback;
    mozilla::Maybe<JS::PersistentRootedValue> _jsThisObj;
    mozilla::Maybe<JS::PersistentRootedObject> _ctxObj;
    JSContext* _ctx;
};


bool jsb_baiyou_SDKCenter_setUserResultListener(JSContext *cx, uint32_t argc, jsval *vp){
    CCLOG("in SDKCenter_setResultListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SDKCenter *cobj = (SDKCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
        JS_ReportError(cx, "jsb_baiyou_SDKCenter_setResultListener : wrong number of arguments: %d, was expecting %d", argc, 0);
        return false;
    }
    BaiyouJSUserResultListener* listener = new BaiyouJSUserResultListener();
    listener->setJSCallbackFunc( cx, args.get(0) );
    listener->setJSCallbackThis( cx, args.get(1) );
    listener->setJSCallbackCtx( cx, obj );
    cobj->setUserResultListener(listener);
    return true;
}

void register_all_baiyou_sdk_manual(JSContext* cx, JS::HandleObject obj) {
    JS::RootedObject ns(cx);
    JS::RootedObject proto(cx);
    get_or_create_js_obj(cx, obj, "baiyou", &ns);
    
    proto.set(jsb_baiyou_SDKCenter_prototype);
    JS_DefineFunction(cx, proto, "setUserResultListener", jsb_baiyou_SDKCenter_setUserResultListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
