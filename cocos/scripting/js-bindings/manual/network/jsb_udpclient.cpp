//
//  jsb_udpclient.cpp
//  cocos2d_js_bindings
//
//  Created by gumin on 2017/5/25.
//
//

#include "jsb_udpclient.h"

#include "base/ccUTF8.h"
#include "base/CCDirector.h"
#include "network/UdpClient.h"
#include "platform/CCPlatformMacros.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/spidermonkey_specifics.h"
#include "scripting/js-bindings/auto/jsb_cocos2dx_network_auto.hpp"

using namespace cocos2d::network;


class JSB_UdpClientDelegate : public UdpClient::Delegate
{
public:
    
    JSB_UdpClientDelegate()
    {
    }
    
    ~JSB_UdpClientDelegate()
    {
    }
    
    virtual void onOpen(UdpClient* ws)
    {
        js_proxy_t * p = jsb_get_native_proxy(ws);
        if (!p) return;
        
        if (cocos2d::Director::getInstance() == nullptr || cocos2d::ScriptEngineManager::getInstance() == nullptr)
            return;
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedObject jsobj(cx, JS_NewPlainObject(cx));
        JS::RootedValue vp(cx);
        c_string_to_jsval(cx, "open",&vp);
        JS_SetProperty(cx, jsobj, "type", vp);
        
        JS::RootedValue jsobjVal(cx, JS::ObjectOrNullValue(jsobj));
        JS::HandleValueArray args(jsobjVal);
        JS::RootedValue owner(cx, JS::ObjectOrNullValue(_JSDelegate));
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(owner, "onopen", args);
    }
    
    virtual void onMessage(UdpClient* ws, const UdpClient::Data& data)
    {
        js_proxy_t * p = jsb_get_native_proxy(ws);
        if (p == nullptr) return;
        
        if (cocos2d::Director::getInstance() == nullptr || cocos2d::ScriptEngineManager::getInstance() == nullptr)
            return;
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedObject jsobj(cx, JS_NewPlainObject(cx));
        JS::RootedValue vp(cx);
        c_string_to_jsval(cx, "message", &vp);
        JS_SetProperty(cx, jsobj, "type", vp);
        
        JS::RootedValue arg(cx, JS::ObjectOrNullValue(jsobj));
        bool flag;
        if (data.isBinary)
        {// data is binary
            JS::RootedObject buffer(cx, JS_NewArrayBuffer(cx, static_cast<uint32_t>(data.len)));
            if (data.len > 0)
            {
                uint8_t* bufdata = JS_GetArrayBufferData(buffer, &flag, JS::AutoCheckCannotGC());
                memcpy((void*)bufdata, (void*)data.bytes, data.len);
            }
            JS::RootedValue dataVal(cx, JS::ObjectOrNullValue(buffer));
            JS_SetProperty(cx, jsobj, "data", dataVal);
        }else{
            JS::RootedValue dataVal(cx);
            if (strlen(data.bytes) == 0 && data.len > 0)
            {// String with 0x00 prefix
                dataVal = JS::StringValue(JS_NewStringCopyN(cx, data.bytes, data.len));
            }
            else
            {// Normal string
                c_string_to_jsval(cx, data.bytes, &dataVal);
            }
            if (dataVal.isNullOrUndefined())
            {
                return;
            }
            JS_SetProperty(cx, jsobj, "data", dataVal);
        }
        JS::RootedValue delegate(cx, JS::ObjectOrNullValue(_JSDelegate));
        JS::HandleValueArray args(arg);
        ScriptingCore::getInstance()->executeFunctionWithOwner(delegate, "onmessage", args);
    }
    
    virtual void onClose(UdpClient* ws)
    {
        js_proxy_t * p = jsb_get_native_proxy(ws);
        if (!p) return;
        
        if (cocos2d::Director::getInstance() != nullptr && cocos2d::Director::getInstance()->getRunningScene() && cocos2d::ScriptEngineManager::getInstance() != nullptr)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::RootedObject jsobj(cx, JS_NewPlainObject(cx));
            JS::RootedValue vp(cx);
            c_string_to_jsval(cx, "close", &vp);
            JS_SetProperty(cx, jsobj, "type", vp);
            
            JS::RootedValue delegate(cx, JS::ObjectOrNullValue(_JSDelegate));
            JS::RootedValue arg(cx, JS::ObjectOrNullValue(jsobj));
            JS::HandleValueArray args(arg);
            ScriptingCore::getInstance()->executeFunctionWithOwner(delegate, "onclose", args);
            
#if not CC_ENABLE_GC_FOR_NATIVE_OBJECTS
            auto copy = &p->obj;
            JS::RemoveObjectRoot(cx, copy);
#endif
            jsb_remove_proxy(p);
        }
        
