/* 
 * File:   fileMapper.cpp
 * Author: Moritz Willig
 * 
 * Created on September 17, 2012, 2:17 AM
 */

#include <iostream>

#include "../../../libs/v8_64bit/include/v8.h"
#include "../../mapper/macros.h"
#include "../../internalObjects.h"
#include "../../mapper/PermissionChecks.h"
#include "managedFile.h"
#include "fileMapper.h"

using namespace v8;

namespace addin_file {

namespace {

Persistent<Function> v8file;

JS_METHOD(_constructor) {
    if (!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor as function"));
    }
    
    InternalObject<ManagedFile>* t=InternalObject<ManagedFile>::castFrom(args.This(),"managedfile",true);
    t->saveObj(new ManagedFile("./"));
    //V8::AdjustAmountOfExternalAllocatedMemory(sizeof(&pFile));
    //SAVE_PTR(0,pFile); //Save file instance
    
    //save default permission array
    if (args.Length()>0) {
        args.This()->Set(String::New("permissions"),args[0]);
    } else {
        v8::Handle<v8::Value> p=v8::Context::GetCurrent()->Global()->Get(v8::String::New("permissions"));
        if (p->IsObject()) {
            v8::Handle<v8::Object> o=v8::Handle<v8::Object>::Cast(p);
            v8::Handle<v8::Value> a=o->Get(String::New("file"));
            if (!a->IsUndefined()) {
                args.This()->Set(String::New("permissions"),a);
            }
        }
    }
    
    return args.This();
}


JS_METHOD(_getFileName) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();

    bool b;
    switch (args.Length()) {
        case 0: return String::New(pFile->getFileName(false,false).c_str());
        case 1: 
            b=args[0]->ToBoolean()->BooleanValue();
            return String::New(pFile->getFileName(b,false).c_str());
        default:
            return v8::ThrowException(v8::Exception::Error(v8::String::New("File: invalid parameter count")));
    }
}

JS_METHOD(_isInDirectory) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();

    if (args.Length()!=1) {
        return ThrowException(Exception::Error(String::New("Argument missing. Use file.isInDirectory(filename)")));
    }
    
    return Boolean::New(pFile->isInDirectory(*String::Utf8Value(args[0])));
}

JS_METHOD(_loadFile) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();

    if (args.Length()!=1) {
        return ThrowException(Exception::Error(String::New("Argument missing. Use file.load(filename)")));
    }
    
    string s=*String::Utf8Value(args[0]);
    
    Permission* p=PermissionChecks::canAccept<Permission>(args.This()->Get(v8::String::New("permissions")),s);
    if (p==NULL) {
        return ThrowException(Exception::Error(String::New("No Permissions were given for the requested action")));
    }
    pFile->importFromPermission(*p);
    
    return Boolean::New(pFile->loadFile(s));
}

JS_METHOD(_closeFile) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();

    pFile->clearRights();
    pFile->closeFile();
    
    return v8::Undefined();
}

JS_METHOD(_isLoaded) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();

    return Boolean::New(pFile->isLoaded());    
}

JS_METHOD(_setContent) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();

    if (args.Length()!=1) {
        return ThrowException(Exception::Error(String::New("Argument missing. Use file.setCOntent(content)")));
    }
    
    if (!pFile->rights.write) {
        return ThrowException(Exception::Error(String::New("No Permissions were given for the requested action")));
    }
    
    string s=*String::Utf8Value(args[0]);
    
    pFile->setContent(s);
    return v8::Undefined();
}

JS_METHOD(_getContent) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();

    if (!pFile->rights.read) {
        return ThrowException(Exception::Error(String::New("No Permissions were given for the requested action")));
    }
    
    return v8::String::New(pFile->getContent().c_str());
}

JS_METHOD(_read) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();

    if ((args.Length()!=2) && (args[0]->IsString()) && (args[1]->IsInt32())) {
        return ThrowException(Exception::Error(String::New("Argument missing. Use file.read(pos,len)")));
    }
    
    if (!pFile->rights.read) {
        return ThrowException(Exception::Error(String::New("No Permissions were given for the requested action")));
    }
    return v8::String::New(pFile->read(args[0]->Int32Value(),args[1]->Int32Value()).c_str());
}

JS_METHOD(_write) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();

    if ((args.Length()!=2) && (args[0]->IsString()) && (args[1]->IsInt32())) {
        return ThrowException(Exception::Error(String::New("Argument missing. Use file.setCOntent(content)")));
    }
    
    if (!pFile->rights.write) {
        return ThrowException(Exception::Error(String::New("No Permissions were given for the requested action")));
    }
    
    pFile->write(*String::Utf8Value(args[0]),args[1]->Int32Value());
    return v8::Undefined();
}

JS_METHOD(_getSize) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();

    if (!pFile->rights.read) {
        return ThrowException(Exception::Error(String::New("No Permissions were given for the requested action")));
    }
    return v8::Boolean::New(pFile->getSize());    
}

JS_METHOD(_append) {
    ManagedFile* pFile=InternalObject<ManagedFile>::trustedGet(args.Holder())->getObj();
    
    if ((args.Length()!=1) && (args[0]->IsString())) {
        return ThrowException(Exception::Error(String::New("Argument missing. Use file.setCOntent(content)")));
    }
    
    if (!pFile->rights.write) {
        return ThrowException(Exception::Error(String::New("No Permissions were given for the requested action")));
    }
    
    pFile->append(*String::Utf8Value(args[0]));
    return v8::Undefined();    
}

} //End namespace

/*
 * Mapps the ManagedFile class as "File" into the JS-Context
 */
void load() {
    HandleScope hs;
    
    //Create new class template
    Handle<FunctionTemplate> file_templ = FunctionTemplate::New(_constructor);
    file_templ->SetClassName(String::New("File")); //set template name
    
    //get instance template; create space for native class pointer
    Handle<ObjectTemplate> it = file_templ->InstanceTemplate();
    it->SetInternalFieldCount(1); /* managedFile */
    
    //add prototype functions (new File.*)
    Local<ObjectTemplate> file_proto = file_templ->PrototypeTemplate();

    v8::Handle<v8::Signature> sign=v8::Signature::New(file_templ);
    SET_NATIVE(file_proto,"getPath",_getFileName,sign);
    SET_NATIVE(file_proto,"load",_loadFile,sign);
    SET_NATIVE(file_proto,"isInDirectory",_isInDirectory,sign);
    SET_NATIVE(file_proto,"close",_closeFile,sign);
    SET_NATIVE(file_proto,"isLoaded",_isLoaded,sign);
    SET_NATIVE(file_proto,"getContent",_getContent,sign);
    SET_NATIVE(file_proto,"setContent",_setContent,sign);
    SET_NATIVE(file_proto,"read",_read,sign);
    SET_NATIVE(file_proto,"write",_write,sign);
    SET_NATIVE(file_proto,"getSize",_getSize,sign);
    SET_NATIVE(file_proto,"append",_append,sign);
    //file_proto->Set(String::New("X"),FunctionTemplate::New(fileGetFileName)->GetFunction());
    
    v8::Context::GetCurrent()->Global()->Set(String::New("File"),file_templ->GetFunction()); //map file into global object
    v8file = Persistent<Function>::New(file_templ->GetFunction());
}

void unload() {
    v8file.MakeWeak(NULL,NULL);
}

}