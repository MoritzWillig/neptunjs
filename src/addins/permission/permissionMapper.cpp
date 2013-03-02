/* 
 * File:   permissionMapper.cpp
 * Author: moritz
 * 
 * Created on January 16, 2013, 8:06 PM
 */

#include "../../internalObjects.h"
#include "../../../libs/v8/include/v8.h"
#include "../../mapper/macros.h"
#include "../../Permission.h"
#include "permissionMapper.h"

using namespace v8;

namespace addin_permission {
Persistent<Function> v8permission;
bool cppInit;
namespace {

JS_METHOD(_constructor) {
    if (!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor as a function"));
    }
    
    if (args.Length()!=1) {
        return ThrowException(String::New("Argument missing. Use new Permission(permission_instance)"));
    }
    
    InternalObject<Permission>* t=InternalObject<Permission>::castFrom(args.Holder(),"permission",true);
    InternalObject<Permission>* c=InternalObject<Permission>::castFrom(args[0],"permission",false);
    
    if (c==NULL) {
        InternalObject<Permission>::releaseFrom(t);
        InternalObject<Permission>::releaseFrom(c);
        return ThrowException(String::New("Wrong argument. Use new Permission(permission_instance)"));
    }
    
    t->saveObj(c->getObj());
    V8::AdjustAmountOfExternalAllocatedMemory(sizeof(Permission));
    
    //InternalObject<Permission>::releaseFrom(t); <- call in destructor!
    InternalObject<Permission>::releaseFrom(c);
    return args.This();
}

JS_METHOD(_restrictTrace) {
    Permission* pPermission=InternalObject<Permission>::trustedGet(args.Holder())->getObj();
    
    return Boolean::New(pPermission->restrictTrace(*String::Utf8Value(args[0])));
}

JS_METHOD(_lowerRights) {
    Permission* pPermission=InternalObject<Permission>::trustedGet(args.Holder())->getObj();
    
    if (args.Length()!=3) {
        return ThrowException(Exception::Error(String::New("Argument missing. Use permission.lowerRights(bool read, bool write, bool execute)")));
    }
    
    bool r=args[0]->ToBoolean()->BooleanValue();
    bool w=args[1]->ToBoolean()->BooleanValue();
    bool x=args[2]->ToBoolean()->BooleanValue();
    
    pPermission->lowerRights(r,w,x);
    
    return v8::Undefined();
}

JS_METHOD(_lockTrace) {
    Permission* pPermission=InternalObject<Permission>::trustedGet(args.Holder())->getObj();
    
    pPermission->isFile=true;

    return v8::Undefined();
}

JS_GETTER(_getTraceLocked) {
    Permission* pPermission=InternalObject<Permission>::trustedGet(info.Holder())->getObj();
    
    return v8::Boolean::New(pPermission->isFile);
}

JS_GETTER(_getProtocol) {
    Permission* pPermission=InternalObject<Permission>::trustedGet(info.Holder())->getObj();
    
    return v8::String::New(pPermission->protocol.c_str());
}

JS_GETTER(_getTrace) {
    Permission* pPermission=InternalObject<Permission>::trustedGet(info.Holder())->getObj();
    
    return v8::String::New(pPermission->trace.c_str());
}

JS_GETTER(_getRightsRead) {    
    Permission* pPermission=InternalObject<Permission>::trustedGet(info.Holder())->getObj();
    
    return v8::Boolean::New(pPermission->read);
}

JS_GETTER(_getRightsWrite) {
    Permission* pPermission=InternalObject<Permission>::trustedGet(info.Holder())->getObj();
    
    return v8::Boolean::New(pPermission->write);
}

JS_GETTER(_getRightsExecute) {
    Permission* pPermission=InternalObject<Permission>::trustedGet(info.Holder())->getObj();
    
    return v8::Boolean::New(pPermission->execute);
}

JS_METHOD(_checkPermission) {
    Permission* pPermission=InternalObject<Permission>::trustedGet(args.Holder())->getObj();
    
    if (args.Length()!=1) {
        return ThrowException(Exception::Error(String::New("Argument missing. Use permission.checkPermission(trace)")));
    }
    
    return Boolean::New(pPermission->checkPermission(*String::Utf8Value(args[0])));
}

} //End namespace

/*
 * Mapps the ManagedFile class as "File" into the JS-Context
 */
void load() {
    cppInit=false;
    
    HandleScope hs;
    
    //Create new class template
    Handle<FunctionTemplate> perm_templ = FunctionTemplate::New(_constructor);
    perm_templ->SetClassName(String::New("Permission")); //set template name
    
    //get instance template; create space for native class pointer
    Handle<ObjectTemplate> it = perm_templ->InstanceTemplate();
    it->SetInternalFieldCount(1);
    
    
    //instance vars (File.*)
    //file_templ->Set("loadFile",FunctionTemplate::New(fileLoadFile));
 
    //add prototype functions (new File.*)
    Local<ObjectTemplate> perm_proto = perm_templ->PrototypeTemplate();
    v8::Handle<v8::AccessorSignature> asign=v8::AccessorSignature::New(perm_templ);
    v8::Handle<v8::Signature> sign=v8::Signature::New(perm_templ);
    
    SET_NATIVE(perm_proto,"restrictedTrace",_restrictTrace,sign);
    SET_NATIVE(perm_proto,"lowerRights",_lowerRights,sign);
    SET_NATIVE(perm_proto,"lockTrace",_lockTrace,sign);
    SET_NATIVE(perm_proto,"checkPermission",_checkPermission,sign);
    
    it->SetAccessor(String::New("traceLocked"),_getTraceLocked,0,Handle<Value>(),
            static_cast<v8::AccessControl>(v8::DEFAULT),
            static_cast<v8::PropertyAttribute>(v8::ReadOnly),
            asign);
    it->SetAccessor(String::New("protocol"),_getProtocol,0,Handle<Value>(),
            static_cast<v8::AccessControl>(v8::DEFAULT),
            static_cast<v8::PropertyAttribute>(v8::ReadOnly),
            asign);
    it->SetAccessor(String::New("trace"),_getTrace,0,Handle<Value>(),
            static_cast<v8::AccessControl>(v8::DEFAULT),
            static_cast<v8::PropertyAttribute>(v8::ReadOnly),
            asign);
    it->SetAccessor(String::New("read"),_getRightsRead,0,Handle<Value>(),
            static_cast<v8::AccessControl>(v8::DEFAULT),
            static_cast<v8::PropertyAttribute>(v8::ReadOnly),
            asign);
    it->SetAccessor(String::New("write"),_getRightsWrite,0,Handle<Value>(),
            static_cast<v8::AccessControl>(v8::DEFAULT),
            static_cast<v8::PropertyAttribute>(v8::ReadOnly),
            asign);
    it->SetAccessor(String::New("execute"),_getRightsExecute,0,Handle<Value>(),
            static_cast<v8::AccessControl>(v8::DEFAULT),
            static_cast<v8::PropertyAttribute>(v8::ReadOnly),
            asign);
    
    v8::Context::GetCurrent()->Global()->Set(String::New("Permission"),perm_templ->GetFunction()); //map file into global object
    v8permission = Persistent<Function>::New(perm_templ->GetFunction());
}

void unload() {
    v8permission.MakeWeak(NULL,NULL);
}

}