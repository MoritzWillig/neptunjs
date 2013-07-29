/* 
 * File:   abstractNative.cpp
 * Author: moritz
 * 
 * Created on January 27, 2013, 11:17 PM
 */

#include "../../../libs/v8_64bit/include/v8.h"
#include "abstractNative.h"

namespace addin_AbstractNative {
v8::Persistent<v8::Function> v8abstractNative;

namespace {

JS_METHOD(_constructor) {
    if (!args.IsConstructCall()) {
        JS_EXCEPTION("Cannot call constructor as a function");
    }
    JS_RETURN(args.This());
}

}

/*
 * Creates the AbstractNative class
 */
void load() {
    v8::HandleScope hs;
    
    //Create new class template
    v8::Handle<v8::FunctionTemplate> perm_templ = v8::FunctionTemplate::New(_constructor);
    perm_templ->SetClassName(v8::String::New("AbstractNative")); //set template name
    
    //get instance template; create space for native class pointer
    v8::Handle<v8::ObjectTemplate> it = perm_templ->InstanceTemplate();
    it->SetInternalFieldCount(1);
    
    //v8::Context::GetCurrent()->Global()->Set(v8::String::New("AbstractNative"),perm_templ->GetFunction()); //map file into global object
    v8abstractNative.Reset(v8::Isolate::GetCurrent(),perm_templ->GetFunction());
}

void unload() {
    v8abstractNative.Dispose(v8::Isolate::GetCurrent());
}

}