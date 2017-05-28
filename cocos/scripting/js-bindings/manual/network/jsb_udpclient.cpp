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
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        _JSDelegate.construct(cx);
    }
    
    ~JSB_UdpClientDelegate()
    {
        _JSDelegate.destroyIfConstructed();
    }
    
    virtual void onOpen(UdpClient* ws)
    {
        js_proxy_t * p = jsb_get_native_proxy(ws);
        if (!p) return;
        
        if (cocos2d::Director::getInstance() == nullptr || cocos2d::ScriptEngineManager::getInstance() == nullptr)
            return;
        
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
        JS::RootedValue vp(cx);
        vp = c_string_to_jsval(cx, "open");
        JS_SetProperty(cx, jsobj, "type", vp);
        
        jsval args = OBJECT_TO_JSVAL(jsobj);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate.ref()), "onopen", 1, &args);
    }
    
    virtual void onMessage(UdpClient* ws, const UdpClient::Data& data)
    {
        js_proxy_t * p = jsb_get_native_proxy(ws);
        if (p == nullptr) return;
        
        if (cocos2d::Director::getInstance() == nullptr || cocos2d::ScriptEngineManager::getInstance() == nullptr)
            return;
        
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
        JS::RootedValue vp(cx);
        vp = c_string_to_jsval(cx, "message");
        JS_SetProperty(cx, jsobj, "type", vp);
        
        JS::RootedValue args(cx, OBJECT_TO_JSVAL(jsobj));
        if (data.isBinary)
        {// data is binary
            JS::RootedObject buffer(cx, JS_NewArrayBuffer(cx, static_cast<uint32_t>(data.len)));
            if (data.len > 0)
            {
                uint8_t* bufdata = JS_GetArrayBufferData(buffer);
                memcpy((void*)bufdata, (void*)data.bytes, data.len);
            }
            JS::RootedValue dataVal(cx);
            dataVal = OBJECT_TO_JSVAL(buffer);
            JS_SetProperty(cx, jsobj, "data", dataVal);
        }else{
            JS::RootedValue dataVal(cx);
            if (strlen(data.bytes) == 0 && data.len > 0)
            {// String with 0x00 prefix
                dataVal = STRING_TO_JSVAL(JS_NewStringCopyN(cx, data.bytes, data.len));
            }
            else
            {// Normal string
                dataVal = c_string_to_jsval(cx, data.bytes,data.len);
            }
            if (dataVal.isNullOrUndefined())
            {
                return;
            }
            JS_SetProperty(cx, jsobj, "data", dataVal);
        }
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate.ref()), "onmessage", 1, args.address());
    }
    
    virtual void onClose(UdpClient* ws)
    {
        js_proxy_t * p = jsb_get_native_proxy(ws);
        if (!p) return;
        
        if (cocos2d::Director::getInstance() != nullptr && cocos2d::Director::getInstance()->getRunningScene() && cocos2d::ScriptEngineManager::getInstance() != nullptr)
        {
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
            JS::RootedValue vp(cx);
            vp = c_string_to_jsval(cx, "close");
            JS_SetProperty(cx, jsobj, "type", vp);
            
            JS::RootedValue args(cx, OBJECT_TO_JSVAL(jsobj));
            ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate.ref()), "onclose", 1, args.address());
            
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
        
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
        JS::RootedValue vp(cx);
        vp = c_string_to_jsval(cx, "error");
        JS_SetProperty(cx, jsobj, "type", vp);
        
        JS::RootedValue args(cx, OBJECT_TO_JSVAL(jsobj));
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate.ref()), "onerror", 1, args.address());
    }
    
    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate.ref() = pJSDelegate;
    }
private:
    mozilla::Maybe<JS::RootedObject> _JSDelegate;
};