        // Delete WebSocket instance
        CC_SAFE_DELETE(ws);
        // Delete self at last while websocket was closed.
        delete this;
    }
    
    virtual void onError(UdpClient* ws, const UdpClient::ErrorCode& error)
    {
        js_proxy_t * p = jsb_get_native_proxy(ws);
        if (!p) return;
        
        if (cocos2d::Director::getInstance() == nullptr || cocos2d::ScriptEngineManager::getInstance() == nullptr)
            return;
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedObject jsobj(cx, JS_NewPlainObject(cx));
        JS::RootedValue vp(cx);
        c_string_to_jsval(cx, "error", &vp);
        JS_SetProperty(cx, jsobj, "type", vp);
        
        JS::RootedValue delegate(cx, JS::ObjectOrNullValue(_JSDelegate));
        JS::RootedValue arg(cx, JS::ObjectOrNullValue(jsobj));
        JS::HandleValueArray args(arg);
        ScriptingCore::getInstance()->executeFunctionWithOwner(delegate, "onerror", args);
    }
    
    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
private:
    JS::PersistentRootedObject _JSDelegate;
};

bool js_cocos2dx_extension_UdpClient_Write(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs argv = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, argv.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    UdpClient* cobj = (UdpClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if(argc == 1)
    {
        if (argv[0].isString())
        {
            ssize_t len = JS_GetStringLength(argv[0].toString());
            std::string data;
            jsval_to_std_string(cx, argv[0], &data);
            
            if (data.empty() && len > 0)
            {
                CCLOGWARN("Text message to send is empty, but its length is greater than 0!");
                //FIXME: Note that this text message contains '0x00' prefix, so its length calcuted by strlen is 0.
                // we need to fix that if there is '0x00' in text message,
                // since javascript language could support '0x00' inserted at the beginning or the middle of text message
            }
            
            cobj->Write(data.c_str(),data.size());
        }
        else if (argv[0].isObject())
        {
            uint8_t *bufdata = NULL;
            uint32_t len = 0;
            
            JS::RootedObject jsobj(cx, argv[0].toObjectOrNull());
            bool flag;
            if (JS_IsArrayBufferObject(jsobj))
            {
                bufdata = JS_GetArrayBufferData(jsobj, &flag, JS::AutoCheckCannotGC());
                len = JS_GetArrayBufferByteLength(jsobj);
            }
            else if (JS_IsArrayBufferViewObject(jsobj))
            {
                bufdata = (uint8_t*)JS_GetArrayBufferViewData(jsobj, &flag, JS::AutoCheckCannotGC());
                len = JS_GetArrayBufferViewByteLength(jsobj);
            }
            
            cobj->Write(bufdata, len);
        }
        else
        {
            JS_ReportErrorUTF8(cx, "data type to be sent is unsupported.");
            return false;
        }
        
        argv.rval().setUndefined();
        
        return true;
    }
    JS_ReportErrorUTF8(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return true;
}

JSClass  *jsb_cocos2d_network_UdpClient_class;
JSObject *jsb_cocos2d_network_UdpClient_prototype;

bool js_cocos2dx_network_UdpClient_Connect(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    cocos2d::network::UdpClient* cobj = (cocos2d::network::UdpClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_network_UdpClient_Connect : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_network_UdpClient_Connect : Error processing arguments");
        int ret = cobj->Connect(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_network_UdpClient_Connect : error parsing return value");
        args.rval().set(jsret);
        return true;
    }
    
    JS_ReportErrorUTF8(cx, "js_cocos2dx_network_UdpClient_Connect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_cocos2dx_network_UdpClient_Close(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    cocos2d::network::UdpClient* cobj = (cocos2d::network::UdpClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_network_UdpClient_Close : Invalid Native Object");
    if (argc == 0) {
        cobj->Close();
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportErrorUTF8(cx, "js_cocos2dx_network_UdpClient_Close : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_network_UdpClient_constructor(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::network::UdpClient* cobj = new (std::nothrow) cocos2d::network::UdpClient();
    
    // create the js object and link the native object with the javascript object
    JS::RootedObject jsobj(cx);
    JS::RootedObject proto(cx, jsb_cocos2d_network_UdpClient_prototype);
    jsb_create_weak_jsobject(cx, cobj, jsb_cocos2d_network_UdpClient_class, proto, &jsobj, "cocos2d::network::UdpClient");
    JS_SetPrivate(jsobj.get(), cobj);
    JS::RootedValue retVal(cx, JS::ObjectOrNullValue(jsobj));
    args.rval().set(retVal);
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
    {
        JS::HandleValueArray argsv(args);
        ScriptingCore::getInstance()->executeFunctionWithOwner(retVal, "_ctor", argsv);
    }
    return true;
}

void js_cocos2d_network_UdpClient_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (UdpClient)", obj);
    cocos2d::network::UdpClient *nobj = static_cast<cocos2d::network::UdpClient *>(JS_GetPrivate(obj));
    if (nobj) {
        CC_SAFE_DELETE(nobj);
    }
}

bool js_cocos2dx_network_UdpClient_setZipEnabled(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    cocos2d::network::UdpClient* cobj = (cocos2d::network::UdpClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_network_UdpClient_setZipEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        ok &= jsval_to_bool(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_network_UdpClient_setZipEnabled : Error processing arguments");
        cobj->setZipEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportErrorUTF8(cx, "js_cocos2dx_network_UdpClient_setZipEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_cocos2dx_network_UdpClient_Write(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs argv = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, argv.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    UdpClient* cobj = (UdpClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if(argc == 1)
    {
        if (argv[0].isString())
        {
            ssize_t len = JS_GetStringLength(argv[0].toString());
            std::string data;
            jsval_to_std_string(cx, argv[0], &data);
            
            if (data.empty() && len > 0)
            {
                CCLOGWARN("Text message to send is empty, but its length is greater than 0!");
                //FIXME: Note that this text message contains '0x00' prefix, so its length calcuted by strlen is 0.
                // we need to fix that if there is '0x00' in text message,
                // since javascript language could support '0x00' inserted at the beginning or the middle of text message
            }
            
            cobj->Write(data.c_str(),data.length());
        }
        else if (argv[0].isObject())
        {
            uint8_t *bufdata = NULL;
            uint32_t len = 0;
            
            JS::RootedObject jsobj(cx, argv[0].toObjectOrNull());
            bool flag;
            if (JS_IsArrayBufferObject(jsobj))
            {
                bufdata = JS_GetArrayBufferData(jsobj, &flag, JS::AutoCheckCannotGC());
                len = JS_GetArrayBufferByteLength(jsobj);
            }
            else if (JS_IsArrayBufferViewObject(jsobj))
            {
                bufdata = (uint8_t*)JS_GetArrayBufferViewData(jsobj, &flag, JS::AutoCheckCannotGC());
                len = JS_GetArrayBufferViewByteLength(jsobj);
            }
            
            cobj->Write(bufdata, len);
        }
        else
        {
            JS_ReportErrorUTF8(cx, "data type to be sent is unsupported.");
            return false;
        }
        
        argv.rval().setUndefined();
        
        return true;
    }
    JS_ReportErrorUTF8(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return true;
}

void register_jsb_udpclient(JSContext *cx, JS::HandleObject global) {
    static const JSClassOps udpclient_classOps = {
        nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr,
        js_cocos2d_network_UdpClient_finalize,
        nullptr, nullptr, nullptr, nullptr
    };
    
    static JSClass udpclient_class = {
        "UdpClient",
        JSCLASS_HAS_PRIVATE | JSCLASS_FOREGROUND_FINALIZE,
        &udpclient_classOps
    };
    jsb_cocos2d_network_UdpClient_class = &udpclient_class;
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    
    static JSFunctionSpec funcs[] = {
        JS_FN("Connect",js_cocos2dx_network_UdpClient_Connect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Close",js_cocos2dx_network_UdpClient_Close, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Write",js_cocos2dx_network_UdpClient_Write, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZipEnabled",js_cocos2dx_network_UdpClient_setZipEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    JS::RootedObject parent_proto(cx, nullptr);
    jsb_cocos2d_network_UdpClient_prototype = JS_InitClass(
                                                   cx, global,
                                                   parent_proto,
                                                   jsb_cocos2d_network_UdpClient_class,
                                                   js_cocos2dx_network_UdpClient_constructor, 0, // constructor
                                                   properties,
                                                   funcs,
                                                   nullptr, // no static properties
                                                   nullptr);
    
    JS::RootedValue jsclassVal(cx);
    bool ok = anonEvaluate(cx, global, "(function () { return UdpClient; })()", &jsclassVal);
    if (ok)
    {
        JS::RootedObject jsclassObj(cx, jsclassVal.toObjectOrNull());
    }
}
