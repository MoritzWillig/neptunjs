/* 
 * File:   permissionMapper.h
 * Author: moritz
 *
 * Created on January 16, 2013, 8:06 PM
 */

#ifndef PERMISSIONMAPPER_H
#define	PERMISSIONMAPPER_H

#include <iostream>
#include "../../mapper/macros.h"
#include "../../../libs/v8/include/v8.h"

using namespace v8;

namespace addin_permission {
    extern Persistent<Function> v8permission;
    extern bool cppInit;
namespace {

//no constructor - permissions are given by native code only
JS_METHOD(_constructor);

JS_METHOD(_restrictTrace);
JS_METHOD(_lowerRights);
JS_METHOD(_lockTrace);

JS_GETTER(_getTraceLocked);
JS_GETTER(_getProtocol);
JS_GETTER(_getTrace);
JS_GETTER(_getRightsRead);
JS_GETTER(_getRightsWrite);
JS_GETTER(_getRightsExecute);

JS_METHOD(_checkPermission);
}

void load();
void unload();
}

#endif	/* PERMISSIONSMAPPER_H */