bool js_cocos2dx_extension_UdpClient_Write(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs argv = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, argv.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
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
            
            cobj->Write(data.c_str(),len);
        }
        else if (argv[0].isObject())
        {
            uint8_t *bufdata = NULL;
            uint32_t len = 0;
            
            JS::RootedObject jsobj(cx, argv[0].toObjectOrNull());
            if (JS_IsArrayBufferObject(jsobj))
            {
                bufdata = JS_GetArrayBufferData(jsobj);
                len = JS_GetArrayBufferByteLength(jsobj);
            }
            else if (JS_IsArrayBufferViewObject(jsobj))
            {
                bufdata = (uint8_t*)JS_GetArrayBufferViewData(jsobj);
                len = JS_GetArrayBufferViewByteLength(jsobj);
            }
            
            cobj->Write(bufdata, len);
        }
        else
        {
            JS_ReportError(cx, "data type to be sent is unsupported.");
            return false;
        }
        
        argv.rval().setUndefined();
        
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return true;
}

JSClass  *jsb_cocos2d_network_UdpClient_class;
JSObject *jsb_cocos2d_network_UdpClient_prototype;

bool js_cocos2dx_network_UdpClient_Connect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::network::UdpClient* cobj = (cocos2d::network::UdpClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_network_UdpClient_Connect : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_network_UdpClient_Connect : Error processing arguments");
        int ret = cobj->Connect(arg0);
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_network_UdpClient_Connect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_network_UdpClient_Close(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::network::UdpClient* cobj = (cocos2d::network::UdpClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_network_UdpClient_Close : Invalid Native Object");
    if (argc == 0) {
        cobj->Close();
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_network_UdpClient_Close : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_network_UdpClient_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::network::UdpClient* cobj = new (std::nothrow) cocos2d::network::UdpClient();
    
    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::network::UdpClient>(cobj);
    
    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_create_weak_jsobject(cx, cobj, typeClass, "cocos2d::network::UdpClient"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    
    JSB_UdpClientDelegate* delegate = new (std::nothrow) JSB_UdpClientDelegate();
    delegate->setJSDelegate(jsobj);
    cobj->setDelegate(delegate);
    
    return true;
}


void js_cocos2d_network_UdpClient_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (UdpClient)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    jsproxy = jsb_get_js_proxy(jsobj);
    if (jsproxy) {
        cocos2d::network::UdpClient *nobj = static_cast<cocos2d::network::UdpClient *>(jsproxy->ptr);
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

bool js_cocos2dx_network_UdpClient_setZipEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::network::UdpClient* cobj = (cocos2d::network::UdpClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_network_UdpClient_setZipEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_network_UdpClient_setZipEnabled : Error processing arguments");
        cobj->setZipEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_network_UdpClient_setZipEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

void register_jsb_udpclient(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_network_UdpClient_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_network_UdpClient_class->name = "UdpClient";
    jsb_cocos2d_network_UdpClient_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_network_UdpClient_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_network_UdpClient_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_network_UdpClient_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_network_UdpClient_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_network_UdpClient_class->resolve = JS_ResolveStub;
    jsb_cocos2d_network_UdpClient_class->convert = JS_ConvertStub;
    jsb_cocos2d_network_UdpClient_class->finalize = js_cocos2d_network_UdpClient_finalize;
    jsb_cocos2d_network_UdpClient_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    
    static JSFunctionSpec funcs[] = {
        JS_FN("Connect", js_cocos2dx_network_UdpClient_Connect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Close", js_cocos2dx_network_UdpClient_Close, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Write", js_cocos2dx_extension_UdpClient_Write, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZipEnabled", js_cocos2dx_network_UdpClient_setZipEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    JSFunctionSpec *st_funcs = NULL;
    
    jsb_cocos2d_network_UdpClient_prototype = JS_InitClass(
                                                           cx, global,
                                                           JS::NullPtr(),
                                                           jsb_cocos2d_network_UdpClient_class,
                                                           js_cocos2dx_network_UdpClient_constructor, 0, // constructor
                                                           properties,
                                                           funcs,
                                                           NULL, // no static properties
                                                           st_funcs);
    
    JS::RootedObject proto(cx, jsb_cocos2d_network_UdpClient_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "UdpClient"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::network::UdpClient>(cx, jsb_cocos2d_network_UdpClient_class, proto, JS::NullPtr());
}
