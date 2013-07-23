/* 
 * File:   macros.h
 * Author: Moritz Willig
 * including parts from the V8cgi Project (http://code.google.com/p/v8cgi/) macros.h
 * 
 * Created on September 17, 2012, 4:49 AM
 */

#ifndef MACROS_H
#define	MACROS_H

//replaced this() by holder()
//SetPointerInInternalField was marked deprecated
//#define SAVE_PTR(index, ptr) args.Holder()->SetPointerInInternalField(index, (void*)(ptr))
//#define LOAD_PTR(index, type) reinterpret_cast<type>(args.Holder()->GetPointerFromInternalField(index))

#define SAVE_PTR(index, ptr) args.Holder()->SetInternalField(index,External::New(ptr));
#define LOAD_PTR(index, type) reinterpret_cast<type>(v8::Handle<v8::External>::Cast(args.Holder()->GetInternalField(index))->Value())

#define SAVE_VALUE(index,val) args.Holder()->SetInternalField(index,val)
#define LOAD_VALUE(index) args.Holder()->GetInternalField(index)

#define JS_METHOD(name) v8::Handle<v8::Value> name(const v8::Arguments& args)
#define JS_GETTER(name) v8::Handle<v8::Value> name(v8::Local<v8::String> property, const v8::AccessorInfo &info)

#define JS_FUNCTIONTEMP(name) v8::Handle<v8::Value> name(const v8::FunctionCallbackInfo<v8::Value>& args)

typedef JS_METHOD(NativeFunction);

#define SET_NATIVE(proto,name,callback,signature) proto->Set(name,FunctionTemplate::New(callback,v8::Handle<v8::Value>(),signature));



#endif	/* MACROS_H */

