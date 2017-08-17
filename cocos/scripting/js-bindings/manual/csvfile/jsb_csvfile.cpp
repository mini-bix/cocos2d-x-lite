#include "scripting/js-bindings/manual/csvfile/jsb_csvfile.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "extensions/baiyou/csvfile/CsvFile.h"
#include <sstream>
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
JSClass  *jsb_baiyou_CsvFile_class;
JSObject *jsb_baiyou_CsvFile_prototype;
//bool js_isNum(const std::string& str)
//{
//    std::stringstream sin(str);
//    double d;
//    char c;
//    if(!(sin >> d))
//        return false;
//    if (sin >> c)
//        return false;
//    return true;
//}
//jsval js_parsing(JSContext *cx,std::vector<std::string> fileList)
//{
//    if (fileList.empty()) {
//        return JSVAL_NULL;
//    }
//    std::vector<std::string>::iterator iter = fileList.begin();
//    std::string headStr = (*iter);
//    iter++;
//    std::vector<std::string> head = baiyou::CsvFile::getHead(headStr);
//    
//    if (head.empty()) {
//        return JSVAL_NULL;
//    }
//    std::vector<std::string> body;
//    body.resize(head.size());
//    JS::RootedObject jsonObj(cx,JS_NewArrayObject(cx,fileList.size() - 2 ));
//    int index = 0;
//    while (iter != fileList.end()) {
//        body.clear();
//        baiyou::CsvFile::getBody((*iter), body);
//        if (body.empty() || body.size() != head.size()) {
//            iter++;
//            continue;
//        }
//        std::vector<std::string>::iterator headIter = head.begin();
//        std::vector<std::string>::iterator bodyIter = body.begin();
//        JS::RootedObject arrElement(cx,JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
//        for (;headIter != head.end() && bodyIter != body.end();headIter++,bodyIter++) {
//            std::string bodyStr = (*bodyIter);
//            JS::RootedValue objElement(cx);
//            if (js_isNum(bodyStr)){
//                double num = atof(bodyStr.c_str());
//                objElement = DOUBLE_TO_JSVAL(num);
//            }else{
//                objElement = std_string_to_jsval(cx,bodyStr);
//                if(bodyStr != "" && (bodyStr[0] == '[' || bodyStr[0] == '{')){
//                    JS::RootedString jsout(cx, objElement.toString());
//                    if(!JS_ParseJSON(cx,jsout,&objElement)){
//                        JS_ReportError(cx,"js_parsing:JS_ParseJSON: Error processing arguments");
//                        objElement = JSVAL_NULL;
//                    }
//                }
//            }
//            if (!JS_DefineProperty(cx, arrElement, (*headIter).c_str(), objElement, JSPROP_ENUMERATE | JSPROP_PERMANENT)){
//                JS_ReportError(cx,"js_parsing:JS_DefineProperty: Error processing arguments");
//                continue;
//            }
//        }
//        
//        if (!JS_SetElement(cx, jsonObj, index, arrElement)) {
//            JS_ReportError(cx,"js_parsing : Error processing arguments");
//            continue;
//        }
//        index++;
//        iter++;
//    }
//    return OBJECT_TO_JSVAL(jsonObj);
//}

bool js_csvfile_CsvFile_parsingByFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_csvfile_CsvFile_parsingByFile : Error processing arguments");
        std::string ret = "";
        baiyou::CsvFile::parsingByFile(arg0,ret);
        if (ret == "") {
            args.rval().setUndefined();
            return true;
        }
        JS::RootedValue objElement(cx);
        jsval jsStr = std_string_to_jsval(cx, ret);
        JS::RootedString jsout(cx, jsStr.toString());
        if(!JS_ParseJSON(cx,jsout,&objElement)){
            arg0 +="js_parsing:JS_ParseJSON: Error processing arguments:"+ arg0 + "+" + ret;
            JS_ReportError(cx,arg0.c_str());
            objElement = JSVAL_NULL;
        }
        args.rval().set(objElement);
        return true;
    }
    JS_ReportError(cx, "js_csvfile_CsvFile_parsingByFile : wrong number of arguments");
    return false;
}

void js_register_csvfile_CsvFile(JSContext *cx, JS::HandleObject global) {
    jsb_baiyou_CsvFile_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_baiyou_CsvFile_class->name = "CsvFile";
    jsb_baiyou_CsvFile_class->addProperty = JS_PropertyStub;
    jsb_baiyou_CsvFile_class->delProperty = JS_DeletePropertyStub;
    jsb_baiyou_CsvFile_class->getProperty = JS_PropertyStub;
    jsb_baiyou_CsvFile_class->setProperty = JS_StrictPropertyStub;
    jsb_baiyou_CsvFile_class->enumerate = JS_EnumerateStub;
    jsb_baiyou_CsvFile_class->resolve = JS_ResolveStub;
    jsb_baiyou_CsvFile_class->convert = JS_ConvertStub;
    jsb_baiyou_CsvFile_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("parsingByFile", js_csvfile_CsvFile_parsingByFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_baiyou_CsvFile_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_baiyou_CsvFile_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_baiyou_CsvFile_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "CsvFile"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<baiyou::CsvFile>(cx, jsb_baiyou_CsvFile_class, proto, JS::NullPtr());
}

void register_all_csvfile(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "baiyou", &ns);

    js_register_csvfile_CsvFile(cx, ns);
}

