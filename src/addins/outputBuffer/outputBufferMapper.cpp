/* 
 * File:   fileMapper.cpp
 * Author: Moritz Willig
 * 
 * Created on September 17, 2012, 2:17 AM
 */

#include <iostream>

#include "../../../libs/v8_64bit/include/v8.h"
#include "../../mapper/macros.h"
#include "outputBuffer.h"

using namespace v8;

namespace addin_outputBuffer {

namespace {

//Persistent<Object> v8outputBuffer;

JS_METHOD(_open) {
    OutputBuffer::open();
    JS_RETURN(v8::Boolean::New(true));
}

JS_METHOD(_close) {
    OutputBuffer::OutputBuffer* ob = OutputBuffer::getCurrent();
    if (ob==NULL) { JS_EXCEPTION("No output buffer opened"); }
    OutputBuffer::close();
    
    JS_RETURN(v8::Boolean::New(true));
}

JS_METHOD(_write) {
    OutputBuffer::OutputBuffer* ob = OutputBuffer::getCurrent();
    if (ob==NULL) { JS_EXCEPTION("No output buffer opened"); }
    
    string s="";
    for (int i=0; i<args.Length(); i++) {
        v8::String::AsciiValue ts(args[i]->ToString());
        s+=std::string(*ts);
    }
    OutputBuffer::getCurrent()->write(s);
    
    JS_RETURN(v8::Boolean::New(true));
}

JS_METHOD(_writeln) {
    OutputBuffer::OutputBuffer* ob = OutputBuffer::getCurrent();
    if (ob==NULL) { JS_EXCEPTION("No output buffer opened"); }
    
    string s="";
    for (int i=0; i<args.Length(); i++) {
        v8::String::AsciiValue ts(args[i]->ToString());
        s+=std::string(*ts);
    }
    OutputBuffer::getCurrent()->write(s+"\n");
    
    JS_RETURN(v8::Boolean::New(true));
}

JS_METHOD(_read) {
    OutputBuffer::OutputBuffer* ob = OutputBuffer::getCurrent();
    if (ob==NULL) { JS_EXCEPTION("No output buffer opened"); }
    JS_RETURN(v8::String::New(OutputBuffer::getCurrent()->read().c_str()));
}

JS_METHOD(_flush) {
    OutputBuffer::OutputBuffer* ob = OutputBuffer::getCurrent();
    if (ob==NULL) { JS_EXCEPTION("No output buffer opened"); }
    
    JS_RETURN(v8::String::New(OutputBuffer::getCurrent()->flush().c_str()));
}

} //End namespace

/*
 * Mapps the Outputbuffer as "OutputBuffer" into the JS-Context
 */
void load() {
    HandleScope hs;
    
    //Create new class template
    Handle<Object> obj = Object::New();
    
    obj->Set(String::New("open"   ),FunctionTemplate::New(_open   )->GetFunction());
    obj->Set(String::New("close"  ),FunctionTemplate::New(_close  )->GetFunction());
    obj->Set(String::New("write"  ),FunctionTemplate::New(_write  )->GetFunction());
    obj->Set(String::New("writeln"),FunctionTemplate::New(_writeln)->GetFunction());
    obj->Set(String::New("read"   ),FunctionTemplate::New(_read   )->GetFunction());
    obj->Set(String::New("flush"  ),FunctionTemplate::New(_flush  )->GetFunction());
    
    //v8outputBuffer.Reset(Isolate::GetCurrent(),obj->NewInstance());
    v8::Context::GetCurrent()->Global()->Set(String::New("outputBuffer"),obj); //map into global object
    v8::Context::GetCurrent()->Global()->Set(String::New("ob"),obj); //save with short name
}

void unload() {
    //v8outputBuffer.Dispose(Isolate::GetCurrent());
    OutputBuffer::closeAll();
}

}