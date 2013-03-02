/* 
 * File:   internalObjects.h
 * Author: moritz
 *
 * Created on January 26, 2013, 9:28 PM
 */

#ifndef INTERNALOBJECTS_H
#define	INTERNALOBJECTS_H

#include <string>
//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>
//#include "../../mapper/macros.h"
#include "../../../libs/v8/include/v8.h"

using namespace std;


template<class T> class InternalObject {
public:
    static InternalObject<T>* trustedGet(v8::Handle<v8::Object> obj) {
        v8::Handle<v8::Value> i=obj->GetInternalField(0);
        v8::Handle<v8::External> e=v8::Handle<v8::External>::Cast(i);
        InternalObject<T>* r = static_cast<InternalObject<T>*>(e->Value());
        
        return r;
    }

    static InternalObject<T>* castFrom(
        v8::Handle<v8::Value> obj, string className, bool tryCreate) {
        
        //test if the object already contains an internalObject
        if (!obj->IsObject()) { return NULL; }
        v8::Handle<v8::Object> o = v8::Handle<v8::Object>::Cast(obj);
        v8::Handle<v8::Value> i=o->GetInternalField(0);
        if (!i->IsExternal()) {
            //if not should a new be created?
            if (tryCreate) {
               //create new InternalObject
               InternalObject<T>* rs = new InternalObject<T>();
               rs->className=className;
               
               //save new instance to internalField
               i = v8::External::New(rs);
               o->SetInternalField(0,i);
            } else {
                return NULL; 
            }
        }
        v8::Handle<v8::External> e=v8::Handle<v8::External>::Cast(i);
        //tests internal class name
        InternalObject<T>* r = static_cast<InternalObject<T>*>(e->Value());
        
        if (r->className!=className) { return NULL; }
        
        r->refCount+=1;
        return r;
    }
    
    static void releaseFrom(InternalObject<T>* io) {
        io->refCount-=1;
        
        if (io->refCount==0) {
            delete io;
        }
    }

    T* getObj () {
        return this->obj;
    }

    void saveObj(T* obj) {
        this->obj=obj;
    }

    InternalObject() {
        this->obj=NULL;
        this->className="";
        this->refCount=0;
    }
    
    ~InternalObject() {
        this->obj=NULL;
    }

    //string className;
    string className;
    int refCount;
private:
    T* obj;
};


#endif	/* INTERNALOBJECTS_H */

