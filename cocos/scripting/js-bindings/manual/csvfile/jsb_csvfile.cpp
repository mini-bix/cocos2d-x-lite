#include "jsb_csvfile.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "baiyou/csvfile/CsvFile.h"

JSClass  *jsb_baiyou_CsvFile_class;
JS::PersistentRootedObject *jsb_baiyou_CsvFile_prototype;

bool js_csvfile_CsvFile_split(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        std::vector<std::string> arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_vector_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_csvfile_CsvFile_split : Error processing arguments");
        baiyou::CsvFile::split(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_csvfile_CsvFile_split : wrong number of arguments");
    return false;
}

bool js_csvfile_CsvFile_getBody(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 2) {
        std::string arg0;
        std::vector<std::string> arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_vector_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_csvfile_CsvFile_getBody : Error processing arguments");
        baiyou::CsvFile::getBody(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_csvfile_CsvFile_getBody : wrong number of arguments");
    return false;
}

bool js_csvfile_CsvFile_parsingByFile(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_csvfile_CsvFile_parsingByFile : Error processing arguments");
        std::string ret;
        baiyou::CsvFile::parsingByFile(arg0,ret);
        if (ret == "") {
            args.rval().setUndefined();
            return true;
        }
        JS::RootedValue jsStr(cx);
        std_string_to_jsval(cx, ret,&jsStr);
        JS::RootedString jsout(cx, jsStr.toString());
        if(!JS_ParseJSON(cx,jsout,&jsStr)){
            arg0 +="js_parsing:JS_ParseJSON: Error processing arguments:"+ arg0 + "+" + ret;
            JS_ReportErrorUTF8(cx,"%s", arg0.c_str());
            args.rval().setUndefined();
            return true;
        }
        args.rval().set(jsStr);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_csvfile_CsvFile_parsingByFile : wrong number of arguments");
    return false;
}

bool js_csvfile_CsvFile_parsingCsvToJsonSting(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 2) {
        std::vector<std::string> arg0;
        std::string arg1;
        ok &= jsval_to_std_vector_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_csvfile_CsvFile_parsingCsvToJsonSting : Error processing arguments");
        baiyou::CsvFile::parsingCsvToJsonSting(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_csvfile_CsvFile_parsingCsvToJsonSting : wrong number of arguments");
    return false;
}

bool js_csvfile_CsvFile_getHead(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_csvfile_CsvFile_getHead : Error processing arguments");
        
        std::vector<std::string> ret = baiyou::CsvFile::getHead(arg0);
        JS::RootedValue jsret(cx, JS::NullHandleValue);
        ok &= std_vector_string_to_jsval(cx, ret, &jsret);
        JSB_PRECONDITION2(ok, cx, false, "js_csvfile_CsvFile_getHead : error parsing return value");
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_csvfile_CsvFile_getHead : wrong number of arguments");
    return false;
}


void js_register_csvfile_CsvFile(JSContext *cx, JS::HandleObject global) {
    static const JSClassOps baiyou_CsvFile_classOps = {
        nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr,
        nullptr,
        nullptr, nullptr, nullptr, nullptr
    };
    static JSClass baiyou_CsvFile_class = {
        "CsvFile",
        JSCLASS_HAS_PRIVATE,
        &baiyou_CsvFile_classOps
    };
    jsb_baiyou_CsvFile_class = &baiyou_CsvFile_class;
    
    static JSFunctionSpec st_funcs[] = {
        JS_FN("split", js_csvfile_CsvFile_split, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBody", js_csvfile_CsvFile_getBody, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("parsingByFile", js_csvfile_CsvFile_parsingByFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("parsingCsvToJsonSting", js_csvfile_CsvFile_parsingCsvToJsonSting, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHead", js_csvfile_CsvFile_getHead, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    JS::RootedObject parent_proto(cx, nullptr);
    JS::RootedObject proto(cx, JS_InitClass(
                                            cx, global,
                                            parent_proto,
                                            jsb_baiyou_CsvFile_class,
                                            empty_constructor, 0,
                                            nullptr,
                                            nullptr,
                                            nullptr,
                                            st_funcs));
    
    // add the proto and JSClass to the type->js info hash table
    js_type_class_t *typeClass = jsb_register_class<baiyou::CsvFile>(cx, jsb_baiyou_CsvFile_class, proto);
    jsb_baiyou_CsvFile_prototype = typeClass->proto;
    JS::RootedValue className(cx);
    std_string_to_jsval(cx, "CsvFile", &className);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}

void register_all_csvfile(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "baiyou", &ns);
    
    js_register_csvfile_CsvFile(cx, ns);
}

