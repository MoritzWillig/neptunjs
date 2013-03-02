/* 
 * File:   PermissionChecks.h
 * Author: moritz
 *
 * Created on February 20, 2013, 4:32 PM
 */

#ifndef PERMISSIONCHECKS_H
#define	PERMISSIONCHECKS_H

#include "../../v8/include/v8.h"
#include "../Permission.h"
#include "../internalObjects.h"

namespace PermissionChecks {

    bool checkPermission(v8::Handle<v8::Object> perm, string trace);
    
    template<class T> Permission* canAccept(v8::Handle<v8::Value> val, string trace) {
        if (val->IsArray()) {
            v8::Handle<v8::Array> a=v8::Handle<v8::Array>::Cast(val);
            for (int i=0; i<a->Length(); i++) {
                v8::Handle<v8::Value> p=a->Get(i);
                if (p->IsObject()) {
                    if (checkPermission(v8::Handle<v8::Object>::Cast(p),trace)) {
                        InternalObject<Permission>* v=InternalObject<Permission>::trustedGet(v8::Handle<v8::Object>::Cast(p));
                        return v->getObj();
                    }
                }
            }
            return NULL;
        } else {
            if (val->IsObject()) {
                if (checkPermission(v8::Handle<v8::Object>::Cast(val),trace)) {
                    InternalObject<Permission>* v=InternalObject<Permission>::trustedGet(v8::Handle<v8::Object>::Cast(val));
                    return v->getObj();
                }
            } else {
                return NULL;
            }
        }
    }
}

#endif	/* PERMISSIONCHECKS_H */

