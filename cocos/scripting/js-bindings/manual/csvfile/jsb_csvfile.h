#include "base/ccConfig.h"
#ifndef __csvfile_h__
#define __csvfile_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_baiyou_CsvFile_class;
extern JS::PersistentRootedObject *jsb_baiyou_CsvFile_prototype;

bool js_csvfile_CsvFile_constructor(JSContext *cx, uint32_t argc, JS::Value *vp);
void js_csvfile_CsvFile_finalize(JSContext *cx, JSObject *obj);
void js_register_csvfile_CsvFile(JSContext *cx, JS::HandleObject global);
void register_all_csvfile(JSContext* cx, JS::HandleObject obj);
bool js_csvfile_CsvFile_split(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_csvfile_CsvFile_getBody(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_csvfile_CsvFile_parsingByFile(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_csvfile_CsvFile_parsingCsvToJsonSting(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_csvfile_CsvFile_getHead(JSContext *cx, uint32_t argc, JS::Value *vp);

#endif // __csvfile_h__
