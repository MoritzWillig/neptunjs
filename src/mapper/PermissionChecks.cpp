/**
 * @author: Moritz Willig
 * @date: 2013_01_12
 * Routines to handle permissions for addins
**/

#include "../../v8/include/v8.h"
#include "../Permission.h"
#include "../internalObjects.h"

#include "PermissionChecks.h"

namespace PermissionChecks {

    ///*
    bool checkPermission(v8::Handle<v8::Object> perm, string trace) {
        InternalObject<Permission>* v=InternalObject<Permission>::castFrom(perm,"permission",false);

        if (v!=NULL) {
            Permission* p=v->getObj();
            bool b=p->checkPermission(trace);

            InternalObject<Permission>::releaseFrom(v);
            return b;
        } else { return false; }
    }


    //*/

}
